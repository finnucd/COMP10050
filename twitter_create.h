#ifndef ASSIGNMENT_2___PROJECT_DIRECTORY_TWITTER_CREATE_H
#define ASSIGNMENT_2___PROJECT_DIRECTORY_TWITTER_CREATE_H
    #define TWEET_LENGTH 270
    #define USR_LENGTH 100
    #define MAX_FOLLOWERS 30
    #define MAX_FOLLOWING 30
    #define MAX_TWEETS 100
    #define MAX_USERS 100

    typedef struct tweet  {
        int id;
        char msg[TWEET_LENGTH];
        char user[USR_LENGTH];
    }tweet;

    struct linked_list_news_feed {
        struct tweet tweet;
        struct linked_list_news_feed *next_tweet;
    };
    typedef struct linked_list_news_feed new_tweet;
    typedef new_tweet *new_tweet_PTR;

    typedef struct user {
        char username[USR_LENGTH];
        char followers[MAX_FOLLOWERS][USR_LENGTH];
        int num_followers;
        char following[MAX_FOLLOWING][USR_LENGTH];
        int num_following;
        int num_tweets;
    }user;

    typedef struct twitter  {
        tweet news_feed[MAX_TWEETS];
        user users[MAX_USERS];
        int num_tweets;
        int num_users;
    } twitter;

    void create_twitter_system(twitter * twitter_system);
    int does_exist(twitter *twitter_system, char * check);
    void remove_newLine(twitter *twitter_system, int current);
#endif //ASSIGNMENT_2___PROJECT_DIRECTORY_TWITTER_CREATE_H


