#ifndef MAIN_C_DELETE_ACCOUNT_H
#define MAIN_C_DELETE_ACCOUNT_H
#include "twitter_create.h"
#include "tweet_functionalities.h"
void delete_account(twitter *twitter_system, int user, new_tweet_PTR *headPtr);
void find_user_following(twitter  *twitter_system, char *user, int current);
void remove_from_following(twitter *twitter_system, int size, int user, int del_user_index);
void delete_from_total(twitter *twitter_system, int delete_index);
void find_user_follower(twitter *twitter_system, int current_user, int index);
void remove_user_follower(twitter *twitter_system, int size, int user, int index);

#endif //MAIN_C_DELETE_ACCOUNT_H
