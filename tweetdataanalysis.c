/*
 * Author: David T. Auna
 * date: 3/1/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.c"
#include "AVLTree.c"
#include "Stack.c"

// function to insert a hashtag into the AVL tree
AVLTree insertHashtag(AVLTree hashtagTree, char *hashtag, int tweetID){
   if(hashtagTree == NULL){
       hashtagTree = (AVLTree) malloc(sizeof(struct TweetNode));
       if(hashtagTree == NULL){
           printf("Couldn't allocate space for tree!");
       } else{
           hashtagTree->tweetIDs = CreateList();
           insertTweetID(hashtagTree->tweetIDs, tweetID);
           hashtagTree->hashtag = (char *) malloc(sizeof(char) * 20);
           strcpy(hashtagTree->hashtag, hashtag);
           hashtagTree->height = 0;
           hashtagTree->left = 0;
           hashtagTree->right = 0;
       }
   } else if (strcmp(hashtag, hashtagTree->hashtag) < 0){
       hashtagTree->left = insertHashtag(hashtagTree->left, hashtag, tweetID);
       if (treeHeight(hashtagTree->left) - treeHeight(hashtagTree->right) == 2){
           if(strcmp(hashtag, hashtagTree->left->hashtag) < 0){
               hashtagTree = singleRotateWithLeft(hashtagTree);
           } else{
               hashtagTree = doubleRotateWithLeft(hashtagTree);
           }
       }
   } else if(strcmp(hashtag, hashtagTree->hashtag) > 0){
       hashtagTree->right = insertHashtag(hashtagTree->right, hashtag, tweetID);
       if (treeHeight(hashtagTree->right) - treeHeight(hashtagTree->left) == 2){
           if(strcmp(hashtag, hashtagTree->right->hashtag) > 0){
               hashtagTree = singleRotateWithRight(hashtagTree);
           } else {
               hashtagTree = doubleRotateWithRight(hashtagTree);
           }
       }
   } else{
       insertTweetID(hashtagTree->tweetIDs, tweetID);
   }
    hashtagTree->height = treeHeight(hashtagTree);
    return hashtagTree;
}

// function to check for successful file opening
void fileError(FILE *file){
    if (file == NULL){
        printf("Could not open tweet file !");
        exit(1);
    }
}

// function to read tweets from the .txt file
AVLTree readTweetData(char *fileName){
    FILE *tweetsFile = fopen(fileName,"r+");
    fileError(tweetsFile);
    int i = 1;
    char tweet[160]; // max size of a tweet
    int size = 0;

    // count the number if tweets
    while(fgets(tweet, 160, tweetsFile)){
        size++;
    }

    // go to the beginning of the file
    fseek(tweetsFile, 0L, SEEK_SET);

    AVLTree hashtagTree = createTree();
    char delimiter[2] = " ";
    char *hashtag;
    while(fgets(tweet, 160, tweetsFile) && i <= size){
        // set the tweet to lower case
        strlwr(tweet);

        // remove new line from tweets
        if(tweet[strlen(tweet) - 1] == '\n'){
            tweet[strlen(tweet) - 1] = '\0';
        }

        if(i < 10){
            // remove the ANNOYING tab space after the tweet ID
            memmove(&tweet[1], &tweet[2], strlen(tweet) - 1);

            // get the first hashtag in a tweet
            hashtag = strtok(tweet, delimiter);

            if(hashtag[1] == '#' ){
                memmove(&hashtag[0], &hashtag[1], strlen(hashtag) - 0);
            }
        } else{
            // remove the ANNOYING tab space after the tweet ID
            memmove(&tweet[2], &tweet[3], strlen(tweet) - 1);

            // get the first hashtag in a tweet
            hashtag = strtok(tweet, delimiter);

            if(hashtag[2] == '#' ){
                memmove(&hashtag[0], &hashtag[2], strlen(hashtag) - 1);
            }
        }

        // get the other hashtags in the tweet
        while(hashtag != NULL){
            if(hashtag[0] == '#'){
                // remove ( ',' , '.', '"' ) from end of tweets
                if(hashtag[(strlen(hashtag)) - 1] >= 34 && hashtag[(strlen(hashtag)) - 1] <= 46){
                    hashtag[(strlen(hashtag)) - 1] = '\0';
                }
                if(hashtag[(strlen(hashtag)) - 2] >= 34 && hashtag[(strlen(hashtag)) - 2] <= 46){
                    hashtag[(strlen(hashtag)) - 2] = '\0';
                }
                if(hashtag[(strlen(hashtag)) - 1] >= 34 && hashtag[(strlen(hashtag)) - 1] <= 46){
                    hashtag[(strlen(hashtag)) - 1] = '\0';
                }
                memmove(&hashtag[0], &hashtag[1], strlen(hashtag) - 0);
                hashtagTree = insertHashtag(hashtagTree, hashtag, i);
            }
            hashtag = strtok(NULL, delimiter);
        }
        i++;
    }

    fclose(tweetsFile);
    return hashtagTree;
}

// function to show tweets in alphabetical order
void displayIndex(AVLTree hashtagTree){
    if (hashtagTree != NULL){
        displayIndex(hashtagTree->left);
        printf("%s ", hashtagTree->hashtag);
        displayTweetIDs(hashtagTree->tweetIDs);
        displayIndex(hashtagTree->right);
    }
}

// display's the most trending hashtags
void displayMostTrendingHastag(AVLTree hashtagTree){
    /*The complexity of my implementation is O(n) as I need to traverse every node in the tree
     * If I used a heap and used the number of times a hashtag appeared in the tweets as priority,
     * the the complexity may improve to O(1)
    */

    Stack stack = createStack();
    if (hashtagTree == NULL){
        printf("No tweets at this time!\n");
    } else{
        pushStack(hashtagTree, stack);
        int maxTweets = 0;
        // traverse the stack iteratively to find tweet
        while (!isEmpty(stack)){
            AVLTree tempTree = popStack(stack);
            if (tempTree->tweetIDs->size > maxTweets){
                maxTweets = tempTree->tweetIDs->size;
            }
            if (tempTree->left != NULL){
                pushStack(tempTree->left, stack);
            }
            if (tempTree->right != NULL){
                pushStack(tempTree->right, stack);
            }
        }
        // display the hashtag appearing in the most tweets
        pushStack(hashtagTree, stack);
        while (!isEmpty(stack)){
            AVLTree tempTree = popStack(stack);
            if (tempTree->tweetIDs->size == maxTweets){
                printf("%s ", tempTree->hashtag);
                displayTweetIDs(tempTree->tweetIDs);
            }
            if (tempTree->left != NULL){
                pushStack(tempTree->left, stack);
            }
            if (tempTree->right != NULL){
                pushStack(tempTree->right, stack);
            }
        }

    }
}

int main(int argc, char *argv[]) {

    int option = 1;
    char *fileName = (char *) malloc(sizeof(char) * 15);
    strcpy(fileName, argv[1]);

    AVLTree hashtagTree;
    hashtagTree = readTweetData(fileName);

    printf("Welcome to Hashtag Analysis at Twitter.\n");

    while(option){
        printf("\nMenu\n"
                       "1. Display the hashtag index\n"
                       "2. Display the most trending hashtag\n"
                       "3. Exit\n"
                       "Option: ");
        fflush(stdin);
        scanf("%d", &option);
        switch (option){
            case 1:
                printf("\nHashtag Index\n"
                               "---------------\n");
                displayIndex(hashtagTree);
                break;
            case 2:
                printf("\nMost Trending Hahshtags\n"
                               "---------------\n");
                displayMostTrendingHastag(hashtagTree);
                break;
            case 3:
                printf("Bye!\n");
                exit(1);
            default:
                printf("No such option!\n");
                break;
        }
    }
    return 0;
}
