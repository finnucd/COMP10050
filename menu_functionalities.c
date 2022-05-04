#include "menu_functionalities.h"
#include <stdio.h>
#include <stdlib.h>
//"display menu" displays menu to user
void display_menu(twitter *twitter_system, int current_user)  {
    printf("\nCurrent user is: %s\n", twitter_system->users[current_user].username);

    printf("Press 1 to follow another user\n"
           "Press 2 to unfollow another user\n"
           "Press 3 to post a tweet\n"
           "Press 4 to display the news feed\n"
           "Press 5 to switch users\n"
           "Press 6 to delete user\n"
           "Press 7 to end Twitter\n");
}
//"get menu input" takes a string as input, converts it to an int and returns this int
int get_menu_input()    {
    char *num_char = malloc(2);

    fgets(num_char, 2, stdin);
    getc(stdin);
    char *ptr;
    int input = strtol(num_char, &ptr, 10);
    return input;
}
void end_twitter()  {
    printf("Exiting the twitter system...\n");
    exit(0);
}
