/*
 * Author: David T. Auna
 * date: 3/1/2019
*/
#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

TweetIDList CreateList(){
    TweetIDList tweetIDs;
    tweetIDs = (TweetIDList) malloc(sizeof(struct TweetIDList));
    if(tweetIDs == NULL){
        printf("Couldn't make tweetList!\n");
    } else{
        makeEmptyList(tweetIDs);
    }
    return tweetIDs;
}

void makeEmptyList(TweetIDList tweetIDs){
    tweetIDs->head = (TweetIDNode *) malloc(sizeof(TweetIDNode));
    if(tweetIDs->head == NULL){
        printf("Couldn't initialize head Node!\n");
    } else{
        tweetIDs->head->next = NULL;
        tweetIDs->tail = tweetIDs->head;
        tweetIDs->size = 0;
    }
}

void displayTweetIDs(TweetIDList tweetIDs){
    TweetIDNode * printNode;
    printNode = tweetIDs->head->next;
    printf("(Tweets: ");
    while(printNode != NULL){
        printf("%d", printNode->tweetID);
        if(printNode->next != NULL){
            printf(", ");
        } else{
            printf(")");
        }

        printNode = printNode->next;
    }
    printf("\n");
}

void insertTweetID(TweetIDList tweetIDs, int ID){
    TweetIDNode * newTweetID = (TweetIDNode *) malloc(sizeof(TweetIDNode));
    if(newTweetID == NULL){
        printf("Out of memory for new Tweet!\n");
    }else{
        newTweetID->tweetID = ID;
        newTweetID->next = NULL;

        tweetIDs->tail->next = newTweetID;
        tweetIDs->tail = newTweetID;
        tweetIDs->size++;
    }
}