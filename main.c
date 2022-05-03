#include <stdio.h>
#include "twitter_create.h"
#include "follow_AND_unfollow.h"
#include "menu_functionalities.h"
#include "tweet_functionalities.h"
#include "delete_account.h"
int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    for(int i = 0; i < twitter_system.num_users; i++)   {
        user usr = twitter_system.users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers );
    }
    //headPtr for linked list representing news feed
    new_tweet_PTR headPtr = NULL;
    int user_choice = 0;
    int current_user = 0;
    while(user_choice != -1 && twitter_system.num_users >= 1) {
        if (current_user <= twitter_system.num_users) {
            display_menu(&twitter_system, current_user);
            //save user input in variable user_choice and use it to control switch statement
            user_choice = get_menu_input();

            switch (user_choice) {
                case 1:
                    follow(&twitter_system, current_user);
                    break;
                case 2:
                    unfollow(&twitter_system, current_user);
                    break;
                case 3:
                    post_tweet(&twitter_system, &headPtr, current_user);
                    break;
                case 4:
                    get_news_feed(&twitter_system, &headPtr, current_user);
                    break;
                case 5:
                    //as long as current_user is smaller than total num users: switch to next user
                    if(current_user + 1 < twitter_system.num_users)    {
                        current_user++;
                    }
                    else    {
                        printf("This is the  last user.\n");
                    }
                    break;
                case 6:
                    current_user--;
                    break;
                case 7:
                    is_following(&twitter_system, current_user);
                    break;
                case 8:
                    //delete user
                    delete_account(&twitter_system, current_user, &headPtr);
                    //revert to user who came before deleted user
                    if(current_user != 0) {
                        current_user--;
                    }
                    //if user deleted was last user in system: end program
                    if(twitter_system.num_users == 0)    {
                        printf("There are no users in the system.\n");
                        end_twitter();
                    }
                    break;
                default:
                    end_twitter();
                    break;
            }
        }
    }
    return 0;
}