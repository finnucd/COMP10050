#include "twitter_create.h"
#include <stdio.h>
#include <string.h>

void create_twitter_system(twitter * twitter_system)    {
    //TODO: Does user already exist?
    twitter_system->num_users = 0;
    twitter_system->num_tweets = 0;

    for(size_t i = 0; i < MAX_USERS; i++)   {
        printf("Input the Username of user %i or press x to terminate\n", i+1);
        fgets(twitter_system->users[i].username, USR_LENGTH, stdin); //read in username

        if(twitter_system->users[i].username[strlen(twitter_system->users[i].username)-1] == '\n') { //make sure null terminating character is added; fgets could add newline if its read
            twitter_system->users[i].username[strlen(twitter_system->users[i].username)-1] = '\0';
        }
        if(strcmp(twitter_system->users[i].username, "x") == 0)    { //TODO: x is still added as user!
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
