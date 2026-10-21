#include <stdlib.h>
#include "game_logic.h"
#include "ai_stratigie.h"

int bot_index_0(const int *tab){
    int index;
    do{
        index = rand()%9;
    }while (tab[index] != EMPTHY);
    return index;
}

int bot_index_1(const int *tab){
    int index;
    if (tab[4] == EMPTHY)
    {
        return 4;
    }
    do{
        index = rand()%9;
    }while (tab[index] != EMPTHY);
    return index;
}

int bot_index_2(const int *tab){
        int index;

        int bot_indexs[4];
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
            if (tab[4] == -1)
            {
                return 4;
            }
            
        }
        
        int sum = 0;
        for (int i = 0; i < count; i++)
        {
            sum += bot_indexs[i];
        }
        
        int requiested_index;

            if (sum == 9 || sum == 3 || sum == 12)
            {
                requiested_index = 0;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 11 || sum == 2)
            {
                requiested_index = 1;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 1 || sum == 12)
            {
                requiested_index = 2;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 6|| sum == 2)
            {
                requiested_index= 3;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }
            else if (sum == 8)
            {
                requiested_index = 4;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 10 || sum == 7)
            {
                requiested_index = 5;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 3 || sum == 6 || sum == 15)
            {
                requiested_index = 6;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 14 || sum == 5)
            {
                requiested_index = 7;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            }else if (sum == 13 || sum == 4 || sum == 7)
            {
                requiested_index = 8;
                if (tab[requiested_index] != -1)
                {
                    requiested_index = index;
                }
                return requiested_index;
            } 
}

int bot_index_3(const int *tab){
    
}

int bot_index_4(const int *tab){
    
}
