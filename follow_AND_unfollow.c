#include <stdio.h>
#include <string.h>
#include "follow_AND_unfollow.h"
#include "delete_account.h"
#include <stdlib.h>

void follow(twitter *twitter_system, int current_user)    {

    if(twitter_system->users[current_user].num_following == MAX_FOLLOWING)   {
        printf("User \"%s\" already follows the max number of other users. You need to unfollow another user to follow a new user!\n"
               "Returning to menu...\n",twitter_system->users[current_user].username);
        return;
    }
    else if(twitter_system->num_users == 1) {
        printf("User \"%s\" is the only user in the system.\nAdd at least one more user to follow someone\nReturning to menu...\n",
               twitter_system->users[current_user].username);
        return;
    }
    else if((twitter_system->users[current_user].num_following + 1) == twitter_system->num_users) {
        printf("User \"%s\" already follows all other users in the system\nReturning to menu...\n",
               twitter_system->users[current_user].username);
        return;
    }
    else    {//display users user currently does not follow
        printf("%s does not follow:\n", twitter_system->users[current_user].username);
        is_not_following(twitter_system, current_user);
    }

    printf("Please enter username of user you want to follow.\n");
    //give user choice to decide which user he/she wants to follow and store in variable "user_choice_follow"
    char *user_choice_follow = get_user_input(USR_LENGTH);

    //prompt user until username provided is valid, meaning corresponding to an existing user and is not the username of the current user
    while(is_valid(twitter_system, user_choice_follow, current_user) != 0)   {
        user_choice_follow = get_user_input(USR_LENGTH);
    }
    //if username entered exists and is not username of current user: add current user to followers of user current user now follows
    //store index of user current user wants to follow in following_index (used later to add current user to followers of user current user wants to follow)
    int following_index = twitter_system->users[current_user].num_following;
    //store user current user wants to follow in following of current user
    strcpy(twitter_system->users[current_user].following[following_index], user_choice_follow);
    //increment num following of current user
    twitter_system->users[current_user].num_following++;
    //update followers of user the current user just followed IF not max number of followers have been reached
    if(add_to_followers(twitter_system, current_user, twitter_system->users[current_user].following[following_index]) == 0) {
        printf("=====================\n");
        printf("%s now follows %s\n",twitter_system->users[current_user].username, twitter_system->users[current_user].following[following_index]);
        printf("=====================\n");
    }
    else    {
        printf("The user you are trying to follow has already reached the maximum number of followers.\nReturning to menu...\n");
    }
}
void unfollow(twitter *twitter_system, int current_user)  {
    if(twitter_system->users[current_user].num_following == 0)  {
        printf("\"%s\" does not follow any users.\nReturning to menu...\n", twitter_system->users[current_user].username);
        return;
    }
    else    {
        //print list of all users current user is following
        is_following(twitter_system, current_user);
        //prompt user to provide name of person they want to unfollow
        printf("Please provide the username of the user you want to unfollow\n");
        //store username of user current user wants to unfollow in variable user_choice_follow
        char *user_choice_unfollow = get_user_input(USR_LENGTH);
        //re-prompt user in case user does not follow any other user with the entered username
        while(unfollow_user_validity_check(twitter_system, user_choice_unfollow, current_user) == -1)  {
            printf("The username you entered does not match any username of the users you currently follow.\nPlease enter a valid username.\n");
            user_choice_unfollow = get_user_input(USR_LENGTH);
        }
        //save index in following of current user of user current user wants to unfollow in variable "index"
        int index = unfollow_user_validity_check(twitter_system, user_choice_unfollow, current_user);
        //remove current user from list of followers of user current user is unfollowing
        find_user_follower(twitter_system, current_user, index);
        //remove username from following of current user
        find_user_following(twitter_system, twitter_system->users[current_user].following[index], current_user);
    }
}
//"is not following" prints usernames of users "user" is not following
void is_not_following(twitter *twitter_system, int user) {

    int checkInt;
    //loop through all users
    for(size_t i = 0; i < twitter_system->num_users; i++)   {

        checkInt = 0;
        //for each user in the system: loop through number of following of current user to see if there is a match
        for(size_t j = 0; j < twitter_system->users[user].num_following; j++)   {
            //make sure user is not able to  follow him/herself & user does not already follow a given user
            if((strcmp(twitter_system->users[i].username, twitter_system->users[user].following[j]) == 0))
            {
                //if member j of following matches user i: set checkint to -1.
                checkInt = -1;
            }
        }
        //if user i not in following, print username
        if(checkInt == 0 && strcmp(twitter_system->users[i].username, twitter_system->users[user].username) != 0 )   {

            printf("--> %s\n", twitter_system->users[i].username);
        }
    }
}
//is following prints usernames of user(s) current user is following
void is_following(twitter *twitter_system, int user)    {
    if(twitter_system->users[user].num_following == 0)  {
        printf("User currently does not follow anyone\n");
        return;
    }
    printf("User \"%s\" is following:\n", twitter_system->users[user].username);
    for(size_t i = 0; i < twitter_system->users[user].num_following; i++)   {
        printf("--> %s\n", twitter_system->users[user].following[i]);
    }
}
//is_valid takes checks whether a given username already exists in the system
int is_valid(twitter *twitter_system, char *checkString, int current_user)   {

    for(size_t i = 0; i < twitter_system->num_users; i++)   {

        if(strcmp(twitter_system->users[i].username, checkString) == 0) {
            //if the current user tries to follow him/herself: print message and return error code to follow
            if(strcmp(twitter_system->users[current_user].username,checkString) == 0)   {
                printf("You cannot follow yourself.\nTry again!\n");
                return 1;
            }
            else   {
                return 0;
            }
        }
    }
    //return 1 in case username entered does not exist
    printf("username: \"%s\"does not exist. Please enter a valid username\n", checkString);
    return 1;
}
//unfollow_user_validity_check compares the current users´s followers against a string
//and returns index in user following if match is found
int unfollow_user_validity_check(twitter *twitter_system, char *checkUser, int current_user)    {
    for(int i = 0; i < twitter_system->users[current_user].num_following; i++)   {
        if(strcmp(twitter_system->users[current_user].following[i], checkUser) == 0)    {
            //if match is found return index of user
            return i;
        }
    }
    //if no match is found, return -1;
    return -1;
}
//function "get_user_input" gets user input and returns it as a string
char *get_user_input(int size)   {

    char *user_choice_container = malloc(size);
    fgets(user_choice_container, size, stdin);
    //make sure null terminating character is added; fgets could add newline if its read
    if(user_choice_container[strlen(user_choice_container)-1] == '\n') {
        user_choice_container[strlen(user_choice_container)-1] = '\0';
    }
    return user_choice_container;
}
//"add_to_followers" adds user who just followed another user (say user x) to followers of user x
int add_to_followers(twitter *twitter_system, int current_user, char *userCheck) {
    //search for user in twitter system
    for (int i = 0; i < twitter_system->num_users; i++) {
        //if user i´s name matches the username of user current_user just followed: add current user to followers of user i
        if (strcmp(twitter_system->users[i].username, userCheck) == 0) {
            if(twitter_system->users[i].num_followers < MAX_FOLLOWERS)    {
                //if number of followers is smaller than Max followers: add user to followers
                strcpy(twitter_system->users[i].followers[twitter_system->users[i].num_followers],twitter_system->users[current_user].username);
                twitter_system->users[i].num_followers++;
                return 0;
            }
            else    {
                //if number of followers of user ialready at max: return 1
                return 1;
            }
        }
    }
}
