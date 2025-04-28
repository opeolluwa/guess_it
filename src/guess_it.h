#include <sqlite3.h>
#include <stdbool.h>

#ifndef GUESS_IT_VALIDATORS
#define GUESS_IT_VALIDATORS
bool validate_argument(int argc, char *argv[]);
int play_game(char *player_name, sqlite3 *db);
void fetch_high_score();
void print_help_message();
#endif


#ifndef GUESS_IT_DB_API
#define GUESS_IT_BD_API
struct Score
{
    char *user_name[];
    unsigned long score;
}
bool user_name_exist(char *user_name[]);
int create_user(char *user_name[]);
Score fetch_user_score(char *user_name[]);
#endif

#ifndef GUESS_IT_TYPES
#define GUESS_IT_TYPES

