

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "hestia.h"

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

int play(char *player_name)
{
    return 0;
}

void fetch_hight_score() {}

void print_hep_message() {}