#ifndef AI_BOT_STRATIGIE_H
#define AI_BOT_STRATIGIE_H



typedef struct bot_i_s
{   
    bool bot_init_value;

    int win_arr[8][3];
    int size_a;

    int *arr_element;
    int size_e;

    int corner[4];
    int empthy_case[5];

    int counter_corner;
    int counter_case;

}bot_info;

int bot_index_0(const int *tab);

int bot_index_1(const int *tab);

int bot_index_2(const int *tab);

int bot_index_3(const int *tab);

int bot_index_4(const int *tab);

int bot_index_5(const int *tab,bot_info *b);

int bot_index_6(const int *tab);

void reset_bot_index_6(void);

#endif