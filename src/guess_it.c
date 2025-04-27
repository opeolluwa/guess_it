

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "guess_it.h"
#include <sqlite3.h>

_Bool validate_argument(int argc, char *argv[])
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
    char *help_msg = "Classical guess the number game\nUsage : hestia [COMMAND\nCommands :\n--help | -h\t\tprint this message\nplay \t\tplay the game\n--leaderboard | -l\t\tsee high scores";

    fprintf(stdout, "%s\n", help_msg);
}