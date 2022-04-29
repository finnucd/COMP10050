#include <stdio.h>
#include <string.h>
#include "follow_AND_unfollow.h"
#include <stdlib.h>

void follow(twitter *twitter_system, int current_user)    {
    //display users user currently does not follow
    if(twitter_system->users[current_user].num_following == MAX_FOLLOWING)   {
        printf("User %s already follows the max number of other users. You need to unfollow another user to follow a new user!\n",twitter_system->users[current_user].username);
    }
    else if(twitter_system->num_users == 1) {
        printf("User \"%s\" is the only user in the system.\nAdd at least one more user to follow someone\nReturning to menu...\n",
               twitter_system->users[current_user].username);
        getchar();
        return;
    }
    else    {
        printf("%s does not follow:\n", twitter_system->users[current_user].username);
        is_not_following(twitter_system, current_user);
        printf("Please input the name of the user you want to follow:\n");
    }
    //give user choice to decide which user he/she wants to follow and store in variable
    //make code below conditional upon there being more than 1 user in the system
    printf("Please enter username of user you want to follow.\n");
    char *user_choice_follow = get_user_input(USR_LENGTH);
    //make sure user cannot follow him or herself
    //make sure username provided is valid, meaning corresponding to an existing user and is not the username of the current user
    while(is_valid(twitter_system, user_choice_follow) == 1)   {//TODO: check here is user typed himself in!
        //prompt user until valid username is provided
        printf("username: \"%s\"does not exist. Please enter a valid username\n", user_choice_follow);
        user_choice_follow = get_user_input(USR_LENGTH);
    }
    //if username entered exists: add to followers
    int next_slot = twitter_system->users[current_user].num_following;
    strcpy(twitter_system->users[current_user].following[next_slot], user_choice_follow);
    //increment num following of current user
    twitter_system->users[current_user].num_following++;
    printf("%s now follows %s\n", twitter_system->users[current_user].username, twitter_system->users[current_user].following[next_slot]);
}
void unfollow(twitter *twitter_system, int current_user)  {
    if(twitter_system->users[current_user].num_following == 0)  {
        printf("%s does not follow any users.\n");
        return;
    }
    else    {
        //prompt user to provide name of person they wnat to unfollow
        printf("Please provide the username of the user you want to unfollow\n");
        char *user_choice_following = get_user_input(USR_LENGTH);
        //re-prompt user in case user does not follow any other user with the entered username
        while(unfollow_user_validity_check(twitter_system, user_choice_following, current_user) == -1)  {
            printf("The username you entered does not match any username of the users you currently follow.\nPlease enter a valid username.\n");
            user_choice_following = get_user_input(USR_LENGTH);
        }
        size_t index = unfollow_user_validity_check(twitter_system, user_choice_following, current_user);
        //set string of matching user to null == unfollowing user
        strcpy(twitter_system->users[current_user].following[index], "\0");
        //decrement num following of current user
        twitter_system->users[current_user].num_following--;
    }

    if(twitter_system->users[current_user].num_following == 0)  {
        printf("user is following no one");
    }
    else    {
        is_following(twitter_system, current_user);
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
    for(size_t i = 0; i < twitter_system->users[user].num_following; i++)   {

        printf("--> %s\n", twitter_system->users[user].following[i]);
    }
}
/*is_valid takes checks whether a given username exists in the system
next to the twitter_system struct, it takes the username whose existence is checked
*/
int is_valid(twitter *twitter_system, char *checkString)   {
    for(size_t i = 0; i < MAX_FOLLOWING; i++)   {//loop through number of following of current user to see if there is a match with any of the users
        if(strcmp(twitter_system->users[i].username, checkString) == 0) {
            //return 0 to indicate a match was found
            return 0;
        }
    }
    //return 1 in case username does not exist
    return 1;
}
int unfollow_user_validity_check(twitter *twitter_system, char *checkUser, int current_user)    {
    for(size_t i = 0; i < twitter_system->users[current_user].num_following; i++)   {
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
    //getchar();
    fgetc(stdin); //get leftover newline character for fgets to work
    fgets(user_choice_container, size, stdin);
    //make sure null terminating character is added; fgets could add newline if its read
    if(user_choice_container[strlen(user_choice_container)-1] == '\n') {
        user_choice_container[strlen(user_choice_container)-1] = '\0';
    }
    return user_choice_container;
}