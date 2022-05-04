#include "delete_account.h"
#include "twitter_create.h"
#include <stdio.h>
#include <string.h>

void delete_account(twitter *twitter_system, int delete_user, new_tweet_PTR *headPtr)   {
    //loop through all users in the system
    for(int i = 0; i < twitter_system->num_users; i++)  {
        //variable "a" stores index of user i, IF user to be deleted follows user i
        int a = unfollow_user_validity_check(twitter_system, twitter_system->users[i].username, delete_user);
        //the index stored in a is then used to remove the user to be deleted from the list of followers of user i
        find_user_follower(twitter_system, delete_user,a);
        //remove user to be deleted from list of following of user  i
        find_user_following(twitter_system, twitter_system->users[delete_user].username, i);
    }
    //if user to be deleted has posted any tweets: delete them
    if(twitter_system->users[delete_user].num_tweets > 0)    {
        delete_tweets(headPtr, twitter_system->users[delete_user].username);
    }
    //delete user from total user base
    delete_from_total(twitter_system, delete_user);
}
//"find_user_following" searches through following of current user and, calls "remove_from_following" in case a match with string "user" is found
void find_user_following(twitter *twitter_system, char *user, int current_user)    {
        for(size_t j = 0; j < twitter_system->users[current_user].num_following; j++)  {
            if(strcmp(user, twitter_system->users[current_user].following[j]) == 0)    {
                //if match is found: remove user from following of current_user
                remove_from_following(twitter_system, twitter_system->users[current_user].num_following, current_user, j);
                //decrement number of following
                twitter_system->users[current_user].num_following--;
                break;
            }
        }
}
//"remove_from_following" moves users in following of user down, starting from the index of the user to be deleted in following
void remove_from_following(twitter *twitter_system, int size, int user, int del_user_index)  {
    for(int i = del_user_index; i < size; i++) {
        //move all users above user index one position down
        strcpy(twitter_system->users[user].following[i],twitter_system->users[user].following[i+1]);
    }
}
//"find_user_follower" calls "remove user follower" if "goal user" appears in the list followers of user i
void find_user_follower(twitter *twitter_system, int goalUser, int unfollow_index)    {
    //search user that current user is unfollowing
    for(int i = 0; i < twitter_system->num_users; i++)  {
        if(strcmp(twitter_system->users[goalUser].following[unfollow_index], twitter_system->users[i].username) == 0)   {
            //search for username of current user
            for(int j  = 0; j < twitter_system->users[i].num_followers; j++)    {
                //if current user is found in list of followers: delete current user from followers
                if(strcmp(twitter_system->users[goalUser].username, twitter_system->users[i].followers[j]) == 0)    {
                    //remove follower j from user i´s list of followers
                    remove_user_follower(twitter_system, twitter_system->users[i].num_followers, i, j);
                }
            }
            break;
        }
    }
}
//"remove_user_follower" removes user at "index" from followers of "user"
void remove_user_follower(twitter *twitter_system, int size, int user, int index)  {
    if(index == size-1)   {   //if user to be removed from followers at last position: set string to 0
        strcpy(twitter_system->users[user].followers[index], "\0");
    }
    else    {
        for(int i = index; i < size-1; i++)   {
            //move all users above user index one position down
            strcpy(twitter_system->users[user].followers[i],twitter_system->users[user].followers[i+1]);
        }
    }
    //decrement num following for user
    twitter_system->users[user].num_followers--;
}
//"delete_from_total" deletes user at "delete index" from users in system
void delete_from_total(twitter *twitter_system, int delete_index)    {
    for(int i = delete_index; i < twitter_system->num_users-1; i++)   {
        twitter_system->users[i] = twitter_system->users[i+1];
    }
    printf("User deleted\n");
    twitter_system->num_users--;
}