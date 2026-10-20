#include <stdio.h>
#include <stdbool.h>
#include "ai_stratigie.h"
#include "interface.h"

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

static void read_option_interface(int *op){
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

static void read_mark_interface(char *m){
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

static int game_interface(int *option,char * mark,game_p g){
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
                    //this is the real game call from this callback we run the game.
                    g(*mark);// callback
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
        read_option_interface(&option);//an interface to read option with options.
        
        if (option == 0)
        {
            printf("case 0: exit interface.\n");
            break;
        }
        
        read_mark_interface(&mark);

        
        if (option == 1)
        {
            int temp = game_interface(&option,&mark,game);//interface connect loigc game whit user interface
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
    int option;
    char mark;

    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");
    printf(">>     solo interface    <<\n");
    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");

    while (true)
    {
        read_option_interface(&option);

        if (option == 0)
        {
            printf("case 0: exit interface.\n");
            break;
        }
        
        read_mark_interface(&mark);

        if (option == 1)
        {
            int temp = game_interface(&option,&mark,game_solo);//interface connect loigc game whit user interface
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

//----------------------------------------------------//

void print_border(game_info *gm){
    int bn = 2;
    printf("\n");
    for (int i = 0; i < 7; i = i+3)
    {
        int n = 2;
        for (int j = i; j < 3+i; j++)
        {
            if (gm->tab[j] == 0)
            {
                printf("%c",gm->m->player);
            }else if (gm->tab[j] == 1)
            {
                printf("%c",gm->m->bot);
            }else if (gm->tab[j] == -1)
            {
                printf("%d",j+1);
            }
            
            if (n > 0)
            {
                printf("|");
                n--;
            }
        }
        printf("\n");
        if (bn > 0)
        {
            printf("_____\n");
            bn--;
        }        
    } 
    printf("\n");
}

int get_index(){
    int i ;
    while (true)
    {
        printf("{give your index betwen 1-9.(choose a emthpy place)}\n");
        int res = read_input(&i);

        if (res == -1)
        {
            printf("\n");
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
       
        printf("[-<player with %c round>-]",gm->m->last_round);
        print_border(gm);

        if (eval == 1)
        {
            char winner = (gm->m->last_round == gm->m->player)?gm->m->bot:gm->m->player;
            int winner_num = (gm->m->last_round == gm->m->player)?2:1;
            printf("->>>{player %d,with mark %c was win.}<<<-\n",winner_num,winner);

            clean_up(gm);
            game_over = true;
            continue;  
        }else if(eval == 0 && gm->empthy_count <= 0){
            printf("->>>{draw,no ones win.}<<<-\n");

            clean_up(gm);
            game_over = true;
            continue;
        }

        index = get_index(); 

        if (index == -1)
        {
            printf("\n");
            return;
        }

        if(!set_mark(gm->m,gm->tab,index-1)){
            continue;
        }
        
        gm->empthy_count--;


        eval = check_win(gm->tab);  

    } 
}

void game(char mark){
    game_info *gm = game_init(mark);//call form logic side to init game info.
    game_start(gm);// here is the actuale game loop.
}

int get_index_bot(const int *tab){
    return bot_index(tab);
}
void game_start_solo(game_info *gm){
    bool game_over = false;

    bool is_bot_round;

    if (gm->m->last_round == gm->m->bot)
    {
        is_bot_round = true;
    }else{
        is_bot_round = false;
    }
    
    int eval;
    int index;

    while (!game_over)
    {
        printf("[-<player with %c round>-]",gm->m->last_round);
        print_border(gm);

        if (eval == 1)
        {
            char winner = (gm->m->last_round == gm->m->player)?gm->m->bot:gm->m->player;
            int winner_num = (gm->m->last_round == gm->m->player)?2:1;
            printf("->>>{player %d,with mark %c was win.}<<<-\n",winner_num,winner);

            clean_up(gm);
            game_over = true;
            continue;  
        }else if(eval == 0 && gm->empthy_count <= 0){
            printf("->>>{draw,no ones win.}<<<-\n");

            clean_up(gm);
            game_over = true;
            continue;
        }

        if (is_bot_round)
        {   
            index = get_index_bot(gm->tab);
            while (gm->tab[index] != EMPTHY)
            {
                index = get_index_bot(gm->tab);
            }
            is_bot_round = false;
        }else{
            index = get_index();
            is_bot_round = true;
        }
        
        if (index == -1)
        {
            printf("\n");
            return;
        }

        if(!set_mark(gm->m,gm->tab,index-1)){
            continue;
        }
        
        gm->empthy_count--;

        eval = check_win(gm->tab);

    }
    
}

void game_solo(char mark){
    game_info *gm = game_init(mark);
    game_start_solo(gm);
}