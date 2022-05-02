#include "delete_account.h"
#include "twitter_create.h"
#include <stdio.h>
#include <string.h>

void delete_account(twitter *twitter_system, int current_user, new_tweet_PTR *headPtr)   {
    //find all users who follow the user to be deleted and delete that user from the list of following
    find_user_following(twitter_system, twitter_system->users[current_user].username);
    //if user to be deleted has posted any tweets: delete them
    if(twitter_system->users[current_user].num_tweets > 0)    {
        delete_tweets(headPtr, twitter_system->users[current_user].username);
    }
    //delete user from total user base
    delete_from_total(twitter_system, current_user);
}

void find_user_following(twitter  *twitter_system, char *user)    {
    for(size_t i = 0; i < twitter_system->num_users; i++)   {
        for(size_t j = 0; j < twitter_system->users[i].num_following; j++)  {
            if(strcmp(user, twitter_system->users[i].following[j]) == 0)    {

                remove_from_following(twitter_system, twitter_system->users[i].num_following, i, j);
                //decrement number of following
                twitter_system->users[i].num_following--;
            }
        }
    }
}
void remove_from_following(twitter *twitter_system, int size, int user, int del_user_index)  {
    for(int i = del_user_index; i < size; i++) {
        //move all users above user index one position down
        strcpy(twitter_system->users[user].following[i],twitter_system->users[user].following[i+1]);
    }
}
void delete_from_total(twitter *twitter_system, int delete_index)    {
    for(int i = delete_index; i < twitter_system->num_users-1; i++)   {
        twitter_system->users[i] = twitter_system->users[i+1];
    }
    printf("User deleted\n");
    twitter_system->num_users--;
}
void find_user_follower(twitter *twitter_system, int current_user, int unfollow_index)    {
    //search user that current user is unfollowing
    for(int i = 0; i < twitter_system->num_users; i++)  {
        if(strcmp(twitter_system->users[current_user].following[unfollow_index], twitter_system->users[i].username) == 0)   {
            //search for username of current user
            for(int j  = 0; j < twitter_system->users[i].num_followers; j++)    {
                //if current user is found in list of followers: set string to 0 and decrement number of followers
                if(strcmp(twitter_system->users[current_user].username, twitter_system->users[i].followers[j]) == 0)    {
                    remove_user_follower(twitter_system, twitter_system->users[i].num_followers, i, j);
                }
            }
            break;
        }
    }
}
void remove_user_follower(twitter *twitter_system, int size, int user, int index)  {
    printf("size: %i\n", size);
    if(index == size-1)   {   //if user to be removed from following at last position: set string to 0
        strcpy(twitter_system->users[user].followers[index], "\0");
    }
    else    {
        for(int i = index; i < size-1; i++)   {
            //move all users above user index one position down
            printf("test4 index: %i\n", i);
            strcpy(twitter_system->users[user].followers[i],twitter_system->users[user].followers[i+1]);
        }
    }
    //decrement num following for user
    twitter_system->users[user].num_followers--;
}