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
        play_game("d");
    }
    else if ((strcmp("--leaderboard", cmd) || strcmp("-l", cmd)) != 0)
    {
        fetch_high_score();
    }
    else
    {
        print_help_message();
    }
}
