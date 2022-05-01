#include "delete_account.h"
#include "twitter_create.h"
#include <stdio.h>
#include <string.h>

void delete_account(twitter *twitter_system, int current_user, new_tweet_PTR *headPtr)   {
    //set username to 0
    delete_from_following(twitter_system, twitter_system->users[current_user].username);
    if(twitter_system->users[current_user].num_tweets > 0)    {
        delete_tweets(headPtr, twitter_system->users[current_user].username);
    }
    delete_from_total(twitter_system, current_user);
    //delete tweets if user to be deleted has posted any


    //strcpy(twitter_system->users[current_user].username, "\0");
}

void delete_from_following(twitter  *twitter_system, char *user)    {
    for(size_t i = 0; i < twitter_system->num_users; i++)   {
        for(size_t j = 0; j < twitter_system->users[i].num_following; j++)  {
            if(strcmp(user, twitter_system->users[i].following[j]) == 0)    {
                strcpy(twitter_system->users[i].following[j], "\0");
                //call
                remove_user_following(twitter_system, twitter_system->users[i].num_following, i, j);
                //decrement number of following
                twitter_system->users[i].num_following--;
            }
        }
    }
}
void remove_user_following(twitter *twitter_system, int size, int user, int del_user_index)  {
    for(int i = del_user_index; i < size; i++) {
        //move all users above user index one position down
        strcpy(twitter_system->users[user].following[i],twitter_system->users[user].following[i+1]);
        //decrement number of users
    }
}
void delete_from_total(twitter *twitter_system, int delete_index)    {
    for(int i = delete_index; i < twitter_system->num_users-1; i++)   {
        twitter_system->users[i] = twitter_system->users[i+1];
    }
    printf("User deleted\n");
    twitter_system->num_users--;
}