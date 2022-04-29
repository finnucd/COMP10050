#include "delete_account.h"
#include "twitter_create.h"
#include <stdio.h>
#include <string.h>

void delete_account(twitter *twitter_system, int current_user)   {
    //set username to 0
    delete_from_following(twitter_system, twitter_system->users[current_user].username);
    strcpy(twitter_system->users[current_user].username, "\0");
    delete_from_total(twitter_system, current_user);
    //delete tweets if user to be deleted has posted any
    /*
    if(twitter_system[current_user].num_tweets > 0)    {

    }
    */
    //decrement num users
}

//TODO:
/*
 * 1. set all values in struct to 0 //WHAT IS VALUE OF USER STRING THAT IS NOT INITIALIZED?
 * 2. if not the last user was deleted, move followers 1 position down && following--
 * 3. if user deleted not last user, move all users 1 position down && numusers--
 * 4. Delete tweets --> linked list && num tweets - tweets the person has posted
 */
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
    for(int i = delete_index; i < twitter_system->num_users; i++)   {
        for(int i = delete_index; i < twitter_system->num_users; i++)   {
            twitter_system->users[i] = twitter_system->users[i+1];
        }
    }
    twitter_system->num_users--;
}