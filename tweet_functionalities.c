#include "tweet_functionalities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void post_tweet(twitter *twitter_system,new_tweet_PTR *headPtr, int current_user)    {

    if(twitter_system->num_tweets == MAX_TWEETS)    {
        printf("The maximum number of tweets (100) has been reached!\nReturning to menu...\n");
        return;
    }
    else    {
        //allocate memory for new tweet
        new_tweet_PTR newTweetNode = malloc(sizeof(new_tweet));
        new_tweet_PTR currentPtr;
        printf("Type away, %s!\n",twitter_system->users[current_user].username);
        //if memory was successfully allocated: add new tweet
        if(newTweetNode != NULL)    {
            //set tweet ID
            twitter_system->num_tweets++;
            newTweetNode->tweet.id = twitter_system->num_tweets;
            //copy tweet inputted by user
            strcpy(newTweetNode->tweet.msg, get_user_input(TWEET_LENGTH));
            //set username of tweet
            strcpy(newTweetNode->tweet.user, twitter_system->users[current_user].username);
            //increment number of tweets of given user
            twitter_system->users[current_user].num_tweets++;
            //new node points to null
            newTweetNode->next_tweet = NULL;

            //set new tweet as head pointer
            currentPtr = newTweetNode;
            currentPtr->next_tweet = *headPtr;
            *headPtr = currentPtr;
        }
        else    {
            printf("There is no memory available to store the new tweet\n");
            return;
        }
    }
}
void get_news_feed(twitter *twitter_system, new_tweet_PTR *headPtr, int current_user) {
    if(twitter_system->num_tweets == 0) {
        printf("No tweets have been posted yet.\nReturning to menu...\n");
        return;
    }
    else    {
        new_tweet_PTR traverse = *headPtr;
        //tweet_counter counts number of tweets user or users user follows have been found
        int tweet_counter = 0;
        int following_index;
        while(traverse != NULL && tweet_counter < 10)    {
            //store resulting index if author of current tweet matches one of the usernames the current user is following
            following_index = unfollow_user_validity_check(twitter_system, traverse->tweet.user, current_user);
            //condition specifies whether current tweet is either authored by user him/herself or by any of the users he/she is following
            if(strcmp(traverse->tweet.user,twitter_system->users[current_user].username) == 0 || following_index != -1) {
                //print tweet & author
                printf("User: %s\n", traverse->tweet.user);
                printf("Tweet:\n%s\n",traverse->tweet.msg);
                printf("__________________________________________________________\n");
                //increment tweet_counter
                tweet_counter++;
            }
            //move to next tweet
            traverse = traverse->next_tweet;
        }
        printf("__________________________________________________________\n");
    }
}
//function "delete tweets" deletes tweets of user who has been deleted
void delete_tweets(new_tweet_PTR *headPtr, char *deleted_user)  {
    new_tweet_PTR prev = NULL;
    new_tweet_PTR curr = *headPtr;

    while((curr != NULL) ) {

        if(strcmp(curr->tweet.user, deleted_user) == 0) {
            //if tweet authored by deleted user is the head pointer: delete tweet and set new head pointer
            if(strcmp((*headPtr)->tweet.user, deleted_user) == 0) {
                new_tweet_PTR temp = *headPtr;
                (*headPtr) = (*headPtr)->next_tweet;
                free(temp);
                curr = *headPtr;
            }
            else    {
                //delete tweet and relink list
                new_tweet_PTR temp = curr;
                prev->next_tweet = curr->next_tweet;
                curr = curr->next_tweet;
                free(temp);
            }
        }
        else   {//if tweet wasn't authored by deleted user: continue traversing the list
            prev = curr;
            curr = curr->next_tweet;
        }
    }
}