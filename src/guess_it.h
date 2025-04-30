#define PLAYERS_TABLE_NAME "playerS"
#define GUESS_IT_DB_PATH "guess_it.db"
#define START_OUT_SCORE 500

#include <sqlite3.h>
#include <stdbool.h>

#ifndef GUESS_IT_VALIDATORS
#define GUESS_IT_VALIDATORS
bool validate_argument(int argc, char *argv[]);
int play_game(sqlite3 *db);
void fetch_high_score();
void print_help_message();
#endif

#ifndef GUESS_IT_DB_API
#define GUESS_IT_BD_API
struct Score
{
    unsigned long int score;
    char *user_name[];
};
bool user_name_exist(char *user_name, sqlite3 *db);
int create_user(char *user_name, sqlite3 *db);
struct Score fetch_user_score(char *user_name, sqlite3 *db);
#endif
