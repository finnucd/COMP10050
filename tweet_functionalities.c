#include "tweet_functionalities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void post_tweet(twitter *twitter_system,new_tweet_PTR *headPtr, int current_user)    {
    //TODO: Conditionals
        //what happens if message length is over max length?
    if(twitter_system->num_tweets == MAX_TWEETS)    {
        printf("The maximum number of tweets (100) has been reached!\nReturning to menu...\n");
        return;
    }
    else    {
        new_tweet_PTR newTweetNode = malloc(sizeof(new_tweet));
        new_tweet_PTR currentPtr;
        printf("Type away, %s!\n",twitter_system->users[current_user].username);

        if(newTweetNode != NULL)    {
            //set tweet ide
            twitter_system->num_tweets++;
            newTweetNode->tweet.id = twitter_system->num_tweets;
            //copy tweet inputted by user
            strcpy(newTweetNode->tweet.msg, get_user_input(TWEET_LENGTH));
            //set username
            strcpy(newTweetNode->tweet.user, twitter_system->users[current_user].username);
            twitter_system->users[current_user].num_tweets++;
            //new node points to null
            newTweetNode->next_tweet = NULL;

            currentPtr = newTweetNode;
            currentPtr->next_tweet = *headPtr;
            *headPtr = currentPtr;
        }
        else    {
            printf("There is no memory available to store the new node\n");
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
        while(traverse != NULL && tweet_counter < 11)    {
            //store resulting index if author of current tweet matches one of the usernames the current user is following
            following_index = unfollow_user_validity_check(twitter_system, traverse->tweet.user, current_user);
            //condition specifies whether current tweet is either authored by user him/herself or by any of the users he/she is following
            if(strcmp(traverse->tweet.user,twitter_system->users[current_user].username) == 0 || following_index != -1) {
                //print tweet & author
                printf("User: %s\n", traverse->tweet.user);
                printf("Tweet:\n%s\n",traverse->tweet.msg);
                //increment tweet_counter
                tweet_counter++;
            }
            //move to next tweet
            traverse = traverse->next_tweet;
        }
    }
}
