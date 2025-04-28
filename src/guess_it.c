
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

int play_game(char *user_name, sqlite3 *db)
{
    if (user_name_exist(user_name, db))
    {
        fprintf(stderr, "Username %s already exists", user_name);
        return 1;
    }
    return 0;
}

void fetch_high_score() {}

void print_help_message()
{
    char *help_msg = "Classical guess the number game\n\nUsage : guess_it [COMMAND]\n\nCommands:\nhelp — Print this message\nplay — Play the game\nleaderboard — See high scores\n";

    fprintf(stdout, "%s\n", help_msg);
}

bool user_name_exist(char *user_name, sqlite3 *db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1 FROM " GUESS_IT_DB_NAME " WHERE user_name = ?";
    int rc;
    bool exists = false;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_text(stmt, 1, user_name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        exists = true;
    }

    sqlite3_finalize(stmt);
    return exists;
}

int create_user(char *user_name, sqlite3 *db)
{
    if (!user_name)
    {
        fprintf(stderr, "Username is required");
        return 1;
    }

    const char *sql = "INSERT INTO " GUESS_IT_DB_NAME "(user_name) VALUES (?)";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare INSERT statement: %s\n", sqlite3_errmsg(db));
        return 2;
    }

    sqlite3_bind_text(stmt, 1, user_name, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 3;
    }

    sqlite3_finalize(stmt);
    return 0;
}
struct Score fetch_user_score(char *user_name, sqlite3 *db) {}
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    return 0;
}