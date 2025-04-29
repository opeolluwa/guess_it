
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "guess_it.h"
#include <sqlite3.h>

// Emojis
#define GOOD_FEEDBACK_EMOJIS {"😊", "😘", "🤗", "💞", "💝", "💓", "💖", "💓", "😍", "😝", "👐", "😚"}
#define OUCH_FEEDBACK_EMOJIS {"😣", "😭", "😩", "😟", "😤", "😢", "😒", "😌", "😔", "😬", "🤧"}

// Replies
#define GREATER_THAN_REPLIES {                                  \
    "Try again, your current input is greater than the number", \
    "Exceeding!\\n Try a lesser value",                         \
    "That's over the top \\n, try something lower",             \
    "Ouch! that's way more than the target"}

#define LESS_THAN_REPLIES {                                        \
    "Ouch! %s your guess is less than the number %s",              \
    "%s Try something greater, current input is less than target", \
    "Aim higher %s.",                                              \
    "%s, your guess is not up to the target."}

#define EQUAL_TO_REPLIES {                  \
    "Awesome! %s that's correct.",          \
    "%s Ten on Ten! your input is correct", \
    "Incredible 😋 that's correct %s",      \
    "That's very correct",                  \
    "You're UNSTOPPABLE! That's correct",   \
    "You guessed right %s"}

#define CLOSE_TO_REPLIES {                                    \
    "Almost there. %s",                                       \
    "That's very close yet less than the number. %s",         \
    "Ouch %s You missed a bit. The target number is higher.", \
    "%s...that was so close, try again.",                     \
    "That's close",                                           \
    "You tried %s, aim again"}

#define WELCOME_REPLIES {    \
    "Welcome",               \
    "Glad to have you",      \
    "It's good to have you", \
    "You're most welcome",   \
    "Greetings",             \
    "Holla!",                \
    "Welcome, let's get started"}

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

const char *get_random_item(const char *items[], int size)
{
    return items[rand() % size];
}

int play_game(char *user_name, sqlite3 *db)
{
    srand(time(NULL));

    const char *goodEmojis[] = GOOD_FEEDBACK_EMOJIS;
    const char *ouchEmojis[] = OUCH_FEEDBACK_EMOJIS;
    const char *equalReplies[] = EQUAL_TO_REPLIES;
    const char *lessThanReplies[] = LESS_THAN_REPLIES;
    const char *greaterThanReplies[] = GREATER_THAN_REPLIES;
    const char *welcomeMsgs[] = WELCOME_REPLIES;
    const char *closeToReplies[] = CLOSE_TO_REPLIES;

    const int sizeOfGoodEmojis = sizeof(goodEmojis) / sizeof(goodEmojis[0]);
    const int sizeOfOuchEmojis = sizeof(ouchEmojis) / sizeof(ouchEmojis[0]);
    const int sizeOfEqualReplies = sizeof(equalReplies) / sizeof(equalReplies[0]);
    const int sizeOfLessThanReplies = sizeof(lessThanReplies) / sizeof(lessThanReplies[0]);
    const int sizeOfCloseToReplies = sizeof(closeToReplies) / sizeof(closeToReplies[0]);
    const int sizeOfGreaterThanReplies = sizeof(greaterThanReplies) / sizeof(greaterThanReplies[0]);
    const int sizeOfWelcomeMsgs = sizeof(welcomeMsgs) / sizeof(welcomeMsgs[0]);

    bool game_over = false;
    int score = 500;

    if (!user_name_exist(user_name, db))
    {
        int rc = create_user(user_name, db);
        if (rc != 0)
        {
            fprintf(stderr, "Error creating user %s", user_name);
            return 1;
        }
    }

    int guess = 56;
    int user_guess;
    char formattedReply[256];
    printf("System: %s\n", get_random_item(welcomeMsgs, sizeOfWelcomeMsgs));

    while (score != 0)
    {
        printf("> Guess a number %s: \n", user_name);
        scanf("%d", &user_guess);
        const char *emoji = get_random_item(ouchEmojis, sizeOfOuchEmojis);

        if (guess == user_guess)
        {
            score += 100;
            const char *reply = get_random_item(equalReplies, sizeOfEqualReplies);
            sprintf(formattedReply, reply, emoji);
            printf("Feedback: %s\n", formattedReply);
            printf("You have %d more retries\n", score / 100);
        }
        else if (user_guess > guess)
        {
            score -= 100;
            const char *reply = get_random_item(greaterThanReplies, sizeOfGreaterThanReplies);
            sprintf(formattedReply, reply, emoji);
            printf("Feedback: %s\n", formattedReply);
            printf("You have %d more retries\n", score / 100);
        }
        else if (user_guess < guess)
        {
            score -= 100;
            const char *reply = get_random_item(lessThanReplies, sizeOfLessThanReplies);
            sprintf(formattedReply, reply, emoji);
            printf("Feedback: %s\n", formattedReply);
            printf("You have %d more retries\n", score / 100);
        }
        else if (((user_guess + 10) > guess) || ((user_guess - 10) < guess))
        {
            score -= 100;
            const char *reply = get_random_item(closeToReplies, sizeOfCloseToReplies);
            sprintf(formattedReply, reply, emoji);
            printf("Feedback: %s\n", formattedReply);
            printf("You have %d more retries\n", score / 100);
        }
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
    const char *sql = "SELECT 1 FROM " PLAYERS_TABLE_NAME " WHERE user_name = ?";
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

    const char *sql = "INSERT INTO " PLAYERS_TABLE_NAME "(user_name) VALUES (?)";
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
    sqlite3_close(db);
    return 0;
}
struct Score fetch_user_score(char *user_name, sqlite3 *db) {}
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    return 0;
}