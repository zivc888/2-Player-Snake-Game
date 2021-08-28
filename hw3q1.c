/*=========================================================================*
 *   Include files:                                                        *
 *=========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================*
 *   Constants and definitions:                                            *
 *=========================================================================*/

/* put your #defines and typedefs here*/
#define N 25
#define BOARD_ELEMENT '#'

#define PERCENT 0
#define PERCENT_HEAD '%'
#define PERCENT_BODY '*'

#define SHTRODEL 1
#define SHTRODEL_HEAD '@'
#define SHTRODEL_BODY '+'

#define FIRST_PLAYER PERCENT
#define ILLEGAL_MOVE 0

#define RST_INT 0
#define RST_CHR ' '
#define FOOD 'F'

#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define UP 8

#define BI 2
#define STRT_SIZE 2

#define HEAD 0
#define XPOS 1
#define YPOS 0

/*=========================================================================*
 *   Function declaration:                                                 *
 *=========================================================================*/

void print_error_input();                             //print message - there is error in the input
void valid_input(int entries, int expected);          /*checks if the number of values that the scanf has got is equal to the expected */

void print_invalid_input();			                  //print message - re-insert valid input

void prep1(char board[N][N],int *size,int *hngr_max,int *size_prcnt,
int *size_shtrdl,int *prcnt_hngr,int *shtrdl_hngr);
void prep2(char board[N][N],int size,int prcnt_pos[N*N][BI],int size_prcnt,
int size_shtrdl,int shtrdl_pos[N*N][BI],int food_pos[BI], int *hngr_max);
                                                      /*these are the two preparation steps that are required before the actual game */

void print_board_size_msg();                          //print message to enter board size
int input_board();                                    /*checks valid input and returns the size of the board */

void initialize(char board[N][N], int size);          /*initialize the used part of the board */

void rst_vars(int *hngr_max, int *size_prcnt, int *size_shtrdl,
int *prcnt_hngr, int *shtrdl_hngr);                   /*resets a bunch of variables in function main */

void game_on(char board[N][N], int size, int *trn, int *size_prcnt,
int prcnt_pos[N*N][BI], int *size_shtrdl,
int shtrdl_pos[N*N][BI], int food_pos[BI], int hngr_max,
int *prcnt_hngr, int *shtrdl_hngr);                   /*contains everything that happens during the game itself */

void print_introduction_msg();                        //print welcome message , and introduction message to the game

void fill_board_with_elements(char board[N][N], int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl,
int shtrdl_pos[N*N][BI], int food_pos[BI]);           /*put the elements (snakes and food) on the board */

void print_steps_without_food();                      //print message to enter maximum number of steps can snake do without food
void print_food_location_msg();                       //print message to insert place for next food

int no_food();                                        /*checks valid input and returns the life length of the snake (how long can it survive foodless) */
void where_food(char board[N][N],int size,int food_pos[BI]);
                                                      /*checks valid input */

void full_board(char board[N][N], int size, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]);                                    /*checks if the board is full or if there are still some empty spaces */

void help_print_board(int size);                      //printing static part of the board
void print_board(char board[N][N], int size);         //print the current board for the user

void print_player_message(int player);                //print message when we switch between users
void print_insert_direction();			              //print message asking the user to insert his move

void down(int tmp_y,int tmp_x,int trn,int size_prcnt,
int prcnt_pos[N*N][BI],int size_shtrdl,int shtrdl_pos[N*N][BI]); /*move down */
void left(int tmp_y,int tmp_x,int trn,int size_prcnt,
int prcnt_pos[N*N][BI],int size_shtrdl,int shtrdl_pos[N*N][BI]); /*move left */
void right(int tmp_y,int tmp_x,int trn,int size_prcnt,
int prcnt_pos[N*N][BI],int size_shtrdl,int shtrdl_pos[N*N][BI]); /*move right */
void up(int tmp_y,int tmp_x,int trn,int size_prcnt,
int prcnt_pos[N*N][BI],int size_shtrdl,int shtrdl_pos[N*N][BI]); /*move up */

void move_common_act_percent(int tmp_y,int tmp_x,int size_prcnt,
int prcnt_pos[N*N][BI]);                              /*the atomic function of the percent movements */
void move_common_act_shtrodel(int tmp_y,int tmp_x,int size_shtrdl,
int shtrdl_pos[N*N][BI]);                             /*the atomic function of the shtrodel movements */

int switch_trn(int trn);                              /*switches the turn */

void movement_itself(int direction,int trn,int size_prcnt,
int prcnt_pos[N*N][BI],int size_shtrdl,int shtrdl_pos[N*N][BI]); /*all of the movement parts combined */
void eat(char board[N][N],int size,int trn, int *size_prcnt,
int prcnt_pos[N*N][BI],int *size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]);                                               /*eating */
void move(char board[N][N],int size,int trn,int *size_prcnt,
int prcnt_pos[N*N][BI],int *size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]);                                               /*the entire snake action - movement and eating */

bool percent_fail(int trn, char board[N][N], int prcnt_pos[N*N][BI],
int *prcnt_hngr, int hngr_max);                       /*the protocol for a percent player failure */
bool shtrodel_fail(int trn, char board[N][N], int shtrdl_pos[N*N][BI],
int *shtrdl_hngr, int hngr_max);                      /*the protocol for a shtrodel player failure */
bool fail(int trn, char board[N][N], int prcnt_pos[N*N][BI],
int shtrdl_pos[N*N][BI], int hngr_max, int *prcnt_hngr, int *shtrdl_hngr);
                                                      /*the entire failure check and execution */

void print_finish_msg(int player,int finish_reason ); //get the player who lose and the reason of losing and print message state
void print_full_board();		                      //print message - full board - no winner

/*=========================================================================*
 *   Main:                                                                 *
 *=========================================================================*/

int main(){ //12 lines
    int size,hngr_max,trn=FIRST_PLAYER,food_pos[BI]={RST_INT},size_prcnt,
    size_shtrdl,prcnt_hngr,shtrdl_hngr;
    char board[N][N];

    prep1(board,&size,&hngr_max,&size_prcnt,&size_shtrdl,&prcnt_hngr,
    &shtrdl_hngr);

    int prcnt_pos[N*N][BI]={{RST_INT,RST_INT},{RST_INT,1},{RST_INT,2}},
    shtrdl_pos[N*N][BI]={{size-1,RST_INT},{size-1,1},{size-1,2}};

    prep2(board,size,prcnt_pos,size_prcnt,size_shtrdl,shtrdl_pos,
    food_pos,&hngr_max);

    game_on(board,size,&trn,&size_prcnt,prcnt_pos,&size_shtrdl,
    shtrdl_pos,food_pos,hngr_max,&prcnt_hngr,&shtrdl_hngr);
    return 0;
}

/*=========================================================================*
 *   Function implementation:                                              *
 *=========================================================================*/

void prep1(char board[N][N],int *size,int *hngr_max,int *size_prcnt,
int *size_shtrdl,int *prcnt_hngr,int *shtrdl_hngr){
    print_introduction_msg();
    *size = input_board();
    initialize(board, *size);

    rst_vars(hngr_max,size_prcnt,size_shtrdl,prcnt_hngr,shtrdl_hngr);
}
void prep2(char board[N][N],int size,int prcnt_pos[N*N][BI],int size_prcnt,
int size_shtrdl,int shtrdl_pos[N*N][BI],int food_pos[BI], int *hngr_max){
    fill_board_with_elements(board,size_prcnt,prcnt_pos,size_shtrdl,
    shtrdl_pos,food_pos);
    *hngr_max = no_food();
    where_food(board, size, food_pos);
}

int input_board(){ //made by me - 7 lines
    int size = RST_INT;
    print_board_size_msg();
    valid_input(scanf("%d", &size), 1);
    while(size>25 || size<4){
        print_invalid_input();
        valid_input(scanf("%d", &size), 1);
    }
    return size;
}

void rst_vars(int *hngr_max, int *size_prcnt, int *size_shtrdl,
int *prcnt_hngr, int *shtrdl_hngr){ //made by me - 2 lines
    *hngr_max = *prcnt_hngr = *shtrdl_hngr = RST_INT;
    *size_prcnt = *size_shtrdl = STRT_SIZE;
}

void game_on(char board[N][N], int size, int *trn, int *size_prcnt,
int prcnt_pos[N*N][BI],int *size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI], int hngr_max, int *prcnt_hngr,
int *shtrdl_hngr){ //made by me - 11 lines
    bool game = true;
    while(game){
        fill_board_with_elements(board, *size_prcnt, prcnt_pos,
        *size_shtrdl, shtrdl_pos, food_pos);
        print_board(board, size);
        move(board, size, *trn, size_prcnt, prcnt_pos, size_shtrdl,
        shtrdl_pos, food_pos);
        game = fail(*trn, board, prcnt_pos, shtrdl_pos,
        hngr_max, prcnt_hngr, shtrdl_hngr);
        *trn = switch_trn(*trn);
        initialize(board, size);
    }
}

int no_food(){ //made by me - 7 lines
    int hngr_max = RST_INT;
    print_steps_without_food();
    valid_input(scanf("%d", &hngr_max), 1);
    while(hngr_max<2){
        print_invalid_input();
        valid_input(scanf("%d", &hngr_max), 1);
    }
    return hngr_max;
}
void where_food(char board[N][N], int size, int food_pos[BI]){ //made by me - 8 lines
    print_food_location_msg();
    valid_input(scanf("%d%d", &food_pos[YPOS], &food_pos[XPOS]), 2);

    while(food_pos[YPOS]<RST_INT || food_pos[YPOS]>size-1 ||
    food_pos[XPOS]<0 || food_pos[XPOS]>size-1 ||
    board[food_pos[YPOS]][food_pos[XPOS]]!=RST_CHR){
        print_invalid_input();
        valid_input(scanf("%d%d", &food_pos[YPOS], &food_pos[XPOS]), 2);
    }
}

void full_board(char board[N][N], int size, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]){ //made by me - 12 lines
    int count=RST_INT;
    for(int i=RST_INT; i<size;i++){
        for(int j=RST_INT; j<size; j++){
            if(board[i][j]!=RST_CHR){
                count++;
            }
        }
    }
    if(count==size*size){
        food_pos[YPOS]=food_pos[XPOS]=size+1;
        fill_board_with_elements(board, size_prcnt, prcnt_pos,
        size_shtrdl, shtrdl_pos, food_pos);
        print_board(board, size);
        print_full_board();
        exit(RST_INT);
    }
}

void initialize(char board[N][N], int size){ //made by me - 3 lines
    for(int i=RST_INT; i<size; i++){
        for(int j=RST_INT; j<size; j++){
            board[i][j] = RST_CHR;
        }
    }
}

void fill_board_with_elements(char board[N][N], int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl,
int shtrdl_pos[N*N][BI], int food_pos[BI]){ //made by me - 7 lines
    board[prcnt_pos[HEAD][YPOS]][prcnt_pos[HEAD][XPOS]] = PERCENT_HEAD;
    for(int i=1; i<=size_prcnt; i++){
        board[prcnt_pos[i][YPOS]][prcnt_pos[i][XPOS]] = PERCENT_BODY;
    }

    board[shtrdl_pos[HEAD][YPOS]][shtrdl_pos[HEAD][XPOS]] = SHTRODEL_HEAD;
    for(int i=1; i<=size_shtrdl; i++){
        board[shtrdl_pos[i][YPOS]][shtrdl_pos[i][XPOS]] = SHTRODEL_BODY;
    }

    board[food_pos[YPOS]][food_pos[XPOS]] = FOOD;
}

void move(char board[N][N],int size,int trn,int *size_prcnt,
int prcnt_pos[N*N][BI],int *size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]){ //made by me - 12 lines
    int direction = RST_INT;
    print_player_message(trn);
    print_insert_direction();
    valid_input(scanf("%d", &direction), 1);

    while(!(direction==DOWN || direction==LEFT ||
    direction==RIGHT || direction==UP)){
        print_invalid_input();
        valid_input(scanf("%d", &direction), 1);
    }

    movement_itself(direction, trn, *size_prcnt, prcnt_pos,
    *size_shtrdl, shtrdl_pos);
    eat(board, size, trn, size_prcnt, prcnt_pos, size_shtrdl,
    shtrdl_pos, food_pos);
}

bool fail(int trn, char board[N][N], int prcnt_pos[N*N][BI],
int shtrdl_pos[N*N][BI], int hngr_max, int *prcnt_hngr, int *shtrdl_hngr){ //made by me - 3 lines
    if(trn==PERCENT){
        return percent_fail(trn, board, prcnt_pos, prcnt_hngr, hngr_max);
    }
    else{
        return shtrodel_fail(trn,board,shtrdl_pos, shtrdl_hngr, hngr_max);
    }
}
bool percent_fail(int trn,char board[N][N],int prcnt_pos[N*N][BI],
int *prcnt_hngr,int hngr_max){ //made by me - 12 lines
    (*prcnt_hngr)++;
    char character=board[prcnt_pos[HEAD][YPOS]][prcnt_pos[HEAD][XPOS]];

    if(character==FOOD){
        (*prcnt_hngr) = RST_INT;
    }
    else if(character==PERCENT_BODY || character==SHTRODEL_BODY ||
    character==SHTRODEL_HEAD || prcnt_pos[HEAD][XPOS]<0){
        print_finish_msg(trn ,ILLEGAL_MOVE);
        return false;
    }

    if((*prcnt_hngr) >= hngr_max){
        print_finish_msg(trn ,ILLEGAL_MOVE+1);
        return false;
    }

    return true;
}
bool shtrodel_fail(int trn,char board[N][N],int shtrdl_pos[N*N][BI],
int *shtrdl_hngr,int hngr_max){ //made by me - 12 lines
    (*shtrdl_hngr)++;
    char character=board[shtrdl_pos[HEAD][YPOS]][shtrdl_pos[HEAD][XPOS]];

    if(character==FOOD){
        (*shtrdl_hngr) = RST_INT;
    }
    else if(character==PERCENT_BODY || character==PERCENT_HEAD ||
    character==SHTRODEL_BODY || shtrdl_pos[HEAD][XPOS]<0){
        print_finish_msg(trn ,ILLEGAL_MOVE);
        return false;
    }

    if((*shtrdl_hngr) >= hngr_max){
        print_finish_msg(trn ,ILLEGAL_MOVE+1);
        return false;
    }

    return true;
}

void eat(char board[N][N], int size, int trn, int *size_prcnt,
int prcnt_pos[N*N][BI],int *size_shtrdl,int shtrdl_pos[N*N][BI],
int food_pos[BI]){ //made by me - 11 lines
    switch(trn){
    case PERCENT:
        if(prcnt_pos[HEAD][YPOS]==food_pos[YPOS] && prcnt_pos[HEAD][XPOS]==food_pos[XPOS]){
            (*size_prcnt)++;
            full_board(board, size, *size_prcnt, prcnt_pos,
            *size_shtrdl, shtrdl_pos, food_pos);
            where_food(board, size, food_pos);
        }
        break;
    case SHTRODEL:
        if(shtrdl_pos[HEAD][YPOS]==food_pos[YPOS] && shtrdl_pos[HEAD][XPOS]==food_pos[XPOS]){
            (*size_shtrdl)++;
            full_board(board, size, *size_prcnt, prcnt_pos,
            *size_shtrdl, shtrdl_pos, food_pos);
            where_food(board, size, food_pos);
        }
        break;
    }
}

void movement_itself(int direction, int trn, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl, int shtrdl_pos[N*N][BI]){ //made by me - 10 lines
    int tmp_y=RST_INT,tmp_x=RST_INT;

    if(trn==PERCENT){
        tmp_y = prcnt_pos[HEAD][YPOS];
        tmp_x = prcnt_pos[HEAD][XPOS];
    }
    else{
        tmp_y = shtrdl_pos[HEAD][YPOS];
        tmp_x = shtrdl_pos[HEAD][XPOS];
    }

    switch (direction){
    case DOWN:
        down(tmp_y,tmp_x,trn,size_prcnt,prcnt_pos,size_shtrdl,shtrdl_pos);
        break;
    case UP:
        up(tmp_y,tmp_x,trn,size_prcnt,prcnt_pos,size_shtrdl,shtrdl_pos);
        break;
    case LEFT:
        left(tmp_y,tmp_x,trn,size_prcnt,prcnt_pos,size_shtrdl,shtrdl_pos);
        break;
    case RIGHT:
        right(tmp_y,tmp_x,trn,size_prcnt,prcnt_pos,size_shtrdl,shtrdl_pos);
        break;
    }
}
void down(int tmp_y, int tmp_x, int trn, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl, int shtrdl_pos[N*N][BI]){ //made by me - 5 lines
    if(trn==PERCENT){
        prcnt_pos[HEAD][YPOS]++;
        move_common_act_percent(tmp_y, tmp_x, size_prcnt, prcnt_pos);
    }
    else{
        shtrdl_pos[HEAD][YPOS]++;
        move_common_act_shtrodel(tmp_y, tmp_x, size_shtrdl, shtrdl_pos);
    }
}
void left(int tmp_y, int tmp_x, int trn, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl, int shtrdl_pos[N*N][BI]){ //made by me - 5 lines
    if(trn==PERCENT){
        prcnt_pos[HEAD][XPOS]--;
        move_common_act_percent(tmp_y, tmp_x, size_prcnt, prcnt_pos);
    }
    else{
        shtrdl_pos[HEAD][XPOS]--;
        move_common_act_shtrodel(tmp_y, tmp_x, size_shtrdl, shtrdl_pos);
    }
}
void right(int tmp_y, int tmp_x, int trn, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl, int shtrdl_pos[N*N][BI]){ //made by me - 5 lines
    if(trn==PERCENT){
        prcnt_pos[HEAD][XPOS]++;
        move_common_act_percent(tmp_y, tmp_x, size_prcnt, prcnt_pos);
    }
    else{
        shtrdl_pos[HEAD][XPOS]++;
        move_common_act_shtrodel(tmp_y, tmp_x, size_shtrdl, shtrdl_pos);
    }
}
void up(int tmp_y, int tmp_x, int trn, int size_prcnt,
int prcnt_pos[N*N][BI], int size_shtrdl, int shtrdl_pos[N*N][BI]){ //made by me - 5 lines
    if(trn==PERCENT){
        prcnt_pos[HEAD][YPOS]--;
        move_common_act_percent(tmp_y, tmp_x, size_prcnt, prcnt_pos);
    }
    else{
        shtrdl_pos[HEAD][YPOS]--;
        move_common_act_shtrodel(tmp_y, tmp_x, size_shtrdl, shtrdl_pos);
    }
}
void move_common_act_percent(int tmp_y, int tmp_x, int size_prcnt,
int prcnt_pos[N*N][BI]){ //made by me - 5 lines
    for(int i=size_prcnt+1; i>1; i--){
        prcnt_pos[i][YPOS]=prcnt_pos[i-1][YPOS];
        prcnt_pos[i][XPOS]=prcnt_pos[i-1][XPOS];
    }
    prcnt_pos[1][YPOS]=tmp_y;
    prcnt_pos[1][XPOS]=tmp_x;
}
void move_common_act_shtrodel(int tmp_y, int tmp_x, int size_shtrdl,
int shtrdl_pos[N*N][BI]){ //made by me - 5 lines
    for(int i=size_shtrdl+1; i>1; i--){
        shtrdl_pos[i][YPOS]=shtrdl_pos[i-1][YPOS];
        shtrdl_pos[i][XPOS]=shtrdl_pos[i-1][XPOS];
    }
    shtrdl_pos[1][YPOS]=tmp_y;
    shtrdl_pos[1][XPOS]=tmp_x;
}

int switch_trn(int trn){ //made by me - 3 lines
    if(trn==PERCENT){
        return SHTRODEL;
    }
    else{
        return PERCENT;
    }
}

void valid_input(int entries, int expected){ //made by me - 3 lines
    if(entries!=expected){
        print_error_input();
        exit(1);
    }
}

/* ******************************************************************* */
void print_introduction_msg(){
    printf("Welcome to multi-snake  game, The game have 2 player Percent and Shtrodel.\n"
    "The game starts with PERCENT player.\n");
    printf("You have to choose 4 moves :Up,Down,Right and Left "
    "The Percent player is the snake that starts in (0,0)\n\n");
}

void print_board_size_msg(){
    printf("Insert board size between 4 and 25:\n");
}

void print_steps_without_food(){
    printf("Insert the maximum number of steps the snake can do without food:\n");
}

void print_food_location_msg(){
    printf("in order to continue the game please Insert a row then column numbers to place the next food: \n");
}

void help_print_board(int size){
    int i=0;
    printf("%c",BOARD_ELEMENT);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
    }
    printf("%c\n",BOARD_ELEMENT);
}

void print_board(char board[N][N], int size){
    int i=0,j=0;
    help_print_board(size);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
        for(j=0;j<size;j++)
        {
            printf("%c",board[i][j]);
        }
        printf("%c\n",BOARD_ELEMENT);
    }
    help_print_board(size);
    printf("\n\n");
}

void print_player_message(int player){
    printf("******* Turn of %c ***********\n",player==PERCENT?PERCENT_HEAD:SHTRODEL_HEAD);
}

void print_insert_direction(){
    printf("Enter the direction to move your snake: (2-down,4-left,6-right,8-up):\n");
}

void print_finish_msg(int player ,int finish_reason){
    printf("\nThe game finish and the winner is:\n");
    printf("*** %s player ****.\n",player==PERCENT?"SHTRODEL":"PERCENT");
    printf("The reason is %s of the ",finish_reason==ILLEGAL_MOVE? "Illegal move" : "Snake die");
    printf("%s player.\n\n",player==PERCENT?"PERCENT":"SHTRODEL");
}

void print_invalid_input(){
    printf("Please re-Inset valid input:\n");
}

void print_full_board(){
    printf("Full Board. The game over with no Winner.\n");
}
void print_error_input(){
    printf("Error with the input.\n");
}
