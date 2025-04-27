#include <sqlite3.h>
#include <stdbool.h>

#ifndef HESTIA_H
#define HESTIA_H

_Bool validate_argument(int argc, char *argv[]);

int play_game(char *player_name, sqlite3 *db);

void fetch_high_score();

void print_help_message();

#endif
