#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include "follow_AND_unfollow.h"
#include "menu_functionalities.h"
#include "tweet_functionalities.h"
#include "delete_account.h"
int main() {

    twitter twitter_system;
    // function checks whether username is already used?
    //TODO: while loop encapsulating "create twitter system" prompting user as long as at least one user is entered
    create_twitter_system(&twitter_system);

    for(int i = 0; i < twitter_system.num_users; i++)   {
        user usr = twitter_system.users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers );
    }
    //headPtr for linked list representing news feed
    new_tweet_PTR headPtr = NULL;

    //display menu with possibilities
    //give user possibility to select a given user // ask liliane
    int user_choice = 0;
    int current_user = 0;
    while(user_choice != -1 && twitter_system.num_users >= 1) {
        if (current_user <= twitter_system.num_users) {
            display_menu(&twitter_system, current_user);
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
                    current_user++;
                    break;
                case 6:
                    current_user--;
                    break;
                case 7:
                    is_following(&twitter_system, current_user);
                    break;
                case 8:
                    delete_account(&twitter_system, current_user, &headPtr);
                    //revert to user who came before deleted user
                    if(current_user != 0) {
                        current_user--;
                    }
                    if(twitter_system.num_users == 0)    {
                        printf("There are no users in the system.\n");
                        end_twitter();
                    }
                    break;
                default:
                    end_twitter();
                    break;
                    //TODO: default statment is executed if only 1 user is entered and follow() returning --> getchar fixes this
                    //
                    //break;
            }
        }
    }

    //follow(&twitter_system, current_user);
    //unfollow(&twitter_system, current_user);
    return 0;
}