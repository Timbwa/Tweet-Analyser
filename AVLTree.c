/*
 * Author: David T. Auna
 * date: 3/1/2019
*/

#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

AVLTree createTree(void){
    return NULL;
}

AVLTree makeEmptyTree(AVLTree hashtagTree){
    if(hashtagTree != NULL){
        makeEmptyTree(hashtagTree->left);
        makeEmptyTree(hashtagTree->right);
        free(hashtagTree->tweetIDs);
        free(hashtagTree);
    }
    return NULL;
}

int Max(int num1, int num2) {
    if (num1 >= num2){
        return num1;
    }
    else{
        return num2;
    }
}

int treeHeight(AVLTree hashtagTree){
    if(hashtagTree == NULL){
        return 0;
    }
    else {
        return Max(treeHeight(hashtagTree->left), treeHeight(hashtagTree->right)) + 1;
    }
}

AVLTree singleRotateWithLeft(AVLTree k2){
    AVLTree tempK2 = k2;
    AVLTree k1 = tempK2->left;

    if(k1->right == NULL){
        k1->right = tempK2;
        tempK2->left = NULL;
        k1->height = treeHeight(k1);
        k2->height = treeHeight(k2);
        return k1;
    } else{
        AVLTree tempK1 = k1->right;
        k1->right = tempK2;
        tempK2->left = tempK1;
        k1->height = treeHeight(k1);
        k2->height = treeHeight(k2);
        return k1;
    }
}

AVLTree singleRotateWithRight(AVLTree k1){
    AVLTree tempK1 = k1;
    AVLTree k2 = tempK1->right;

    if(k2->left == NULL){
        k2->left = tempK1;
        tempK1->right = NULL;
        k1->height = treeHeight(k1);
        k2->height = treeHeight(k2);
        return k2;
    } else{
        AVLTree tempK2 = k2->left;
        k2->left = tempK1;
        tempK1->right = tempK2;
        k1->height = treeHeight(k1);
        k2->height = treeHeight(k2);
        return k2;
    }
}

AVLTree doubleRotateWithLeft(AVLTree k3){
    k3->left = singleRotateWithRight(k3->left);
    return singleRotateWithLeft(k3);
}

AVLTree doubleRotateWithRight(AVLTree k3){
    k3->right = singleRotateWithLeft(k3->right);
    return singleRotateWithRight(k3);
}

void DisplayTreeStructure(AVLTree hashtagTree, int depth){
    int i;

    if (hashtagTree != NULL)
    {
        DisplayTreeStructure(hashtagTree->right, depth + 1);

        for (i = 0; i < depth; i++)
            printf("_");
        printf("%s\n", hashtagTree->hashtag);

        DisplayTreeStructure(hashtagTree->left, depth + 1);
    }
}
