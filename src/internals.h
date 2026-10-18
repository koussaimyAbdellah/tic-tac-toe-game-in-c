#ifndef INTER_HELPER_I_H
#define  INTER_HELPER_I_H

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

void print_border(game_info *gm);

int get_index();

#endif