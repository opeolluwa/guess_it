

#include <stdio.h>
#include "guess_it.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{

    sqlite3 *db;
    char *err_msg = NULL;
    char query[256];

    if (validate_argument(argc, argv) != 0)
    {
        fprintf(stderr, "Invalid argument \"%s\" was supplied\n", argv[1]);
        print_help_message();
        return 1;
    }

    if (sqlite3_open(GUESS_IT_DB_PATH, &db) != SQLITE_OK)
    {
        fprintf(stderr, "Error opening db: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sprintf(query,
            "CREATE TABLE IF NOT EXISTS %s ("
            "identifier INTEGER PRIMARY KEY, "
            "user_name TEXT, "
            "score INTEGER DEFAULT %d"
            ")",
            PLAYERS_TABLE_NAME, START_OUT_SCORE);

    if (sqlite3_exec(db, query, 0, 0, &err_msg) != SQLITE_OK)
    {
        fprintf(stderr, "Error creating table: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    const char *cmd = argv[1];
    switch (*cmd)
    {
    case "play":
        return play_game(db);
        break;

    case "--help":
        print_help_message();
        break;

    case "--leaderboard":
        fetch_high_score();
        break;
    default:
        print_help_message();
        break;
    }

    sqlite3_close(db);
    return 0;
}
