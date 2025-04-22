#include <sqlite3.h>
#include "hestia.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *cmd = argv[1];
    validate_argument(argc, argv);
    _Bool is_valid_command = validate_argument(argc, argv);
    if (is_valid_command != 0)
    {
        fprintf(stderr, "invalid argument \"%s\" was supplied\n", cmd);
        print_help_message();
        return 1;
    }

    sqlite3 *db;
    char *err_msg;

    int rc = sqlite3_open("hestia.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "error opening db due to %s\n", sqlite3_errmsg(db));
    }

    char *query = "CREATE TABLE IF NOT EXISTS player(identifier INTEGER PRIMARY KEY, player_name TEXT)";

    rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "error opening db due to %s\n", sqlite3_errmsg(db));
    }

    if (strcmp(cmd, "play") != 0)
    {
        char *player_name;
        printf("Enter your name to begin:");
        scanf("%s", &player_name);
        play_game(&player_name, db);
    }

    else if ((strcmp("--leaderboard", cmd) || strcmp("-l", cmd)) != 0)
    {
        fetch_high_score();
    }
    else if (strcmp("--help", cmd))
    {
        print_help_message();
    }
}
