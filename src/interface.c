#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

static int game_interface(int option,char mark,gm_i *i){
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
                    if (i->diff == -1)
                    {
                        i->multi_player(mark);
                    }else{
                        i->solo(mark,i->diff);
                    }

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
            gm_i *gmi = malloc(sizeof(gm_i));
            gmi->multi_player = game;
            gmi->diff = -1;
            int temp = game_interface(option,mark,gmi);//interface connect loigc game whit user interface
            if(temp == -1){
                if (gmi == NULL)
                {
                    fprintf(stderr,"null pointer.\n");
                    exit(1);
                }
                free(gmi);
                printf("\n");
                return;
            }
            if (gmi == NULL)
                {
                    fprintf(stderr,"null pointer.\n");
                    exit(1);
                }
            free(gmi);
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

static int read_diffuclty_level_for_bot(){
        
        int diffuclty;

        while (true)
        {
            printf(">>========<<\n");
            printf(">>diffucly<<\n");
            printf(">>========<<\n");
            printf("-------------------------------------------------\n");
            printf("choose bot diffuclty.\n");
            printf("0-friendly(random moves.)\n");
            printf("1-bigginer(just take the center from you.)\n");
            printf("2-amateur(try to win agains you in some moves.)\n");
            printf("3-mid-easy(do some effort agains you.)\n");
            printf("4-mid(try to win in any move.)\n");
            printf("-------------------------------------------------\n");

            
            int resl = read_input(&diffuclty);
            if (resl == -1)
            {
                return -1;
            } 

            if (resl != 1)
            {
                printf("please give the correct option(number of option).\n");
                continue;
            } 
            if (diffuclty<0 || diffuclty > 4)
            {
                printf("please give the correct option.\n");
                continue;
            }
            break;
        }
        
        return diffuclty;   
}

void interface2(){
    int option;
    char mark;
    int diff;

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

        diff = read_diffuclty_level_for_bot();
        
        
        if (option == 1)
        {
            gm_i *gmi = malloc(sizeof(gm_i));
            gmi->solo = game_solo;
            gmi->diff = diff;
            int temp = game_interface(option,mark,gmi);//interface connect loigc game whit user interface
            if(temp == -1){
                if (gmi == NULL)
                {
                    fprintf(stderr,"null pointer.\n");
                    exit(1);
                }
                free(gmi);
                printf("\n");
                return;
            }

            if (gmi == NULL)
            {
                fprintf(stderr,"null pointer.\n");
                exit(1);
            }

            free(gmi);
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

            clean_up(&gm);
            game_over = true;
            continue;  
        }else if(eval == 0 && gm->empthy_count <= 0){
            printf("->>>{draw,no ones win.}<<<-\n");

            clean_up(&gm);
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
    game_info *gm = game_init(mark,-1,NULL);//call form logic side to init game info.
    game_start(gm);// here is the actuale game loop.
}

int get_index_bot(game_info *gm){
    return gm->stratigie(gm->tab);
}

static void print_game_stats(game_info *gm,bool is_bot_round){
    if (is_bot_round)
        {
            printf("[-bot with %c round>-]",gm->m->bot);
        }else{
            printf("[-<player with %c round>-]",gm->m->player);
        }
        
        print_border(gm);
}
static bool check_who_start(game_info *gm){
    if (gm->m->last_round == gm->m->bot)
    {
        return true;
    }
    return false;
}

static void print_winner(game_info *gm){
    if (gm->m->last_round == gm->m->player)
    {
        printf("->>>{bot,with mark %c was win.}<<<-\n",gm->m->bot);
    }else
    {
        printf("->>>{player,with mark %c was win.}<<<-\n",gm->m->player);
    }  
}

static bool check_winning_or_draw(game_info *gm,int eval){
        if (eval == 1)
        { 
            print_winner(gm);
            clean_up(&gm);
            return true; 
        }else if(eval == 0 && gm->empthy_count <= 0){
            printf("->>>{draw,no ones win.}<<<-\n");
            clean_up(&gm);
            return true;
        }
        return false;
}

static int get_index_interface(game_info *gm,bool *bot){

        int i;

        if (*bot)
        {   
            i = get_index_bot(gm);
            *bot = false;
        }else{
            do{
                i = get_index()-1;

                if (i + 1 == -1)
                {
                    printf("\n");
                    return -1;
                }

                print_game_stats(gm,bot);
            }while (gm->tab[i] != EMPTHY);

            *bot = true;
        }
        return i;
}

void game_start_solo(game_info *gm){

    bool is_bot_round = check_who_start(gm);
    
    int eval = -1;// just inint with any value for now 
    int index;

    while (true)
    {
        print_game_stats(gm,is_bot_round);

        if (check_winning_or_draw(gm,eval))
        {
            break;
        }
        
        index = get_index_interface(gm,&is_bot_round);
     
        if (index == -1)
        {
            printf("\n");
            return;
        }
        
       
        while(!set_mark(gm->m,gm->tab,index));

        gm->empthy_count--;

        eval = check_win(gm->tab);
    } 
}

bool bot_init_value = true;

void game_solo(char mark,int diff){
    bot_move *arr_st = create_stratigie_bot();

    if (arr_st == NULL)
    {
        fprintf(stderr,"invalid pointer: null pointer.\n");
        exit(1);
    }

    game_info *gm = game_init(mark,diff,arr_st);

    game_start_solo(gm);

    if (!bot_init_value)
    {
        bot_init_value = true;
    }
    
    free(arr_st);
    arr_st = NULL;
}