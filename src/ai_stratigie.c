#include <stdlib.h>
#include <limits.h>
#include "game_logic.h"
#include "ai_stratigie.h"


static bool check_win_in(int arr[][3], int size, const int *arr_e, int arr_size)
{
    if (arr == NULL || arr_e == NULL || size <= 0 || arr_size != 3) {
        return false;
    }

    if (arr_e[0] == arr_e[1] ||
        arr_e[0] == arr_e[2] ||
        arr_e[1] == arr_e[2]) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        bool all_found = true;

        for (int k = 0; k < arr_size; k++) {
            bool found = false;

            for (int j = 0; j < 3; j++) {
                if (arr_e[k] == arr[i][j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                all_found = false;
                break;
            }
        }

        if (all_found) {
            return true;
        }
    }

    return false;
}

static int choose_empty_corner(const int tab[9], const bot_info *b)
{
    int available[4];
    int count = 0;

    for (int i = 0; i < b->counter_corner && i < 4; i++) {
        int square = b->corner[i];

        if (square >= 0 && square < 9 && tab[square] == EMPTHY) {
            available[count++] = square;
        }
    }

    if (count == 0) {
        return -1;
    }

    return available[rand() % count];
}

static int choose_empty_square(const int tab[9])
{
    for (int i = 0; i < 9; i++) {
        if (tab[i] == EMPTHY) {
            return i;
        }
    }

    return -1;
}

static int find_tactical_move(const int tab[9], bot_info *b, int mark)
{
    int marks[9];
    int mark_count = 0;

    for (int i = 0; i < 9; i++) {
        if (tab[i] == mark) {
            marks[mark_count++] = i;
        }
    }

    for (int a = 0; a < mark_count; a++) {
        for (int c = a + 1; c < mark_count; c++) {
            for (int move = 0; move < 9; move++) {
                if (tab[move] != EMPTHY) {
                    continue;
                }

                if ((marks[a] + marks[c] + move) % 3 != 0) {
                    continue;
                }

                b->arr_element[0] = marks[a];
                b->arr_element[1] = marks[c];
                b->arr_element[2] = move;
                b->size_e = 3;

                if (check_win_in(b->win_arr, b->size_a,
                                 b->arr_element, b->size_e)) {
                    return move;
                }
            }
        }
    }

    return -1;
}


int bot_index_0(const int *tab){
    int empty[9];
    int count = 0;

    if (tab == NULL) {
        return -1;
    }

    for (int i = 0; i < 9; i++) {
        if (tab[i] == EMPTHY) {
            empty[count++] = i;
        }
    }

    return count == 0 ? -1 : empty[rand() % count];
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
        }else if (count > 2)
        {
            return index;
        }
        

        int requiested_index = -1;

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

                        if (check_win_in(win_arr,size_arr,element_arr,3))
                        {
                            requiested_index = i;
                        }
                    } 
            }
        }

        if (requiested_index == -1 || tab[requiested_index] != EMPTHY)
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
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
            }
        }else if (count == 1)
        {
            if (tab[4] == -1)
            {
                return 4;
            }else{

                int conner_arr[4] = {0,2,6,8};
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
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
            if (tab[i] == BOT)
            {
                bot_indexs[count] = i;
                count++;
            }
            if (tab[i] == PLAYER)
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
                for (int i = 0; i < 4; i++) {
                    int conren_index = rand()%4;
                    if (tab[conner_arr[conren_index]] == EMPTHY) {
                        return conner_arr[conren_index];
                    }
                }
                return bot_index_0(tab);
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
                    index = rand()%9;
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

int bot_index_5(const int tab[9], bot_info *b)
{
    if (tab == NULL || b == NULL || b->arr_element == NULL) {
        return -1;
    }

    int count_bot = 0;
    int count_player = 0;
    int first_player_mark = -1;

    for (int i = 0; i < 9; i++) {
        if (tab[i] == BOT) {
            count_bot++;
        } else if (tab[i] == PLAYER) {
            if (first_player_mark == -1) {
                first_player_mark = i;
            }
            count_player++;
        }
    }

    if (count_bot == 0 && tab[4] == EMPTHY) {
        return 4;
    }

    if (b->bot_init_value && count_bot == 1 && tab[4] == BOT) {
        int opposite_corner = -1;

        switch (first_player_mark) {
            case 0: opposite_corner = 8; break;
            case 2: opposite_corner = 6; break;
            case 6: opposite_corner = 2; break;
            case 8: opposite_corner = 0; break;
            default: break;
        }

        if (opposite_corner != -1 && tab[opposite_corner] == EMPTHY) {
            return opposite_corner;
        }

        int corner = choose_empty_corner(tab, b);
        if (corner != -1) {
            return corner;
        }
    }

    int move = find_tactical_move(tab, b, BOT);
    if (move != -1) {
        return move;
    }

    move = find_tactical_move(tab, b, PLAYER);
    if (move != -1) {
        return move;
    }

    move = choose_empty_corner(tab, b);
    if (move != -1) {
        return move;
    }

    return choose_empty_square(tab);
}

typedef struct minimax_node node;
struct minimax_node {
    int curr_tab[9];
    int empthy_arr[9];
    int index;
    int eval;
    round_whO round;
    int empthy_case;
    node **childs;
};

#define EVAL_UNKNOWN (-2)

static const int WIN_LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {6, 4, 2}
};

static int winner_mark(const int tab[9])
{
    if (tab == NULL) {
        return EMPTHY;
    }

    for (int i = 0; i < 8; i++) {
        int a = WIN_LINES[i][0];
        int b = WIN_LINES[i][1];
        int c = WIN_LINES[i][2];

        if (tab[a] != EMPTHY && tab[a] == tab[b] && tab[b] == tab[c]) {
            return tab[a];
        }
    }

    return EMPTHY;
}

static int count_e(const int tab[9])
{
    if (tab == NULL) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (tab[i] == EMPTHY) {
            count++;
        }
    }

    return count;
}

static node *create_node(const int tab[9], int index, round_whO round)
{
    if (tab == NULL || (round != BOT && round != PLAYER)) {
        return NULL;
    }

    node *n = calloc(1, sizeof(*n));
    if (n == NULL) {
        return NULL;
    }

    for (int i = 0; i < 9; i++) {
        n->curr_tab[i] = tab[i];
    }

    n->index = index;
    n->round = round;
    n->eval = EVAL_UNKNOWN;

    for (int i = 0; i < 9; i++) {
        if (n->curr_tab[i] == EMPTHY) {
            n->empthy_arr[n->empthy_case++] = i;
        }
    }

    return n;
}

static void free_tree(node *n)
{
    if (n == NULL) {
        return;
    }

    if (n->childs != NULL) {
        for (int i = 0; i < n->empthy_case; i++) {
            free_tree(n->childs[i]);
        }
        free(n->childs);
    }

    free(n);
}

static node *create_tree(const int tab[9], int index, round_whO round)
{
    node *n = create_node(tab, index, round);
    if (n == NULL) {
        return NULL;
    }

    int winner = winner_mark(n->curr_tab);
    if (winner != EMPTHY) {
        n->eval = (winner == BOT) ? 1 : -1;
        return n;
    }

    if (n->empthy_case == 0) {
        n->eval = 0;
        return n;
    }

    n->childs = calloc((size_t)n->empthy_case, sizeof(*n->childs));
    if (n->childs == NULL) {
        free_tree(n);
        return NULL;
    }

    for (int i = 0; i < n->empthy_case; i++) {
        int move = n->empthy_arr[i];
        int child_tab[9];

        for (int j = 0; j < 9; j++) {
            child_tab[j] = n->curr_tab[j];
        }
        child_tab[move] = n->round;

        round_whO next_round = (n->round == BOT) ? PLAYER : BOT;
        n->childs[i] = create_tree(child_tab, move, next_round);

        if (n->childs[i] == NULL) {
            free_tree(n);
            return NULL;
        }
    }

    return n;
}

static int minimax_algo(node *n)
{
    if (n == NULL) {
        return 0;
    }

    if (n->eval != EVAL_UNKNOWN) {
        return n->eval;
    }

    bool found_child = false;

    if (n->round == BOT) {
        int best = INT_MIN;

        for (int i = 0; i < n->empthy_case; i++) {
            if (n->childs == NULL || n->childs[i] == NULL) {
                continue;
            }

            int child_eval = minimax_algo(n->childs[i]);
            if (child_eval > best) {
                best = child_eval;
            }
            found_child = true;
        }

        n->eval = found_child ? best : 0;
    } else {
        int best = INT_MAX;

        for (int i = 0; i < n->empthy_case; i++) {
            if (n->childs == NULL || n->childs[i] == NULL) {
                continue;
            }

            int child_eval = minimax_algo(n->childs[i]);
            if (child_eval < best) {
                best = child_eval;
            }
            found_child = true;
        }

        n->eval = found_child ? best : 0;
    }

    return n->eval;
}

static bool same_board(const int a[9], const int b[9])
{
    if (a == NULL || b == NULL) {
        return false;
    }

    for (int i = 0; i < 9; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

static node *promote_child(node *parent, int chosen_slot)
{
    if (parent == NULL || parent->childs == NULL ||
        chosen_slot < 0 || chosen_slot >= parent->empthy_case ||
        parent->childs[chosen_slot] == NULL) {
        return NULL;
    }

    node *chosen = parent->childs[chosen_slot];

    for (int i = 0; i < parent->empthy_case; i++) {
        if (i != chosen_slot) {
            free_tree(parent->childs[i]);
        }
    }

    free(parent->childs);
    free(parent);
    return chosen;
}

static node *sync_root(node *root, const int tab[9])
{
    if (root == NULL) {
        return NULL;
    }

    if (same_board(root->curr_tab, tab)) {
        return root;
    }

    if (root->childs != NULL) {
        for (int i = 0; i < root->empthy_case; i++) {
            node *child = root->childs[i];
            if (child != NULL && same_board(child->curr_tab, tab)) {
                return promote_child(root, i);
            }
        }
    }

    free_tree(root);
    return NULL;
}

static int best_child_slot(const node *root)
{
    if (root == NULL || root->round != BOT || root->childs == NULL) {
        return -1;
    }

    int best_slot = -1;
    int best_eval = INT_MIN;

    for (int i = 0; i < root->empthy_case; i++) {
        const node *child = root->childs[i];
        if (child != NULL && child->eval > best_eval) {
            best_eval = child->eval;
            best_slot = i;
        }
    }

    return best_slot;
}

static node *bot6_root = NULL;

int bot_index_6(const int *tab)
{
    if (tab == NULL) {
        return -1;
    }

    if (bot6_root != NULL) {
        bot6_root = sync_root(bot6_root, tab);
    }

    if (bot6_root == NULL) {
        bot6_root = create_tree(tab, -1, BOT);
    }

    if (bot6_root == NULL) {
        return -1;
    }

    if (!same_board(bot6_root->curr_tab, tab) || bot6_root->round != BOT) {
        return -1;
    }

    if (winner_mark(tab) != EMPTHY || count_e(tab) == 0) {
        return -1;
    }

    (void)minimax_algo(bot6_root);

    int slot = best_child_slot(bot6_root);
    if (slot == -1) {
        return -1;
    }

    node *chosen = bot6_root->childs[slot];
    int move = chosen->index;

    if (move < 0 || move >= 9 || tab[move] != EMPTHY) {
        return -1;
    }

    bot6_root = promote_child(bot6_root, slot);
    if (bot6_root == NULL) {
        return -1;
    }

    return move;
}

void reset_bot_index_6(void)
{
    free_tree(bot6_root);
    bot6_root = NULL;
}
