#ifndef GAME_LOGIC_H
#define GAMAE_LOGIC_H

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

typedef struct 
{
    marks *m;
    int *tab;
    int empthy_count;
}game_info;

char first_to_start(marks* m);

marks*  create_choice_mark(char c);

int* init_table();

int set_mark_sp(marks* m,int *tab,int index,int *arr,int size);

void set_mark(marks* m,int *tab,int index);

game_info *game_init(char m);

int check_win(int *tab);

void clean_up(game_info *gm);

#endif