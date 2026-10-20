#include <stdlib.h>
#include "game_logic.h"
#include "ai_stratigie.h"

int bot_index(const int *tab){
    int index;

    do{ 
            index = rand()%10;
        
    }while (tab[index] != -1);
    return index;
}