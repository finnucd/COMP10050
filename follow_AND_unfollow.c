#include <stdio.h>
#include <string.h>
#include "follow_AND_unfollow.h"
#include "delete_account.h"
#include <stdlib.h>

void follow(twitter *twitter_system, int current_user)    {
    //display users user currently does not follow
    if(twitter_system->users[current_user].num_following == MAX_FOLLOWING)   {
        printf("User %s already follows the max number of other users. You need to unfollow another user to follow a new user!\n",twitter_system->users[current_user].username);
    }
    else if(twitter_system->num_users == 1) {
        printf("User \"%s\" is the only user in the system.\nAdd at least one more user to follow someone\nReturning to menu...\n",
               twitter_system->users[current_user].username);
        return;
    }
    else if((twitter_system->users[current_user].num_following + 1) == twitter_system->num_users) {
        printf("User \"%s\" already follows all other users in the system\nReturning to menu...\n",twitter_system->users[current_user].username);
        return;
    }
    else    {
        printf("%s does not follow:\n", twitter_system->users[current_user].username);
        is_not_following(twitter_system, current_user);
    }
    //give user choice to decide which user he/she wants to follow and store in variable
    printf("Please enter username of user you want to follow.\n");

    char *user_choice_follow = get_user_input(USR_LENGTH);

    //make sure username provided is valid, meaning corresponding to an existing user and is not the username of the current user
    while(is_valid(twitter_system, user_choice_follow, current_user) != 0)   {
        //prompt user until valid username is provided
        user_choice_follow = get_user_input(USR_LENGTH);
    }
    //if username entered exists and is not username of current user: add to followers
    //store position in array of following to be filled in variable for readability
    int following_index = twitter_system->users[current_user].num_following;
    strcpy(twitter_system->users[current_user].following[following_index], user_choice_follow);
    //increment num following of current user
    twitter_system->users[current_user].num_following++;
    //update followers of user the current user just followed
    if(add_to_followers(twitter_system, current_user, twitter_system->users[current_user].following[following_index]) == 0) {
        printf("=====================\n");
        printf("%s now follows %s\n",twitter_system->users[current_user].username, twitter_system->users[current_user].following[following_index]);
        printf("=====================\n");
    }
    else    {
        printf("This user has already reached the maximum number of followers.\nReturning to menu...\n");
    }
}
void unfollow(twitter *twitter_system, int current_user)  {
    if(twitter_system->users[current_user].num_following == 0)  {
        printf("%s does not follow any users.\nReturning to menu...\n");
        return;
    }
    else    {
        //print list of all users current user is following
        is_following(twitter_system, current_user);
        //prompt user to provide name of person they wnat to unfollow
        printf("Please provide the username of the user you want to unfollow\n");
        char *user_choice_unfollow = get_user_input(USR_LENGTH);
        //re-prompt user in case user does not follow any other user with the entered username
        while(unfollow_user_validity_check(twitter_system, user_choice_unfollow, current_user) == -1)  {
            printf("The username you entered does not match any username of the users you currently follow.\nPlease enter a valid username.\n");
            user_choice_unfollow = get_user_input(USR_LENGTH);
        }
        //save index of user in following of current user in variable index
        int index = unfollow_user_validity_check(twitter_system, user_choice_unfollow, current_user);
        find_user_follower(twitter_system, current_user, index);
        //remove username from following
        find_user_following(twitter_system, twitter_system->users[current_user].following[index], current_user);
        //remove username from followers
        //decrement num following of current user
    }
}
void is_not_following(twitter *twitter_system, int user) {
    //check int is set to 0 if none of the followers match given user in outer for loop && user not himself
    int checkInt;
    for(size_t i = 0; i < twitter_system->num_users; i++)   {
        //loop through number of following of current user to see if there is a match with any of the users
        checkInt = 0;
        for(size_t j = 0; j < twitter_system->users[user].num_following; j++)   {
            //make sure user is not able to  follow him/herself & user does not already follow a given user
            if((strcmp(twitter_system->users[i].username, twitter_system->users[user].following[j]) == 0))
            {
                //if member j of following matches user i: set checkint to -1.
                checkInt = -1;
            }
        }
        if(checkInt == 0 && strcmp(twitter_system->users[i].username, twitter_system->users[user].username) != 0 )   {
            //if user i not in following, print username
            printf("--> %s\n", twitter_system->users[i].username);
        }
    }
}
void is_following(twitter *twitter_system, int user)    {
    if(twitter_system->users[user].num_following == 0)  {
        printf("User currently does not follow anyone\n");
        //6return;
    }

    for(int j = 0; j < twitter_system->num_users; j++)  {
        printf("user %i is following:\n", j);
        for(size_t i = 0; i < twitter_system->users[j].num_following; i++)   {
            printf("--> %s\n", twitter_system->users[j].following[i]);
        }
    }

    printf("Followers:\n");
    for(int i = 0; i < twitter_system->num_users; i++)  {
        for(int j = 0; j < twitter_system->users[i].num_followers; j++) {
            printf("User: %s  Follower %i: %s\n", twitter_system->users[i].username, j, twitter_system->users[i].followers[j]);
        }
        printf("\n");
    }
}
/*is_valid takes checks whether a given username exists in the system
next to the twitter_system struct, it takes the username whose existence is checked and t
*/
int is_valid(twitter *twitter_system, char *checkString, int current_user)   {
    for(size_t i = 0; i < twitter_system->num_users; i++)   {//loop through number of following of current user to see if there is a match with any of the users
        //it a match was found, determine whether user wants to a) follow him or herself; b) username is indeed valid
        if(strcmp(twitter_system->users[i].username, checkString) == 0) {
            //
            if(strcmp(twitter_system->users[current_user].username,checkString) == 0)   {
                printf("You cannot follow yourself.\nTry again!\n");
                return 1;
            }
            else   {
                return 0;
            }
        }
    }
    //return 1 in case username does not exist
    printf("username: \"%s\"does not exist. Please enter a valid username\n", checkString);
    return 2;
}
int unfollow_user_validity_check(twitter *twitter_system, char *checkUser, int current_user)    {
    for(int i = 0; i < twitter_system->users[current_user].num_following; i++)   {
        if(strcmp(twitter_system->users[current_user].following[i], checkUser) == 0)    {
            //if match is found return index of user
            return i;
        }
    }
    //if no match is found, return 1;
    return -1;
}
char *get_user_input(int size)   {

    char *user_choice_container = malloc(size);
    //7ar();
    //fgetc(stdin); //get leftover newline character for fgets to work
    fgets(user_choice_container, size, stdin);
    //make sure null terminating character is added; fgets could add newline if its read
    if(user_choice_container[strlen(user_choice_container)-1] == '\n') {
        user_choice_container[strlen(user_choice_container)-1] = '\0';
    }
    return user_choice_container;
}
int add_to_followers(twitter *twitter_system, int current_user, char *userCheck) {
    //search for user
    for (int i = 0; i < twitter_system->num_users; i++) {

        if (strcmp(twitter_system->users[i].username, userCheck) == 0) {
            if(twitter_system->users[i].num_followers < MAX_FOLLOWERS)    {
                //if number of followers is smaller than Max followers: add user to followers
                strcpy(twitter_system->users[i].followers[twitter_system->users[i].num_followers],twitter_system->users[current_user].username);
                twitter_system->users[i].num_followers++;
                return 0;
            }
            else    {
                //if number of followers already at max: return 1
                return 1;
            }
        }
    }
    printf("add to followers failed\n");
}
