/*
 * Author: David T. Auna
 * date: 3/1/2019
*/
#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

// create stack
Stack createStack(){
    Stack stack = (Stack) malloc(sizeof(struct Node));
    stack->next = NULL;
    return stack;
}

// check if the stack is empty
int isEmpty(Stack stack){
    if(stack->next == NULL){
        return 1;
    }
    return 0;
}

// pops a tree from the stack
AVLTree popStack(Stack stack){
    Stack removeNode;
    AVLTree tree;
    if (isEmpty(stack)){
        printf("No tree in the stack!\n");
        return NULL;
    } else{
        removeNode = stack->next;
        stack->next = stack->next->next;
        tree = removeNode->tree;
        free(removeNode);
        return tree;
    }
}

// empties the stack
void makeEmptyStack(Stack stack){
    if(stack->next == NULL){
        while (!isEmpty(stack)){
            popStack(stack);
        }
    }
}

// pushes a tree to the stack

void pushStack(AVLTree tree, Stack stack){
    Stack newNode = (Stack) malloc(sizeof(struct Node));
    if (newNode == NULL){
        printf("Couldn't allocate memory for new stack node!\n");
    } else{
        newNode->tree = tree;
        newNode->next = stack->next;
        stack->next = newNode;
    }
}