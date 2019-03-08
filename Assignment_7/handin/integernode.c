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

void IntegerNode_ctor(void* thisv, int i) {
    struct IntegerNode* this = thisv;
    Node_ctor(this);
    this->i = i;
}

int IntegerNode_compareTo(void* thisv, void* nodev) {
    struct IntegerNode* this = thisv;
    struct IntegerNode* node = nodev;
    if (this->i < node->i) {
        return -1;
    } else if (this->i > node->i) {
        return 1;
    } else {
        return 0;
    }
}

int IntegerNode_sum(void* thisv){
    struct IntegerNode* this = thisv;
    if (thisv == NULL) {
        return 0;
    }
    return this->i + IntegerNode_sum(this->left) + IntegerNode_sum(this->right);
}

void IntegerNode_printNode(void* thisv) {
    struct IntegerNode* this = thisv;
    printf("%d\n", this->i);
}

void* new_IntegerNode(int i) {
    struct IntegerNode* obj = malloc(sizeof(struct IntegerNode));
    obj->class = &IntegerNode_class_table;
    IntegerNode_ctor(obj, i);
    return obj;
}
