

#include <stdio.h>
#include "guess_it.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (validate_argument(argc, argv) != 0)
    {
        fprintf(stderr, "Invalid argument \"%s\" was supplied\n", argv[1]);
        print_help_message();
        return 1;
    }

    sqlite3 *db;
    char *err_msg = NULL;

    if (sqlite3_open(GUESS_IT_DB_PATH, &db) != SQLITE_OK)
    {
        fprintf(stderr, "Error opening db: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *query = "CREATE TABLE IF NOT EXISTS player(identifier INTEGER PRIMARY KEY, user_name TEXT)";
    if (sqlite3_exec(db, query, 0, 0, &err_msg) != SQLITE_OK)
    {
        fprintf(stderr, "Error creating table: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    const char *cmd = argv[1];

    if (strcmp(cmd, "play") == 0)
    {
        char user_name[100];
        printf("Enter your name to begin: ");
        scanf("%99s", user_name);
        return play_game(user_name, db);
    }
    else if (strcmp(cmd, "--leaderboard") == 0 || strcmp(cmd, "-l") == 0)
    {
        fetch_high_score();
    }
    else if (strcmp(cmd, "--help") == 0 || strcmp(cmd, "-h") == 0)
    {
        print_help_message();
    }

    sqlite3_close(db);
    return 0;
}
