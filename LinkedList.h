/*
 * Author: David T. Auna
 * date: 3/1/2019
 * Library to implement a linked list
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct TweetIDNode{
    int tweetID;
    struct TweetIDNode *next;
};

typedef struct TweetIDNode TweetIDNode;

struct TweetIDList{
    TweetIDNode * head;
    TweetIDNode * tail;
    int size;
};

typedef struct TweetIDList * TweetIDList;

TweetIDList CreateList(void);
void makeEmptyList(TweetIDList);
void insertTweetID(TweetIDList, int);
void displayTweetIDs(TweetIDList);


#endif //INC_3_TWEET_ANALYSER_LINKEDLIST_H
