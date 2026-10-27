#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>

#include "ai_stratigie.h"

typedef struct choice_mark
{
    char player;
    char bot;

    char last_round;
    char first_start;
}marks;

typedef enum{
    EMPTHY = -1,
    BOT = 1,
    PLAYER = 0
}round_whO;

#define STRATIGIE_COUNT 7

typedef int (*bot_move)(const int *tab);
typedef int (*bot_move5)(const int *tab,bot_info *b);

typedef struct 
{
    marks *m;
    int *tab;
    int empthy_count;
    bot_move stratigie;
    bot_move5 move;
    bot_info *b;
}game_info;

char first_to_start(marks* m);

marks*  create_choice_mark(char c);

int* init_table();

int set_mark_sp(marks* m,int *tab,int index,int *arr,int size);

bool set_mark(marks* m,int *tab,int index);

game_info *game_init(char m,int i,bot_move * arr_st);
game_info *game_init_5(char m,bot_move5 move);

bot_move *create_stratigie_bot();

int check_win(const int *tab);

void clean_up(game_info **gm);

#endif