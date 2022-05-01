#include "twitter_create.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void create_twitter_system(twitter * twitter_system)    {
    twitter_system->num_users = 0;
    twitter_system->num_tweets = 0;

    for(int i = 0; i < MAX_USERS; i++)   {
        printf("Input the Username of user %i or press \"x\" to terminate\n", i+1);
        fgets(twitter_system->users[i].username, USR_LENGTH, stdin);
        remove_newLine(twitter_system, i);

        while((does_exist(twitter_system, twitter_system->users[i].username) == 1) && (strcmp(twitter_system->users[i].username, "x") != 0))   {
            printf("The username does already exist. Please try again\n");
            fgets(twitter_system->users[i].username, USR_LENGTH, stdin);
            remove_newLine(twitter_system, i);
        }

        if(strcmp(twitter_system->users[i].username, "x") == 0) {
            //strcpy(twitter_system->users[i].username, "\0");
            break;
        }
        //set number of followers to 0
        twitter_system->users[i].num_followers = 0;
        //set number of following to 0
        twitter_system->users[i].num_following = 0;
        //set tweets to 0;
        twitter_system->users[i].num_tweets = 0;
        //increment number of users (num_users) in struct used for representing twitter system
        twitter_system->num_users++;
    }
    printf("Twitter created!\n");
}
int does_exist(twitter *twitter_system, char * checkUser)   {
    for(int i =  0; i  < twitter_system->num_users; i++)    {
        if(strcmp(twitter_system->users[i].username, checkUser) == 0)    {
            return 1;
        }
    }
    return 0;
}
void remove_newLine(twitter *twitter_system, int current_user)    {
    if(twitter_system->users[current_user].username[strlen(twitter_system->users[current_user].username)-1] == '\n') { //make sure null terminating character is added; fgets could add newline if its read
        twitter_system->users[current_user].username[strlen(twitter_system->users[current_user].username)-1] = '\0';
    }
}