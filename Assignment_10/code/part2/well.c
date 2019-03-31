#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

#define MAX_OCCUPANCY      3
#define NUM_ITERATIONS     100
#define NUM_PEOPLE         20
#define FAIR_WAITING_COUNT 4

/**
 * You might find these declarations useful.
 */
enum Endianness {LITTLE = 0, BIG = 1};
const static enum Endianness oppositeEnd [] = {BIG, LITTLE};

struct Well {
    // TODO
    uthread_mutex_t mx;
    uthread_cond_t littleOrBig[2];
    int numInWell;
    enum Endianness typeInWell;
    int waitingCount[2];
    int isFair;
};

struct Well* createWell() { // well is global!
    struct Well* well = malloc (sizeof (struct Well));
    // TODO
    well->mx = uthread_mutex_create();
    well->littleOrBig[LITTLE] = 0;
    well->littleOrBig[BIG] = 0;
    well->numInWell = 0;
    well->typeInWell = 0; // default is LITTLE
    well->waitingCount[LITTLE] = 0;
    well->waitingCount[BIG] = 0;
    well->oppositeWaitingCount = 0;
    return well;
}

struct Well* Well; // we have a global Well variable

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_PEOPLE)
int             entryTicker;                                          // incremented with each entry
int             waitingHistogram         [WAITING_HISTOGRAM_SIZE];
int             waitingHistogramOverflow;
uthread_mutex_t waitingHistogrammutex;
int             occupancyHistogram       [2] [MAX_OCCUPANCY + 1];

void enterWell (enum Endianness g) {
    // TODO
    uthread_mutex_lock(Well->mx);
    while (1) {
        int isEmpty = (Well->numInWell == 0);
        int hasSpace = (Well->numInWell < MAX_OCCUPANCY);
        int sameType = (Well->typeInWell == g);
        int otherTypeWaiting = (Well->waitingCount[oppositeEnd[g]] > 0);
        int isNotFair = (Well->oppositeWaitingCount >= FAIR_WAITING_COUNT);
        int turnToOppositeType = (Well->oppositeWaitingCount && isNotFair);
//        if (Well->numInWell == 0 | (Well->numInWell < MAX_OCCUPANCY))
        
//        if (isEmpty) {
//            Well->littleOrBig[g]++;
//        }
        // empty or hasSpace
        if (isEmpty || hasSpace && sameType && !turnToOppositeType) {
            if (sameType) {
                Well->oppositeWaitingCount++; // same type continuously enter the well
            } else {
                Well->oppositeWaitingCount = 0; // only one person entered the well with no other person waiting
            }
            entryTicker++;
            break;
        }
        
        // not empty and not same type and no same type is waiting
        if (!sameType && Well->waitingCount[g] == 0) {
            Well->oppositeWaitingCount = 0;
        }
        Well->waitingCount[g]++; // inc waiting count for type g
        uthread_cond_wait(Well->littleOrBig[g]); // wait until can enter
        Well->waitingCount[g]--; // dec waiting count for type g
    }
    assert(Well->numInWell == 0 || Well->typeInWell == g); // empty or same type in well
    assert(Well->numInWell < MAX_OCCUPANCY); // numInWell should less than MAX_OCCUPANCY
    Well->typeInWell = g;
    Well->numInWell++;
    occupancyHistogram[Well->typeInWell][Well->numInWell]++;
    uthread_mutex_unlock(Well->mx);
    
}

void leaveWell() {
    // TODO
    uthread_mutex_lock(Well->mx);
    Well->numInWell-=;
    enum Endianness typeIn = Well->typeInWell;
    enum Endianness typeOut = oppositeEnd[typeIn];
    int isTypeOutWaiting = (Well->waitingCount[typeOut] > 0);
    int isNotFair = Well->oppositeWaitingCount >= FAIR_WAITING_COUNT;
    int isTypeInWaiting = (Well->waitingCount[typeIn] > 0);
    
    // opposite type is waiting and [no same type waiting of is not fair]
    if (isTypeOutWaiting && (!isTypeInWaiting || isNotFair)) {
        if (Well->numInWell == 0) {
            for (int i = 0; i < MAX_OCCUPANCY; i++) {
                // signal opposite type could enter
                uthread_cond_signal(Well->littleOrBig[typeOut]);
            }
        }
    } else if (isTypeInWaiting) {
        // signal same type cout enter
        uthread_cond_signal(Well->littleOrBig[typeIn]);
    }
    uthread_mutex_unlock(Well->mutex);
}

void recordWaitingTime (int waitingTime) {
    uthread_mutex_lock (waitingHistogrammutex);
    if (waitingTime < WAITING_HISTOGRAM_SIZE)
        waitingHistogram [waitingTime] ++;
    else
        waitingHistogramOverflow ++;
    uthread_mutex_unlock (waitingHistogrammutex);
}

//
// TODO
// You will probably need to create some additional produres etc.
//

void* person() {
    enum Endianness e = random() & 1;
    for (int i = 0; i < NUM_PEOPLE; i++) {
        int start = entryTicker;
        enterWell(e);
        recordWaitingTime(entryTicker - start - 1);
        for (int j = 0; j < NUM_PEOPLE; j++) {
            uthread_yield();
        }
        leaveWell();
        for (int j = 0; j < NUM_PEOPLE; j++) {
            uthread_yield();
        }
    }
    return NULL;
}
    


int main (int argc, char** argv) {
    uthread_init (1);
    Well = createWell();
    uthread_t pt [NUM_PEOPLE];
    waitingHistogrammutex = uthread_mutex_create ();
    
    // TODO
    
    for (int i = 0; i < NUM_PEOPLE; i++) {
        pt[i] = uthread_create(person, Well);
    }
    for (int i = 0; i < NUM_PEOPLE; i++) {
        uthread_join(pt[i], 0);
    }
    
    printf ("Times with 1 little endian %d\n", occupancyHistogram [LITTLE]   [1]);
    printf ("Times with 2 little endian %d\n", occupancyHistogram [LITTLE]   [2]);
    printf ("Times with 3 little endian %d\n", occupancyHistogram [LITTLE]   [3]);
    printf ("Times with 1 big endian    %d\n", occupancyHistogram [BIG] [1]);
    printf ("Times with 2 big endian    %d\n", occupancyHistogram [BIG] [2]);
    printf ("Times with 3 big endian    %d\n", occupancyHistogram [BIG] [3]);
    printf ("Waiting Histogram\n");
    for (int i=0; i<WAITING_HISTOGRAM_SIZE; i++)
        if (waitingHistogram [i])
            printf ("  Number of times people waited for %d %s to enter: %d\n", i, i==1?"person":"people", waitingHistogram [i]);
    if (waitingHistogramOverflow)
        printf ("  Number of times people waited more than %d entries: %d\n", WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
