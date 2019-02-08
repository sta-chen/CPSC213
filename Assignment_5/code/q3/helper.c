#include <stdlib.h>
#include "set.h"
#include "stack.h"
#include "integer.h"
#include "helper.h"

void helper_process_input(int argc, char** argv) {
  for (int i=1; i<argc; i++) {
    struct integer* integer = integer_create(atoi(argv[i]));
    set_add(integer);
    stack_push(integer);
  }
}

