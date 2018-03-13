#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SCALE 16
#define BOOM_NUMBER 40
#define BOOM 9
#define BORDER 12

#define NONE "\033[m"
#define L_RED "\033[1;32;31m"
#define L_BLUE "\033[1;32;32m"
#define L_YELLO "\033[1;33m"

int map_value[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*存下炸彈的位置*/
int map_status[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*紀錄該位置的含義*/
int map_print[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*記錄要印出來的位置*/

int counter = 0;/*防止第一次踩到地雷*/
int flag = 0;
/*
   flag -> 遊戲狀態
   0 -> 預設
   1 -> 勝利
   2 -> 失敗
   3 -> Give up
   */

void welcome();/*顯示歡迎畫面*/
void initialize();/*初始化地圖*/
void proceed();/*讓使用者輸入指令*/
void dig();/*踩下去*/
void find_space( int, int );/*空白擴散*/
void flg();/*立旗子*/
void print_graph();/*輸出圖形*/
void win();/*輸出勝利訊息*/
void lose();/*輸出失敗訊息*/
void give_up();/*輸出放棄訊息*/
void byebye();/*顯示結束畫面*/

int main()
{
    srand( time(NULL) );
    //start
    system("clear");

    welcome();
    initialize();

    print_graph();

    do {
        proceed();
    } while ( flag == 0 );

    if ( flag == 1 )
        goto win;
    else if ( flag == 2 )
        goto lose;
    else if ( flag == 3 )
        goto give_up;
    else	/*例外錯誤*/
        goto exit_bug;


win:
    win();
    print_graph();
    goto exit;

lose:
    lose();
    print_graph();
    goto exit;

give_up:
    give_up();
    print_graph();
    goto exit;

exit:
    byebye();

    return 0;

exit_bug:
    exit(1);
}


void welcome()
{
    printf(L_BLUE"========================================================\n");
    printf("|                 踩地雷 made by hydai                 |\n");
    printf("|                                                      |\n");
    printf("|                     How to play:                     |\n");
    printf("|                                                      |\n");
    printf("|              1. d x y = 在(x,y)座標踩下去            |\n");
    printf("|              2. f x y = 在(x,y)座標標旗子            |\n");
    printf("|              3. q     = 放棄遊戲(印出地雷)           |\n");
    printf("|                                                      |\n");
    printf("|             注意！必須把所有旗子插完才算獲勝         |\n");
    printf("|                                                      |\n");
    printf("========================================================\n"NONE);

    usleep(3000000);
}

void initialize()
{
    int i, j;
    int tmp_row, tmp_col;

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
        {
            map_value[i][j] = 0;
        }

    for ( i = 0 ; ; )
    {
        tmp_row = rand() % MAP_SCALE + 1;
        tmp_col = rand() % MAP_SCALE + 1;

        if ( map_value[tmp_row][tmp_col] == 1 )
            continue;

        if ( i >= BOOM_NUMBER )
            break;

        map_value[tmp_row][tmp_col] = 1;
        i++;
    }

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
            map_status[i][j] = map_value[i-1][j-1] + map_value[i-1][j] + map_value[i-1][j+1] + map_value[i][j-1] + map_value[i][j+1] + map_value[i+1][j-1] + map_value[i+1][j] + map_value[i+1][j+1];

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
            if ( map_value[i][j] == 1 )
                map_status[i][j] = BOOM;
}

void proceed()
{
    char input;
re_get:

    scanf("%c", &input);

    switch ( input )
    {
        case 'd':
            dig();
            break;
        case 'f':
            flg();
            break;
        case 'q':
            flag = 3;
            return;

        default:
            print_graph();
            //printf("查無指令！請重新輸入！\n");
            goto re_get;
    }

    if ( flag == 0 )
        print_graph();
}

void dig()
{
    int x, y;

    printf(L_RED"請輸入 (x,y)\n"NONE);
    scanf("%d%d", &x, &y);

    if ( (x < 1) || (x > MAP_SCALE) || (y < 1) || (y > MAP_SCALE) )
    {
        printf(L_RED"輸入座標錯誤！\n"NONE);
        return;
    }

    /*以防第一次踩到地雷*/

    while ( counter == 0 )
    {
        if ( map_value[x][y] == 1 )
        {
            initialize();
            continue;
        }
        else
            counter = 1;
    }


    switch ( map_status[x][y] )
    {
        case BOOM:
            flag = 2;
            return;
        case 0:
            find_space(x, y);
            break;
        default:
            map_print[x][y] = 1;
            break;
    }

}

void find_space( int x, int y )
{
    static int check[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};

    if ( check[x][y] == 1 )
        return;

    if ( x < 1 || x > MAP_SCALE )
        return;
    if ( y < 1 || y > MAP_SCALE )
        return;

    check[x][y] = 1;

    if ( map_status[x][y] != 0 )
        return;

    map_print[x-1][y] = 1;
    map_print[x-1][y-1] = 1;
    map_print[x-1][y+1] = 1;
    map_print[x][y] = 1;
    map_print[x][y-1] = 1;
    map_print[x][y+1] = 1;
    map_print[x+1][y] = 1;
    map_print[x+1][y-1] = 1;
    map_print[x+1][y+1] = 1;

    find_space( x-1, y-1 );
    find_space( x-1, y );
    find_space( x-1, y+1 );
    find_space( x, y-1 );
    find_space( x, y+1 );
    find_space( x+1, y-1 );
    find_space( x+1, y );
    find_space( x+1, y+1 );
}

void flg()
{
    int x, y;
    static int boom_left = BOOM_NUMBER;

    printf(L_RED"請輸入 (x,y)\n"NONE);
    scanf("%d%d", &x, &y);

    if ( ((x < 1)&&(x > MAP_SCALE)) || ((y < 1)&&(y > MAP_SCALE)) )
    {
        printf(L_RED"輸入座標錯誤！\n"NONE);
        return;
    }

    if ( map_print[x][y] != 0 )
        if ( map_print[x][y] == 2 )
        {
            map_print[x][y] = 0;
            if ( map_status[x][y] == BOOM )
                boom_left++;
        }
        else
        {
            printf(L_RED"該位置無法立旗！\n"NONE);
            return;
        }
    else
        map_print[x][y] = 2;

    switch ( map_status[x][y] )
    {
        case BOOM:
            boom_left--;
            break;
        default:
            break;
    }

    if ( boom_left == 0 )
        flag = 1;
}

void print_graph()
{
    int i, j;

    system("clear");

    printf("  ");

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        printf(L_YELLO"%d"NONE, i%10);

    printf("\n");

    printf(L_YELLO" ##################\n"NONE);

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
    {
        printf(L_YELLO"%d#"NONE, i%10);

        for ( j = 1 ; j <= MAP_SCALE ; j++ )
        {
            if ( map_print[i][j] == 0 )
                printf("-");
            else if ( map_print[i][j] == 1 )
            {
                if ( map_status[i][j] != 0 && map_status[i][j] != BOOM )
                    printf("%d", map_status[i][j]);
                if ( map_status[i][j] == 0 )
                    printf(" ");
                if ( map_status[i][j] == BOOM )
                    printf(L_RED"*"NONE);
            }
            else
                printf(L_BLUE"$"NONE);
        }
        printf(L_YELLO"#");
        putchar(10);
    }
    printf(" ##################\n"NONE);

    putchar(10);
    /*use to debug*/
    printf("value\n");
    for ( i = 1 ; i < MAP_SCALE + 1 ; i++ )
    {
        for ( j = 1 ; j < MAP_SCALE + 1 ; j++ )
            printf("%2d", map_value[i][j]);
        putchar(10);
    }
    /*
       putchar(10);
       printf("status\n");
       for ( i = 1 ; i < MAP_SCALE + 1 ; i++ )
       {
       for ( j = 1 ; j < MAP_SCALE + 1 ; j++ )
       printf("%2d", map_status[i][j]);
       putchar(10);
       }

       putchar(10);
       printf("print\n");
       for ( i = 1 ; i < MAP_SCALE + 1 ; i++ )
       {
       for ( j = 1 ; j < MAP_SCALE + 1 ; j++ )
       printf("%2d", map_print[i][j]);
       putchar(10);
       }
       */
    printf("1. 輸入d x y = 在(x,y)座標踩下去\n");
    printf("2. 輸入f x y = 在(x,y)座標標旗子\n");
    printf("3. q     = 放棄遊戲(印出地雷)\n");
    printf("請輸入指令：\n");

}

void win()
{
    int i, j;


    printf(L_RED"Congratulation, You Win!!\n"NONE);

    usleep(5000000);

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
            if ( map_print[i][j] != 2 )
                map_print[i][j] = 1;
}

void lose()
{
    int i, j;

    printf(L_RED"Sorry, You lose!!\n"NONE);

    usleep(5000000);

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
            if ( map_status[i][j] == BOOM )
                map_print[i][j] = 1;
}

void give_up()
{
    int i, j;

    printf(L_RED"So Sad, You Give Up !!\n"NONE);

    usleep(5000000);

    for ( i = 1 ; i <= MAP_SCALE ; i++ )
        for ( j = 1 ; j <= MAP_SCALE ; j++ )
            if ( map_print[i][j] != 2 )
                map_print[i][j] = 1;
}

void byebye()
{
    printf(L_BLUE"\n");
    printf("========================================================\n");
    printf("|                 踩地雷 made by hydai                 |\n");
    printf("|                                                      |\n");
    printf("|             Thank you for playing my game!           |\n");
    printf("|                  See you next time!                  |\n");
    printf("|                                                      |\n");
    printf("========================================================\n"NONE);
}
