#ifndef MAIN_C_TWEET_FUNCTIONALITIES_H
#define MAIN_C_TWEET_FUNCTIONALITIES_H
#include  "twitter_create.h"
#include "follow_AND_unfollow.h"
void post_tweet(twitter *twitter_system, new_tweet_PTR *head, int current_user);
void get_news_feed(twitter *twitter_system, new_tweet_PTR *head, int current_user);
int index_of_following(twitter *twitter_system, int current_user, char* username);
#endif //MAIN_C_TWEET_FUNCTIONALITIES_H
