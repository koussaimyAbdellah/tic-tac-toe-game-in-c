#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game_logic.h"

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

        if (index>8 || index < 0)
        {
            fprintf(stderr,"invalid index: must be in withen range   0-9\n");
            return false;
        }
        
        if (tab[index] != -1)
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

game_info *game_init(char m){
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

void clean_up(game_info *gm){
    if (gm == NULL)
    {

        return;
    }
    if (gm->m == NULL)
    {
        return;
    }
    if (gm->tab == NULL)
    {
        return;
    }

    free(gm->m);
    free(gm->tab);
    free(gm);
}