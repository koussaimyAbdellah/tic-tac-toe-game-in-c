#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game_logic.h"
#include "ai_stratigie.h"

char first_to_start(marks* m){
    int index = rand()%2;
    if(index == 0){
        return m->player;
    }
    if (index == 1)
    {
        return m->bot;
    }
}

marks*  create_choice_mark(char c){
    marks* new_mark = malloc(sizeof(marks));

    if (new_mark == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_mark.\n");
        exit(1);
    }
    
    
        if (c == 'x' || c == 'X')
        {
            new_mark->player = 'x';
            new_mark->bot = 'o';
            new_mark->first_start = first_to_start(new_mark);
            new_mark->last_round = new_mark->first_start;
            return new_mark;
        }else if (c == 'o' || c == 'O')
        {
            new_mark->player = 'o';
            new_mark->bot = 'x';
            new_mark->first_start = first_to_start(new_mark);
            new_mark->last_round = new_mark->first_start;
            return new_mark;
        }
    } 

int* init_table(){
    int* table_game = malloc(sizeof(int)*9);

    for (int i = 0; i < 9; i++)
    {
        table_game[i] = EMPTHY;
    }
    
    return table_game;
}

int set_mark_sp(marks* m,int *tab,int index,int *arr,int size){

    if (index>8 || index < 0)
    {
        fprintf(stderr,"invalid index: must be in withen range   0-9\n");
        return-1;
    }
    
    if (tab[index] != -1)
    {
        fprintf(stderr,"invalid index: you need to chose unocupped place.\n");
        return-1;
    }
    if (arr == NULL)
    {
        if (m->last_round == m->player)
        {
            tab[index] =  PLAYER;
            m->last_round = m->bot;
        }
        else
        {
            tab[index] = BOT;
            m->last_round = m->player;
        }
    }else{
        if (m->last_round == m->player)
        {
            tab[index] =  0;
            m->last_round = m->bot;
            arr[size] = index;
            
        }
        else
        {
            tab[index] = 1;
            m->last_round = m->player;
            arr[size] = index;
           
        } 
        return size++;
    }
    
    
}

bool set_mark(marks* m,int *tab,int index){
    // set_mark_sp(m,tab,index,NULL,-1);

        if (m == NULL || tab == NULL)
        {
            perror("invalid input: null pointer arguement\n.");
            exit(1);
        }
        
        if (index>8 || index < 0)
        {
            fprintf(stderr,"invalid index: must be in withen range   0-9\n");
            return false;
        }
        
        if (tab[index] != EMPTHY)
        {
            fprintf(stderr,"invalid index: you need to chose unocupped place.\n");
            return false;
        }

        if (m->last_round == m->player)
        {
            tab[index] =  PLAYER;
            m->last_round = m->bot;
        }
        else
        {
            tab[index] = BOT;
            m->last_round = m->player;
        }
        
        return true;
}

 bot_move *create_stratigie_bot(){

        bot_move *arr_st = malloc(sizeof(bot_move)*STRATIGIE_COUNT);
        
        if (arr_st == NULL)
        {
            fprintf(stderr,"memory allocaton failded for array stratigie bot");
            exit(1);
        }
        
        arr_st[0] = bot_index_0;
        arr_st[1] = bot_index_1;
        arr_st[2] = bot_index_2;
        arr_st[3] = bot_index_3;
        arr_st[4] = bot_index_4;

        return arr_st;
    }
    
game_info *game_init(char m,int i,bot_move *arr_st){
    game_info *new_game = malloc(sizeof(game_info));
    
    if (new_game == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_game.\n");
        exit(1);
    }

    marks *new_mark = create_choice_mark(m);
    
    if (new_mark == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_mark.\n");
        exit(1);
    }

    int *new_tab = init_table(new_mark);

    if (new_tab == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_tab.\n");
        exit(1);
    }

    if (i == -1)
    {
        new_game->stratigie = NULL;
    }else{ 
        new_game->stratigie = arr_st[i]; 
    }
    
    new_game->m = new_mark;
    new_game->tab = new_tab;
    new_game->empthy_count = 9;

    return new_game;
}

game_info *game_init_5(char m,bot_move5 move){
    game_info *new_game = malloc(sizeof(game_info));
    
    if (new_game == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_game.\n");
        exit(1);
    }

    marks *new_mark = create_choice_mark(m);
    
    if (new_mark == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_mark.\n");
        exit(1);
    }

    int *new_tab = init_table(new_mark);

    if (new_tab == NULL)
    {
        perror("allocation error: cannot allocat memroy for new_tab.\n");
        exit(1);
    }

    new_game->move = move;  

    new_game->m = new_mark;
    new_game->tab = new_tab;
    new_game->empthy_count = 9;

    return new_game;
}

int check_win(const int *tab){
    for (int i = 0; i < 3; i++)
    {
        if (tab[i] == tab[i+3] && tab[i] == tab[i+6])
        {
            if (tab[i] == EMPTHY)
            {
                continue;;
            }
            return 1;   
        }
    }
    
    for (int i = 0; i < 7; i = i +3)
    {
        if (tab[i] == tab[i+1] && tab[i] == tab[i+2])
        {
            if (tab[i] == EMPTHY)
            {
                continue;;
            }
            return 1;
        }   
    }
    for (int i = 0; i < 3; i= i+2)
    {
        if (tab[i] == tab[4] && tab[8-i] == tab[4])
        {
            if (tab[i] == EMPTHY)
            {
                continue;;
            }
            return 1;
        }
    }
    return 0;
}

void clean_up(game_info **gm){
    if (gm == NULL || *gm == NULL)
    {
        return;
    }
    
    game_info *gg = *gm;

    free(gg->m);
    free(gg->tab);
    free(gg);

    *gm = NULL;
}