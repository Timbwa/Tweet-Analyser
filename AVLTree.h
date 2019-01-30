/*
 * Author: David T. Auna
 * date: 3/1/2019
 * Library to maintain the custom AVL Trees
*/
#ifndef AVLTREE_H
#define AVLTREE_H

#include "LinkedList.h"

struct TweetNode{
    char * hashtag;
    TweetIDList tweetIDs;
    struct TweetNode * left;
    struct TweetNode * right;
    int height;
};

typedef struct TweetNode * AVLTree;

AVLTree createTree(void);
AVLTree makeEmptyTree(AVLTree);
AVLTree singleRotateWithLeft(AVLTree);
AVLTree singleRotateWithRight(AVLTree);
AVLTree doubleRotateWithLeft(AVLTree);
AVLTree doubleRotateWithRight(AVLTree);
void DisplayTreeStructure(AVLTree, int);
int Max(int, int);
int treeHeight(AVLTree);

#endif //INC_3_TWEET_ANALYSER_AVLTREE_H
