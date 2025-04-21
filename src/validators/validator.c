

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "validators/validator.h"

_Bool validate_argument(int argc, char *argv[]) {
    if (!(argc >= 2)) {
        printf("Invalid arguments\n");
        return false;
    }
    char *arg = argv[1];
    if (!strcmp(arg, "--help") || !strcmp(arg, "-h") || !strcmp(arg, "play") || strcmp(arg, "--leaderboard") ||
        strcmp(arg, "-l")) {
        printf("Invalid arguments\n");
        return false;
    }
    return true;
}
