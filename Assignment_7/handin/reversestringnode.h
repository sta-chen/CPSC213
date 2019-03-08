#ifndef __REVERSESTRINGNODE_H__
#define __REVERSESTRINGNODE_H__

// TODO
struct ReverseStringNode_class {
    int (*compareTo) (void*, void*);
    void (*printNode) (void*);
    void (*insert) (void*, void*);
    void (*print) (void*);
    void (*delete) (void*);
};
extern struct ReverseStringNode_class ReversStringNode_class_table;

struct ReverseStringNode;
struct ReverseStringNode {
    struct ReverseStringNode_class* class;
    
    struct ReverseStringNode* left;
    struct ReverseStringNode* right;
    
    char* s;
};

int ReverseStringNode_compareTo(void*, void*);
void ReverseStringNode_ctor(void*, char*);

void* new_ReverseStringNode(char*);

#endif /*__REVERSESTRINGNODE_H__*/
