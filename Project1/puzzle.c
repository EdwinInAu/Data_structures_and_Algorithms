#include <stdio.h>
#include <stdlib.h>
#include "boardADT.h"
#define max_size 9999

int main() {
    char *list_address = (char *) malloc(sizeof(char) * max_size);
    int list_length;
    while (0 != (list_length = list(list_address, max_size))) {
        break;
    }
    if (list_length  == 1) {
        printf("solvable\n");
        return EXIT_SUCCESS;
    }
    if (list_length  == -1) {
    printf("unsolvable\n");
    return EXIT_SUCCESS;
    }
    if (list_length == 10) {
        return EXIT_FAILURE;
    }
}