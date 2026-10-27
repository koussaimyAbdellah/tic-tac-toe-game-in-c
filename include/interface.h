#ifndef INTERFACE_H
#define INTERFACE_H

#include "game_logic.h"

typedef void (*interface)();
typedef void (*game_p)(char);
typedef void (*game_pp)(char,int);

typedef struct 
{
    game_p multi_player;
    game_pp solo;
    int diff;
}gm_i;


void interface0(interface i1,interface i2);

void interface1();

void interface2();

void game(char mark);

int read_input(int *var);

int read_mark(char *c);

void game_start(game_info *gm);

void game_start_solo(game_info *gm);

void game_solo(char mark,int i);

void game(char mark);

void print_border(game_info *gm);

int get_index();

int get_index_bot(game_info *gm);
#endif