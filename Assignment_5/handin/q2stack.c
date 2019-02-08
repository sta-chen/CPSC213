#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Element {
    char   name[200];
    struct Element *next;
};

struct Element *top = 0;

void push (char* aName) {
    struct Element* e = malloc (sizeof (*e));    // Not the bug: sizeof (*e) == sizeof(struct Element)
    strncpy (e->name, aName, sizeof (e->name));  // Not the bug: sizeof (e->name) == 200
    e->next  = top;
    top = e;
}

char* pop() {
    struct Element* e = top;
    top = e->next;
    char* temp = malloc(sizeof(e->name));
    strncpy(temp, e->name, sizeof(e->name));
    free (e);
    return temp;
}

int main (int argc, char** argv) {
    push ("A");
    push ("B");
    char* w = pop(); // B
    push ("C");
    push ("D");
    char* x = pop(); // D
    char* y = pop(); // C
    char* z = pop(); // A
    printf ("%s %s %s %s\n", w, x, y, z);
    free(w);
    free(x);
    free(y);
    free(z);
}
