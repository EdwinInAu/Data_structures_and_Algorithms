#include <stdio.h>
#include <stdlib.h>
typedef struct Puzzle *Puz;
void screen_output(int*, int);
int solution(int, int, int, int, int);
int test(int*, int);
int list(char *, int);
int list_algorithm(int *, int);
int blank_position_start(int*, int);
int blank_position_goal(int*, int);
Puz newPuz(int);
void freePuz(Puz);