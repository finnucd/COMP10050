#ifndef MAIN_C_DELETE_ACCOUNT_H
#define MAIN_C_DELETE_ACCOUNT_H
#include "twitter_create.h"
#include "tweet_functionalities.h"
void delete_account(twitter *twitter_system, int user, new_tweet_PTR *headPtr);
void delete_from_following(twitter  *twitter_system, char *user);
void remove_user_following(twitter *twitter_system, int size, int user, int del_user_index);
void delete_from_total(twitter *twitter_system, int delete_index);
#endif //MAIN_C_DELETE_ACCOUNT_H
