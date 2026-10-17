#include <stdio.h>
#include <stdbool.h>
#include "ai_stratigie.h"
#include "game_logic.h"
#include "internals.h"

static void flush_line(void) {          
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    }

int read_input(int *var) {    
    int res = scanf("%d", var);
    if (res == EOF) {
        return -1;
    }
    flush_line();
    return (res == 1)?1:0;
    }  

void interface0(){
    int choice_main;

    printf(">>>>>>>>>>>===========<<<<<<<<<<<\n");
    printf("welcome to tic tac toe game...\n");
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
            printf("test case 1.\n");
            break;
        case 2:
            printf("test case 2 .. \n");
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


void interface1(){

}


void interface2(){

}