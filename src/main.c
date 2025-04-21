#include <stdio.h>
#include "validators/validator.h"


int main(int argc, char *argv[]) {
    _Bool is_valid_command = validate_argument(argc, argv);
    printf("%s\n", is_valid_command ? "valid" : "invalid");
    printf(" you have entered %d ", argc);
    for (int i = 0; i < argc; i++) {
        printf(" %s", argv[i]);
    }
}
