#include <stdio.h>
#include <stdbool.h>
#include "ai_stratigie.h"
#include "game_logic.h"
#include "interface.h"
#include "internals.h"

//-----------------------------------------------------------------------//
/*====================================*/
static void flush_line(void) {          
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    }
/*====================================*/
int read_input(int *var) {    
    int res = scanf("%d", var);
    if (res == EOF) {
        return -1;
    }
    flush_line();
    return (res == 1)?1:0;
    }  

int read_mark(char *c){
    int ch = getchar();
    if (ch == EOF)
    {
        return -1;
    }

    if (ch == 'x' || ch == 'X')
    {
        *c = ch;
        return 1;
    }else if (ch == 'o' || ch == 'O')
    {
        *c = ch;
        return 1;
    }else{
        return 0;
    } 
}
//-----------------------------------------------------------------//
void interface0(interface i1,interface i2){
    int choice_main;

    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");
    printf(">> welcome to tic tac toe game <<\n");
    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");

    while (true)
    {
        printf("===========================\n");
        printf("give you choice:\n");
        printf("0-exit game.\n");
        printf("1-multiplayer mode.\n");
        printf("2-solo mode.\n");
        printf("===========================\n");

        int input_status = read_input(&choice_main);
        if (input_status == -1)
        {
            printf("\n");
            break;
        }
        if (input_status != 1)
        {
            printf("->>>you must give interger value<<<<-\n");
            continue;
        }
    
        switch (choice_main)
        {
        case 0:
            break;
        case 1:
            i1();
            break;
        case 2:
            i2();
            break;
        default:
            printf("-->>>please give the correct choice...<<<--\n");
            break;
        }

        if (choice_main == 0)
        {
            printf("##############################\n");
            printf("you have quit the game..\n");
            printf("have a good day.\n");
            printf("##############################\n");
            break;
        }
    }
}
//--------------------------------------------------------------------------//

static void helper1(int *op){
    while (true)
    {
            printf("===========================\n");
            printf("give you choice:\n");
            printf("0-exit game.\n");
            printf("1-start game.\n");
            printf("===========================\n");

            int res = read_input(op);

            if (res == -1)
            {
                printf("\n");
                return;
            }
            
            if (res != 1)
            {
                printf("->>>you must give interger value<<<<-\n");
                continue;
            }
            return;
    } 
}

static void helper2(char *m){
    while (true)
    {
        printf("=====================================\n");
        printf("give you mark to play with:(x or o)\n");
        printf("=====================================\n");
        
        int res = read_mark(m);
        
        if (res == -1)
        {
            printf("\n");
            return;
        }
        if (res != 1)
        {
            printf("->>>you must give X or O value<<<<-\n");
            continue;
        }
        return;
    }  
}
static int helper3(int *option,char * mark,interface i){
            int op;

            while (true)
            {
                printf(">>==========<<\n");
                printf(">>game start<<\n");
                printf(">>==========<<\n");

                printf("->>pres 1 to start or 2 to retry<<-\n");
            
                int res = read_input(&op);

                if (res == -1)
                {
                    printf("\n");
                    return res;
                }
                if (res != 1)
                {
                    printf("->>>you must give interger value<<<<-\n");
                    continue;
                }
                if (op == 1)
                {
                    /*printf("case 1: call game to play in multi player mode.\n");
                    printf("option: %d,mark: %c.\n",*option,*mark);*/
                    i();// callback
                    return op;
                }else if(op == 2){
                    return op;
                }
                printf("invalid option.\n");
            }
        }

void interface1(){
    int option;
    char mark;

    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");
    printf(">>     multiplayer interface    <<\n");
    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");

    while (true)
    {
        helper1(&option);
        
        if (option == 0)
        {
            printf("case 0: exit interface.\n");
            break;
        }
        
        helper2(&mark);

        
        if (option == 1)
        {
            int temp = helper3(&option,&mark,game);
            if(temp == -1){
                printf("\n");
                return;
            }
            option = temp;
        }

        if (option == 2)
        {
            printf("case 2 : retry to assing new value like new mark or leave.\n");
            printf("option: %d,mark: %c.\n",option,mark);
            continue;
        }else if (option == 1)
        {
            break; 
        }
        printf("-->>>please give the correct choice...<<<--\n");
    }
}
//---------------------------------------------------------------//

void interface2(){

}

//----------------------------------------------------//

void print_border(game_info* gm){

}
int get_index(){
    int i ;
    while (true)
    {
        printf("give your index betwen 1-9.(choose a emthpy place)\n");
        int res = read_input(&i);

        if (res == -1)
        {
            printf('\n');
            return-1;
        }
        if (res != 1)
        {
            printf("give the correct choice .\n");
            continue;
        }

        if (i> 9 || i < 1)
        {
            printf("give the correct choice .\n");
            continue;
        }
        
        return i;
    }
    
    
    
}

void game_start(game_info *gm){
    bool game_over = false;
    int eval;
    int index;
    while (!game_over)
    {
        eval = check_win(gm->tab);
        if (eval == 1)
        {
            
        }else if(eval == 0 && gm->empthy_count <= 0){

        }
        
        index = get_index();

        if (index == -1)
        {
            printf('\n');
            return;
        }
        set_mark(gm->m,gm->tab,index-1);
        gm->empthy_count--;

        print_border(gm);
    }
    
}

void game(char mark){
    game_info *gm = game_init(mark);
    game_start(gm);
}