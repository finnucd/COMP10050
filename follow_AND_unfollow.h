#ifndef ASSIGNMENT_2___PROJECT_DIRECTORY_FOLLOW_AND_UNFOLLOW_H
#define ASSIGNMENT_2___PROJECT_DIRECTORY_FOLLOW_AND_UNFOLLOW_H
#include "twitter_create.h"

#include <stdio.h>
    void follow(twitter *twitter_system, int current_user);
    void is_not_following(twitter *twitter_system, int user);
    void is_following(twitter *twitter_system, int user);
    int is_valid(twitter *twitter_system, char *check, int current_user);
    void unfollow(twitter *twitter_system, int user);
    int unfollow_user_validity_check(twitter *twitter_system, char *checkUser, int current_user);
    char* get_user_input(int size);
    void update_followers(twitter *twitter_system, int current_user, char *user);
#endif //ASSIGNMENT_2___PROJECT_DIRECTORY_FOLLOW_AND_UNFOLLOW_H


