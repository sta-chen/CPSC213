#ifndef __INTEGERNODE_H__
#define __INTEGERNODE_H__

// TODO
struct IntegerNode_class {
    int (*compareTo) (void*, void*);
    void (*printNode) (void*);
    void (*insert) (void*, void*);
    void (*print) (void*);
    void (*delete) (void*);
    int (*sum) (void*);
};

extern struct IntegerNode_class IntegerNode_class_table;

struct IntegerNode;
struct IntegerNode {
    struct IntegerNode_class* class;
    
    struct IntegerNode* left;
    struct IntegerNode* right;
    
    int i;
};

void IntegerNode_ctor(void*, int);
int IntegerNode_compareTo(void*, void*);
void IntegerNode_printNode(void*);
int IntegerNode_sum(void *);

void* new_IntegerNode(int);

#endif /*__INTEGERNODE_H__*/
