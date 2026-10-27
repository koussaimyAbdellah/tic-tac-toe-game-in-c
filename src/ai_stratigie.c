#include <stdlib.h>
#include "game_logic.h"
#include "ai_stratigie.h"


static bool check_win_in(int arr[][3], int size, const int *arr_e, int arr_size)
{
    /* A winning line must contain exactly three distinct board positions. */
    if (arr == NULL || arr_e == NULL || size <= 0 || arr_size != 3) {
        return false;
    }

    if (arr_e[0] == arr_e[1] ||
        arr_e[0] == arr_e[2] ||
        arr_e[1] == arr_e[2]) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        bool all_found = true;

        for (int k = 0; k < arr_size; k++) {
            bool found = false;

            for (int j = 0; j < 3; j++) {
                if (arr_e[k] == arr[i][j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                all_found = false;
                break;
            }
        }

        if (all_found) {
            return true;
        }
    }

    return false;
}

static int choose_empty_corner(const int tab[9], const bot_info *b)
{
    int available[4];
    int count = 0;

    for (int i = 0; i < b->counter_corner && i < 4; i++) {
        int square = b->corner[i];

        if (square >= 0 && square < 9 && tab[square] == EMPTHY) {
            available[count++] = square;
        }
    }

    if (count == 0) {
        return -1;
    }

    return available[rand() % count];
}

static int choose_empty_square(const int tab[9])
{
    for (int i = 0; i < 9; i++) {
        if (tab[i] == EMPTHY) {
            return i;
        }
    }

    return -1;
}

static int find_tactical_move(const int tab[9], bot_info *b, int mark)
{
    int marks[9];
    int mark_count = 0;

    for (int i = 0; i < 9; i++) {
        if (tab[i] == mark) {
            marks[mark_count++] = i;
        }
    }

    for (int a = 0; a < mark_count; a++) {
        for (int c = a + 1; c < mark_count; c++) {
            for (int move = 0; move < 9; move++) {
                if (tab[move] != EMPTHY) {
                    continue;
                }

                /* Every valid winning line has an index sum divisible by 3. */
                if ((marks[a] + marks[c] + move) % 3 != 0) {
                    continue;
                }

                b->arr_element[0] = marks[a];
                b->arr_element[1] = marks[c];
                b->arr_element[2] = move;
                b->size_e = 3;

                if (check_win_in(b->win_arr, b->size_a,
                                 b->arr_element, b->size_e)) {
                    return move;
                }
            }
        }
    }

    return -1;
}


int bot_index_0(const int *tab){
    int empty[9];
    int count = 0;

    if (tab == NULL) {
        return -1;
    }

    for (int i = 0; i < 9; i++) {
        if (tab[i] == EMPTHY) {
            empty[count++] = i;
        }
    }

    return count == 0 ? -1 : empty[rand() % count];
}

int bot_index_1(const int *tab){
    int index;
    if (tab[4] == EMPTHY)
    {
        return 4;
    }
    return bot_index_0(tab); 
}

int bot_index_2(const int *tab){
        int index = bot_index_1(tab);

        int bot_indexs[5];
        int count = 0;

        for (int i = 0; i < 9; i++)
        {
            if (tab[i] == BOT)
            {
                bot_indexs[count] = i;
                count++;
            }
        }

        if (count < 2)
        {
            return index;
        }else if (count > 2)
        {
            return index;
        }
        

        int requiested_index = -1;

        int win_arr[9][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{6,4,2}};
        int size_arr = sizeof(win_arr)/sizeof(win_arr[0][0]);
        int element_arr[3];

        for (int i = 0; i < 9; i++)
        {
            if ((bot_indexs[0]+bot_indexs[1]+i)%3 == 0)
            {
                if (bot_indexs[0] != i && i != bot_indexs[1])
                    {   
                        element_arr[0] = bot_indexs[0];
                        element_arr[1] = bot_indexs[1];
                        element_arr[2] = i;

                        if (check_win_in(win_arr,size_arr,element_arr,3))
                        {
                            requiested_index = i;
                        }
                    } 
            }
        }

        if (requiested_index == -1 || tab[requiested_index] != EMPTHY)
        {
            requiested_index = index;
        }
         

        return requiested_index;
}

int bot_index_3(const int *tab){
        int bot_indexs[5];
        int count = 0;
        int index;

        for (int i = 0; i < 9; i++)
        {
            if (tab[i] == 1)
            {
                bot_indexs[count] = i;
                count++;
            }
        }

        if (count == 0)
        {
            if (tab[4] == -1)
            {
               return 4;
            }else{
                int conner_arr[4] = {0,2,6,8};
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
            }
        }else if (count == 1)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{

                int conner_arr[4] = {0,2,6,8};
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
            }
        }else if (count == 2)
        {
            return bot_index_2(tab);
        }
        return bot_index_0(tab);
}

int bot_index_4(const int *tab){
        int bot_indexs[5];
        int count = 0;

        int index = bot_index_0(tab);

        int player_indexs[5];
        int count_player  = 0;

        for (int i = 0; i < 9; i++)
        {
            if (tab[i] == BOT)
            {
                bot_indexs[count] = i;
                count++;
            }
            if (tab[i] == PLAYER)
            {
                player_indexs[count_player] = i;
                count_player++;
            }  
        }

        if (count == 0)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{

                int conner_arr[4] = {0,2,6,8};
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
            }
        }else if (count == 1)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{
                if (count_player == 1)
                {
                    do{ 
                    index = rand()%9;
                    }while (tab[index] != -1);
                    return index;
                }
                
                return index;
            }
        }else if (count == 2)
        {
            return bot_index_2(tab);
        }
    return bot_index_0(tab);
}

int bot_index_5(const int tab[9], bot_info *b)
{
    if (tab == NULL || b == NULL || b->arr_element == NULL) {
        return -1;
    }

    int count_bot = 0;
    int count_player = 0;
    int first_player_mark = -1;

    for (int i = 0; i < 9; i++) {
        if (tab[i] == BOT) {
            count_bot++;
        } else if (tab[i] == PLAYER) {
            if (first_player_mark == -1) {
                first_player_mark = i;
            }
            count_player++;
        }
    }

    if (count_bot == 0 && tab[4] == EMPTHY) {
        return 4;
    }

    if (b->bot_init_value && count_bot == 1 && tab[4] == BOT) {
        int opposite_corner = -1;

        switch (first_player_mark) {
            case 0: opposite_corner = 8; break;
            case 2: opposite_corner = 6; break;
            case 6: opposite_corner = 2; break;
            case 8: opposite_corner = 0; break;
            default: break;
        }

        if (opposite_corner != -1 && tab[opposite_corner] == EMPTHY) {
            return opposite_corner;
        }

        int corner = choose_empty_corner(tab, b);
        if (corner != -1) {
            return corner;
        }
    }

    int move = find_tactical_move(tab, b, BOT);
    if (move != -1) {
        return move;
    }

    move = find_tactical_move(tab, b, PLAYER);
    if (move != -1) {
        return move;
    }

    move = choose_empty_corner(tab, b);
    if (move != -1) {
        return move;
    }

    return choose_empty_square(tab);
}
