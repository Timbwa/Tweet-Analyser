/*
 * Author: David T. Auna
 * date: 3/1/2019
 * Library to maintain stack functionality
*/

#ifndef STACK_H
#define STACK_H

#include "AVLTree.h"
struct Node{
    AVLTree tree;
    struct Node * next;
};

typedef struct Node *Stack;

Stack createStack();
void makeEmptyStack(Stack);
void pushStack(AVLTree, Stack);
AVLTree popStack(Stack);
int isEmpty(Stack);
#endif //STACK_H
