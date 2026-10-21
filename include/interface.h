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


/**
 * main user interface,here is where we move to other interface
 * contain two interface 0 and 1. 
 */
void interface0(interface i1,interface i2);

/**
 * multuplayer interface ,after you chose these interface 
 * you can start play with others after you chose your mark
 * or get back to main interface
 */
void interface1();

/**
 * solo interface ,after you chose it you can play with bot after
 * you chose difficlty ,with mark to play with or get back to 
 * main interface.
 */
void interface2();

/**
 * this is the real start of game .
 * by calling this function. that mean you inint the game and
 * start playing for now i will just make it for one mode 
 * then later i will make this function chose between modes
 * based on case that been called form .
 */
void game(char mark);

/**
 * @brief read input intgers form stdin,
 * and flush the inputbuffer for integer value
 * store it in integrs value.
 * @param *var is pointer to integrs that we need to read
 * @return int value ,after reading the input user.
 * @retval 1 if input was integers.
 * @retval 0 if input was other value.
 * @retval -1 if ipnut was EOF.like ctrl + d
 */
int read_input(int *var);

/**
 * @brief read user mark to start with.
 * if user sumbber wrong mark it keep ask him tell 
 * he give the correct choice.
 * set mark direclty via pointer
 * @param c is the mark must be x or o. 
 * @return 1 if succes 0 if failed -1 if eof.
 */
int read_mark(char *c);

void game_start(game_info *gm);

void game_start_solo(game_info *gm);

void game_solo(char mark,int i);

void game(char mark);

void print_border(game_info *gm);

int get_index();

int get_index_bot(game_info *gm);
#endif