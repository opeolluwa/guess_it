

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "guess_it.h"
#include <sqlite3.h>

bool validate_argument(int argc, char *argv[])
{
    if (!(argc >= 2))
    {
        fprintf(stderr, "Invalid arguments length");
        return 1;
    }
    char *arg = argv[1];
    if (
        !strcmp(arg, "--help") &&
        !strcmp(arg, "-h") &&
        !strcmp(arg, "play") &&
        !strcmp(arg, "--leaderboard") &&
        !strcmp(arg, "-l"))
    {
        fprintf(stderr, "Invalid command. Use one of: \"--help\", \"-h\", \"play\", \"--leaderboard\", \"-l\"\n");
        printf("Got: %s\n", arg);
        return 1;
    }

    return 0;
}

int play_game(char *player_name, sqlite3 *db)
{
    return 0;
}

void fetch_high_score() {}

void print_help_message()
{
    char *help_msg = "Classical guess the number game\n\nUsage : guess_it [COMMAND]\n\nCommands:\nhelp — Print this message\nplay — Play the game\nleaderboard — See high scores\n";

    fprintf(stdout, "%s\n", help_msg);
}

bool user_name_exist(char *user_name[], sqlite3 *db) {}
int create_user(char *user_name[], sqlite3 *db)
{
    if(strcmp(user_name, "")==true){
        return 1;
    }

    const char *query =
}
Score fetch_user_score(char *user_name[], sqlite3 *db) {}
