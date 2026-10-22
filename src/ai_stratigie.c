#include <stdlib.h>
#include "game_logic.h"
#include "ai_stratigie.h"

static bool check_win_in(int arr[9][3],const int size,const int *arr_e){
    for (int i = 0; i < size; i++)
    {
        int y =0;
        while (y < 3)
        {
            bool is_equal = false;

            for (int j = 0; j < 3; j++)
            {
                if (arr_e[y] == arr[i][j])
                {
                    is_equal = true;
                    break;
                }
            } 

            if (is_equal)
            {
                y++;
            }else{
                break;
            }  
        }
        if (y == 3)
        {
            return true;
        }
    }
    return false;
}

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
    return bot_index_0(tab); 
}

int bot_index_2(const int *tab){
        int index = bot_index_1(tab);

        int bot_indexs[5];
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
            return index;
        }else if (count > 3)
        {
            return index;
        }
        

        int requiested_index;

        int win_arr[9][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{6,4,2}};
        int size_arr = sizeof(win_arr)/sizeof(win_arr[0][0]);
        int element_arr[3];

        for (int i = 0; i < 9; i++)
        {
            if ((bot_indexs[0]+bot_indexs[1]+i)%3 == 0)
            {
                if (bot_indexs[0] != i && i != bot_indexs[1])
                    {   
                        element_arr[0] = bot_indexs[0];
                        element_arr[1] = bot_indexs[1];
                        element_arr[2] = i;
                        
                        if (check_win_in(win_arr,size_arr,element_arr))
                        {
                            requiested_index = i;
                        }
                    } 
            }
        }

        if (tab[requiested_index] != EMPTHY)
        {
            requiested_index = index;
        }
         

        return requiested_index;
}

int bot_index_3(const int *tab){
        int bot_indexs[5];
        int count = 0;
        int index;

        for (int i = 0; i < 9; i++)
        {
            if (tab[i] == 1)
            {
                bot_indexs[count] = i;
                count++;
            }
        }

        if (count == 0)
        {
            if (tab[4] == -1)
            {
               return 4;
            }else{
                int conner_arr[4] = {0,2,6,8};
                int conren_index;

                do{
                 conren_index = rand()%4;

                }while(tab[conner_arr[conren_index]] != -1);
                index = conner_arr[conren_index];
                return index;
            }
        }else if (count == 1)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{

                int conner_arr[4] = {0,2,6,8};
                int conren_index;

                do{
                 conren_index = rand()%4;

                }while(tab[conner_arr[conren_index]] != -1);

                index = conner_arr[conren_index];
    
                return index;
            }
        }else if (count == 2)
        {
            return bot_index_2(tab);
        }
        return bot_index_0(tab);
}

int bot_index_4(const int *tab){
        int bot_indexs[5];
        int count = 0;

        int index = bot_index_0(tab);

        int player_indexs[5];
        int count_player  = 0;

        for (int i = 0; i < 9; i++)
        {
            if (tab[i] == 1)
            {
                bot_indexs[count] = i;
                count++;
            }
            if (tab[i] == 0)
            {
                player_indexs[count_player] = i;
                count_player++;
            }  
        }

        if (count == 0)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{

                int conner_arr[4] = {0,2,6,8};
                int conren_index;

                {
                 conren_index = rand()%4;
                }while(tab[conner_arr[conren_index]] != -1);

                index = conner_arr[conren_index];
                return index;
            }
        }else if (count == 1)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{
                if (count_player == 1)
                {
                    do{ 
                    index = rand()%10;
                    }while (tab[index] != -1);
                    return index;
                }
                
                return index;
            }
        }else if (count == 2)
        {
            return bot_index_2(tab);
        }
    return bot_index_0(tab);
}
/*
int bot_index_5(const int *tab){
    int bot_marks[5];
    int player_marks[5];
    int corner[4] = {0,2,6,8};
    int counter_corner = 3;
    int base = 4;

    int sum_player = 0;
    int sum_bot = 0;

    int count_bot = 0;
    int count_player = 0;

    bool bot_i = false;
    for (int i = 0; i < 9; i++)
    {
        if (tab[i] != BOT)
        {
            bot_marks[count_bot] = i;
            count_bot++;
        }else if (tab[i] != PLAYER)
        {
            player_marks[count_player] = i;
            count_player++;
        }
    }

    if (bot_init_value )
    {
        if (count_bot > count_player)
        {
            bot_i = true;
        }else{
            bot_i = false;
        }  
    }

    if (bot_i){      
            if (count_bot == 0)
            {
                return 4;   
                sum_bot += 4;
            }else if (count_bot == 1)
            {
                //take  corner 
                //-------------------------------------------------------//
                int index_corner = rand()%base;

                int requiested_index;

                if ((player_marks[count_player-1]+4+corner[index_corner])%3 == 0)
                    {
                        element_arr[0] = bot_marks[0];
                        element_arr[1] = bot_marks[1];
                        element_arr[2] = i;
                        if (check_win_in())
                        {
                            
                        }
                        
                        for (int i = index_corner; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner] = -1;
                        counter_corner--;
                        base--;
                        int temp ;
                        for (int i = 0; i < counter_corner; i++)
                        {
                            if (player_marks[count_player-1]==corner[i])
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (int i = temp; i < count_player; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner-1] = -1;
                        counter_corner--;
                        base--;    
                    }

                    index_corner = rand()%base;

                while (tab[corner[index_corner]] != -1)
                {
                    index_corner = rand()%base;
                    
                    if ((player_marks[count_player-1]+4+corner[index_corner])%3 == 0)
                    {
                        for (int i = index_corner; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner] = -1;
                        counter_corner--;
                        base--;
                        int temp ;
                        for (int i = 0; i < counter_corner; i++)
                        {
                            if (player_marks[count_player-1]==corner[i])
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (int i = temp; i < count_player; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner-1] = -1;
                        counter_corner--;
                        base--;    
                    }
                }
                
                int res = set_mark_sp(m,tab,corner[index_corner],bot_marks,count_bot);
                if (res == -1)
                {
                    fprintf(stderr,"problems appear when setting mark.\n");
                    return;
                }else{
                    count_bot = res;
                }
                
                sum_bot += index_corner;
                //---------------------------------------------------------------------//
            }else if (count_bot == 2)
            {
                
                //-------------------------------------------------------//
                bool exit = false;

                int win_arr[9][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{6,4,2}};
                int size_arr = sizeof(win_arr)/sizeof(win_arr[0][0]);
                int element_arr[3];

                element_arr[0] = bot_marks[0];
                element_arr[1] = bot_marks[1];
                element_arr[2] = 2;
                if (check_win_in(win_arr,size_arr,element_arr))
                {
                            
                }
                for (int i = 0; i < 9; i++)
                {   
                    for (int j = 0; j < count_player; j++)
                        {
                            if(player_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }
                    
                    if (exit)
                    {
                        exit = false;
                        continue;
                    }
                    
                    if ((sum_player + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                            int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }
                exit = false;
                //-----------------------------------------------------------//
                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < count_bot; j++)
                        {
                            if(bot_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }

                    if (exit)
                    {
                        exit = false;
                        continue;
                    }
                    
                    if ((sum_bot + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                            int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }
                //------------------------------------------//
                int index_corner = rand()%base;

                if ((player_marks[count_player-1]+4+corner[index_corner])%3 == 0)
                    {
                        for (int i = index_corner; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner] = -1;
                        counter_corner--;
                        base--;
                        int temp ;
                        for (int i = 0; i < counter_corner; i++)
                        {
                            if (player_marks[count_player-1]==corner[i])
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (int i = temp; i < count_player; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner-1] = -1;
                        counter_corner--;
                        base--;    
                    }

                    index_corner = rand()%base;

                while (tab[corner[index_corner]] != -1)
                {
                    index_corner = rand()%base;
                    
                    if ((player_marks[count_player-1]+4+corner[index_corner])%3 == 0)
                    {
                        for (int i = index_corner; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner] = -1;
                        counter_corner--;
                        base--;
                        int temp ;
                        for (int i = 0; i < counter_corner; i++)
                        {
                            if (player_marks[count_player-1]==corner[i])
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (int i = temp; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner-1] = -1;
                        counter_corner--;
                        base--;    
                    }
                }
                
                int res = set_mark_sp(m,tab,corner[index_corner],bot_marks,count_bot);
                if (res == -1)
                {
                    fprintf(stderr,"problems appear when setting mark.\n");
                    return;
                }else{
                    count_bot = res;
                }
                
                sum_bot += corner[index_corner];
                //-------------------------------------------//

            }else if (count_bot == 3)
            {
                //------------------------------------------------------------------------------//
                int first_sum = player_marks[count_player-1]+player_marks[count_player-2];
                int second_sum = player_marks[count_player-1]+player_marks[count_player-3];

                bool exit = true;

                for (int i = 0; i < 9; i++)
                {   
                    for (int j = 0; j < count_player; j++)
                        {
                            if(player_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }
                    
                    if (exit)
                    {
                        exit = false;
                        continue;
                    }

                    if ((first_sum + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                            int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }

                exit = false;

                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < count_player; j++)
                        {
                            if(player_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }

                    if (exit)
                    {
                        exit = false;
                        continue;
                    }
                    
                    if ((second_sum + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                            int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }
                //----------------------------------------------------------------//
                first_sum = bot_marks[count_bot-1]+bot_marks[count_bot-2];
                second_sum = bot_marks[count_bot-1]+bot_marks[count_bot-3];

                exit = false;

                for (int i = 0; i < 9; i++)
                {   
                    for (int j = 0; j < count_bot; j++)
                        {
                            if(bot_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }
                    
                    if (exit)
                    {
                        exit = false;
                        continue;
                    }

                    if ((first_sum + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                             int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }

                exit = false;

                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < count_bot; j++)
                        {
                            if(bot_marks[j] == i){
                                exit = true;
                                break;
                            } 
                        }

                    if (exit)
                    {
                        exit = false;
                        continue;
                    }
                    
                    if ((second_sum + i)%3 == 0)
                    {
                        if (tab[i] == -1)
                        {
                            int res = set_mark_sp(m,tab,i,bot_marks,count_bot);
                            if (res == -1)
                            {
                                fprintf(stderr,"problems appear when setting mark.\n");
                                return;
                            }else{
                                count_bot = res;
                            }
                            
                            sum_bot += i;
                            return;
                        }     
                    } 
                }
                //---------------------------------------------------------------------------------//

                index = rand()%9;

                while (tab[index] != -1)
                {
                    index = rand()%9;
                    
                }
                
            }else if (count_bot == 4)
            {
                index = rand()%9;

                while (tab[index] != -1)
                {
                    index = rand()%9; 
                }
                int res = set_mark_sp(m,tab,index,bot_marks,count_bot);
                if (res == -1)
                {
                    fprintf(stderr,"problems appear when setting mark.\n");
                    return;
                }else{
                    count_bot = res;
                }        
                sum_bot += index;
            }else if (count_bot == 5)
            {
                index = rand()%9;

                while (tab[index] != -1)
                {
                    index = rand()%9; 
                }
                int res = set_mark_sp(m,tab,index,bot_marks,count_bot);
                if (res == -1)
                {
                    fprintf(stderr,"problems appear when setting mark.\n");
                    return;
                    }else{
                    count_bot = res;
                    }        
                sum_bot += index;
            }  
        }else{
            int bot_marks[5];
            int player_marks[4];

            int corner[4] = {0,2,6,8};
            int mids[4] = {1,3,5,7};
            int counter_mids = 4;
            int base_mids = 4;
            int counter_corner = 4;
            int base_corner = 4;

            int sum_player = 0;
            int sum_bot = 0;

            int count_bot = 0;
            int count_player = 0;

            if (count_bot == 0)
            {
                if (tab[4] == -1)
                {
                    int res = set_mark_sp(m,tab,4,bot_marks,count_bot);
                    if (res == -1)
                    {
                        fprintf(stderr,"problems appear when setting mark.\n");
                        return;
                    }else{
                        count_bot = res;
                    }        
                    sum_bot += 4;
                }else{

                    int index_corner = rand()%base_corner;
                    int res = set_mark_sp(m,tab,corner[index_corner],bot_marks,count_bot);
                    if (res == -1)
                    {
                        fprintf(stderr,"problems appear when setting mark.\n");
                        return;
                    }else{
                        count_bot = res;
                    }
                    sum_bot += corner[index_corner];

                    for (int i = index_corner; i < counter_corner; i++)
                        {
                            corner[i] = corner[i+1];
                        }
                        corner[counter_corner-1] = -1;
                        counter_corner--;
                        base_corner--; 
                }
            }else if (count_bot == 1)
            {
                
            }else if (count_bot == 2)
            {
                
            }
            else if(count_bot == 3)
            {

            }else if (count_bot == 4)
            {
                
            } 
        }  
}*/