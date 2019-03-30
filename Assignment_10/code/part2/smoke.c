#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

struct Agent {
    uthread_mutex_t mutex;
    uthread_cond_t  match;
    uthread_cond_t  paper;
    uthread_cond_t  tobacco;
    uthread_cond_t  smoke;
};

struct Agent* createAgent() {
    struct Agent* agent = malloc (sizeof (struct Agent));
    agent->mutex   = uthread_mutex_create();
    agent->paper   = uthread_cond_create (agent->mutex);
    agent->match   = uthread_cond_create (agent->mutex);
    agent->tobacco = uthread_cond_create (agent->mutex);
    agent->smoke   = uthread_cond_create (agent->mutex);
    return agent;
}

//
// TODO
// You will probably need to add some procedures and struct etc.
//

struct Smoker {
    uthread_cond_t pm; // need paper and matches
    uthread_cond_t tm; // need tobacco and matches
    uthread_cond_t tp; // need tobacco and paper
    uthread_cond_t smoke; // could smoke
    struct Agent* agent;
    int tobacco, paper, matches; // the number of tobacco, paper, and matches
}

struct Smoker* createSmoker(struct Agent* agent) {
    struct Smoker* smoker = malloc(sizeof(struct Smoker));
    smoker->pm = uthread_cond_create();
    smoker->tm = uthread_cond_create();
    smoker->tp = uthread_cond_create();
    smoker->smoke = uthread_cond_create();
    smoker->agent = agent;
    smoker->tobacco = 0;
    smoker->paper = 0;
    smoker->matches = 0;
    return smoker;
}



/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource            {    MATCH = 1, PAPER = 2,   TOBACCO = 4};
char* resource_name [] = {"", "match",   "paper", "", "tobacco"};

int signal_count [5];  // # of times resource signalled
int smoke_count  [5];  // # of times smoker with resource smoked

/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can re-write it if you like, but be sure that all it does
 * is choose 2 random reasources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void* agent (void* av) {
    struct Agent* a = av;
    static const int choices[]         = {MATCH|PAPER, MATCH|TOBACCO, PAPER|TOBACCO};
    static const int matching_smoker[] = {TOBACCO,     PAPER,         MATCH};
    
    uthread_mutex_lock (a->mutex);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int r = random() % 3;
        signal_count [matching_smoker [r]] ++;
        int c = choices [r];
        if (c & MATCH) {
            VERBOSE_PRINT ("match available\n");
            uthread_cond_signal (a->match);
        }
        if (c & PAPER) {
            VERBOSE_PRINT ("paper available\n");
            uthread_cond_signal (a->paper);
        }
        if (c & TOBACCO) {
            VERBOSE_PRINT ("tobacco available\n");
            uthread_cond_signal (a->tobacco);
        }
        VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");
        uthread_cond_wait (a->smoke);
    }
    uthread_mutex_unlock (a->mutex);
    return NULL;
}

// TODO the smoker procedure
void smoker(struct Smoker* s, enum Resource r, uthread_cond_t waitCond, int* isAvailable) {
    uthread_mutex_lock(s->agent->mutex);
    while (1) {
        uthread_cond_wait(waitCond); // wait for r until available
        *isAvailable = 1; // now r is available
        
        if (s->paper && s->matches) { // need paper and matches to smoke
            s->paper = 0;
            s->matches = 0; // resources used to smoke
            uthread_cond_signal(s->pm); // signalling pm
            uthread_cond_wait(s->smoker); // waiting for smoker
            uthread_cond_signal(s->agent->smoke); // signalling agent
        } else if (s->tobacco && s->matches) {
            s->tobacco = 0;
            s->matches = 0;
            uthread_cond_signal(s->tm);
            uthread_cond_wait(s->smoker);
            uthread_cond_signal(s->agent->smoke);
        } else if (s->tobacco && s->paper) {
            s->tobacco = 0;
            s->paper = 0;
            uthread_cond_signal(s->tp);
            uthread_cond_wait(s->smoker);
            uthread_cond_signal(s->agent->smoke);
        }
    }
    uthread_mutex_unlock(s->agent->mutex);
}

// modify smoke_count
void smoke(struct Smoker* s, enum Resource r, uthread_cond_t waitCond) {
    uthread_mutex_lock(s->agent->mutex);
    while (1) {
        uthread_cond_wait(waitCond); // wait for resources except r
        smoke_count[r]++; // smoker with r is smoking
        uthread_cond_signal(s->smoker);
    }
    uthread_mutex_unlock(s->agent->mutex);
}

// fn pointer for uthread_create
// smoker already have xx resource
void* smokeWithMatch(void* sv) {
    struct Smoker* s = sv;
    smoke(s, MATCH, s->tp);
    return NULL;
}

void* smokeWithPaper(void* sv) {
    struct Smoker* s = sv;
    smoke(s, PAPER, s->tm);
    return NULL;
}

void* smokeWithTobacco(void* sv) {
    struct Smoker* s = sv;
    smoke(s, TOBACCO, s->pm);
    return NULL;
}

// smoker need xx resource
void* smokerNeedMatches(void* sv) {
    struct Smoker* s = sv;
    smoker(s, MATCH, s->agent->matches, &s->match);
    return NULL;
}

void* smokerNeedPaper(void* sv) {
    struct Smoker* s = sv;
    smoker(s, PAPER, s->agent->paper, &s->paper);
    return NULL;
}

void* smokerNeedTobacco(void* sv) {
    struct Smoker* s = sv;
    smoker(s, PAPER, s->agent->tobacco, &s->tobacco);
    return NULL;
}


int main (int argc, char** argv) {
    uthread_init (7);
    struct Agent*  a = createAgent();
    // TODO
    struct Smoker* s = createSmoker(a);
    uthread_create(smokerNeedMatches, s);
    uthread_create(smokerNeedPaper, s);
    uthread_create(smokerNeedTobacco, s);
    uthread_create(smokeWithMatch, s)
    uthread_create(smokeWithPaper, s);
    uthread_create(smokeWithTobacco, s);
    
    
    
    uthread_join (uthread_create (agent, a), 0);
    assert (signal_count [MATCH]   == smoke_count [MATCH]);
    assert (signal_count [PAPER]   == smoke_count [PAPER]);
    assert (signal_count [TOBACCO] == smoke_count [TOBACCO]);
    assert (smoke_count [MATCH] + smoke_count [PAPER] + smoke_count [TOBACCO] == NUM_ITERATIONS);
    printf ("Smoke counts: %d matches, %d paper, %d tobacco\n",
            smoke_count [MATCH], smoke_count [PAPER], smoke_count [TOBACCO]);
}
