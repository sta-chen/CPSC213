#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "integernode.h"

// TODO
struct IntegerNode_class IntegerNode_class_table = {
    IntegerNode_compareTo,
    IntegerNode_printNode,
    Node_insert,
    Node_print,
    Node_delete,
    IntegerNode_sum,
};
