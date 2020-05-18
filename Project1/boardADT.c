//
// COMP9024 Assignment 1
//
// Authors:
// Chongshi Wang
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "boardADT.h"

typedef struct Puzzle{
    int *board;

    int length;

} Puzzle;

int list(char *list, int max_size) {
    int a;
    int d = 0;
    int n = 0;
    int k = 0;
    int y = 1;
    int *q;
    int list_length = 0;
    int *list_address;
    int half_length;

    list_address = malloc(max_size * sizeof(int));

    if (list_address == NULL) {
        fprintf(stderr, "Run out of memory\n");
        return EXIT_FAILURE;
    }
    Puz puz = newPuz(max_size);
    puz->board = list_address;
    q = puz->board;

    while ((a = getchar()) != EOF && list_length < max_size) {

        if ((a < 48 || a > 57) && a != ' ' && a != '\n' && a != '\t' && a != 'b') {
            fprintf(stdout, "Please provide integers or blank and separate by space or tab\n");
            return 10;
        }

        if (a == '\n') {
            n++;
            y++;
            if (d!=0){
                d=0;
                k=0;
                q++;
                list_length++;
            }
            if (n == 1) {
                half_length = list_length;
            }
            if (n == 2) {
                if (half_length + half_length != list_length) {
                    fprintf(stdout,"Both the start and goal should be in same structure N * N(N>=2) with strictly one 'b' and strictly one '1' to one 'N'.\n");
                    return 10;
                }
                break;
            }
        }
        if (a == 'b' && d == 0 ) {
            d++;
            *q = a;
            y = 0;
        }
        if ((a == 't' || a == ' ') && d != 0) {
            list_length++;
            d = 0;
            q++;
            k = 0;
            y++;
        }
        if (a>='0'&&a<='9'&& y!=0 ) {
            *q = k * 10 + (a - 48);
            k = *q;
            d++;
        }
    
    }
     puz->length = list_length; 
    int test_list = test(list_address, list_length);
    if (test_list == 100) {
        fprintf(stdout,"Both the start and goal should be in same structure N * N(N>=2) with strictly one 'b' and strictly one '1' to one 'N'.\n");
        return 10;
    }
    int b_start = blank_position_start(list_address, list_length);
    int b_goal = blank_position_goal(list_address, list_length);
    if (b_start == 1000) {
        return 10;
    }
    if (b_goal == 1000) {
        return 10;
    }
    int sum_start = list_algorithm(list_address, list_length / 2);
    int sum_goal = list_algorithm(list_address + list_length / 2, list_length / 2);

    int wcs = solution(sum_start, sum_goal, b_start, b_goal, list_length);

    printf("Start: ");
    screen_output(list_address, list_length / 2);

    printf("Goal:  ");
    screen_output(list_address + (list_length / 2), list_length / 2);

    free(list_address);

    return wcs;
}

int test(int *line, int list_length) {
    int *a;
    int *c;
    int *d;
    int *e;
    int *f;
    int blank = 0;
    int sum = 0;
    int h=(sqrt(list_length / 2));
    if (list_length / 2 < 4) {
        return 100;
    }
    if (h*h!=list_length/2) {
        return 100;
    }
    for (a = line; a < line + list_length; a++) {
        if (*a == 'b'){
            blank ++;
            if (blank > 2) {
                return 100;
            }
            continue;
        }
        if (*a == 0){
            return 100;
        }
        if (*a >= (list_length / 2)) {
            return 100;
        }
        sum = sum + *a;
    }
    for (c = line; c < line + (list_length / 2); c++) {
        if (*c == 'b') {
            continue;
        }
        for (d = c + 1; d < line + (list_length / 2); d++) {
            if (*d == 'b') {
                continue;
            }
            if (*c == *d) {
                return 100;
            }
        }
    }
    for (e = line + (list_length / 2); e < (line + list_length); e++) {
        if (*e == 'b') {
            continue;
        }
        for (f = e + 1; f < (line + list_length); f++) {
            if (*f =='b') {
                continue;
            }
            if (*e == *f) {
                return 100;
            }
        }
    }
    if ((sum / 2) != ((list_length / 2) * (list_length / 2 - 1) / 2)) {
        return 100;
    }
    return 50;
}

int list_algorithm(int *list, int list_length) {

    int *a;
    int *b;
    int sum = 0;
    for (a = list; a < list + list_length; a++) {
        if (*a == 'b') {
            continue;
        }
        for (b = a; b < list + list_length; b++) {
            if (*b == 'b') {
                continue;
            }

            if (*a > *b) {
                sum++;
            }
        }
    }
    return sum;
}

int blank_position_start(int *list, int list_length) {
    int *a;
    int b = 0;
    for (a = list; a < list + (list_length / 2); a++) {
        b++;
        if (*a == 'b') {
            return ceil(b / (sqrt(list_length / 2)));
        }
    }
    return 1000;
}

int solution(sum_start, sum_goal, b_start, b_goal, list_length) {
    int tl=0;
    int dym=0;

    if (list_length % 4 != 0) {
        if (sum_start % 2 == sum_goal % 2) {
            return 1;
        } else {
            return -1;
        }
    }
    
    if (list_length % 4 == 0) {
        tl = sum_start + b_start;
        dym = sum_goal + b_goal;
        if (tl % 2 == dym % 2) {
            return 1;
        } else {
            return -1;
        }
    }
}

int blank_position_goal(int *list, int list_length) {
    int *a;
    int b = 0;
    for (a = list + (list_length / 2); a < list + list_length; a++) {
        b++;
        if (*a == 'b') {
            return ceil(b / (sqrt(list_length / 2)));
        }
    }
    return 1000;
}

void screen_output(int *line, int length) {
    int *a;
    for (a = line; a < line + length; a++) {

        if (a == line + length - 1) {
            if (*a == 98) {
                printf("b\n");
                return;
            } else {
                printf("%d\n", *a);
                return;
            }
        }
        if (*a == 98) {
            printf("b ");
            continue;
        }
        printf("%d ", *a);
    }
}

Puz newPuz(int msize) {
   Puzzle *puz = malloc(sizeof(Puzzle));
   puz->board = malloc(msize * sizeof(int));
   puz->length = 0;
   return puz;
}

void freePuz(Puz puz){
    free(puz->board);
    free(puz);
    return;
}