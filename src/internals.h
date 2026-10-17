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

#endif