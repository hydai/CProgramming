#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SCALE 16
#define BOOM_NUMBER 40
#define BOOM 11
#define BORDER 12

int map_value[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*存下炸彈的位置*/
int map_status[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*紀錄該位置的含義*/
int map_print[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};/*記錄要印出來的位置*/

int flag = 0;
/*
	flag -> 遊戲狀態
	0 -> 預設
	1 -> 勝利
	2 -> 失敗
*/
int counter = 0;
/*防止第一次踩到地雷*/

void welcome();/*顯示歡迎畫面*/
void initialize();/*初始化地圖*/
void proceed();/*讓使用者輸入指令*/
void dig();/*踩下去*/
void find_space( int, int );/*空白擴散*/
void flg();/*立旗子*/
void print_graph();/*輸出圖形*/
void win();/*輸出勝利訊息*/
void loss();/*輸出失敗訊息*/
void byebye();/*顯示結束畫面*/

int main()
{
	srand( time(NULL) );
	start:
		system("clear");

		welcome();
        initialize();
		if ( flag == 3 )
            goto exit;
        
		print_graph();
		
		do {
			proceed();
		} while ( flag == 0 );

		if ( flag == 1 )
			goto win;
		else if ( flag == 2 )
			goto loss;
		else	/*例外錯誤*/
			goto exit_bug;

	
	win:
		win();
		print_graph();	
	
	loss:
		loss();
		print_graph();	

	exit:
		byebye();
	
	return 0;

	exit_bug:
		exit(1);
}


void welcome()
{
	char input;
	printf("========================================================\n");
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
	printf("========================================================\n");
	
	usleep(500000);
	/*
	printf("請輸入任意字以開始遊戲，或者輸入 q 離開遊戲");
	
	scanf("%c", &input);
	
	if ( input == 'q' )
		flag = 3;
	*/
}

void initialize()
{
	int i;
	int tmp_row, tmp_col;
	
	for ( i = 0 ; i < BOOM_NUMBER ; )
	{
		tmp_row = rand() % MAP_SCALE + 1;
		tmp_col = rand() % MAP_SCALE + 1;
		
		if ( map_value[tmp_row][tmp_col] == 1 )
			continue;

		map_value[tmp_row][tmp_col] = 1;
		i++;
	}
}

void proceed()
{
	char input;
	scanf("%c", &input);
	
	re_get:
	switch ( input )
	{
		case 'd':
			dig();

		case 'f':
			flg();

		case 'q':
			flag = 2;
			return;

		default:
			printf("查無指令！請重新輸入！\n");
			goto re_get;
	}

	if ( flag == 0 )
		print_graph();
}

void dig()
{
	int x, y;
	int i, j;
	printf("請輸入 (x,y)\n");
	scanf("%d%d", &x, &y);

	if ( ((x < 1)&&(x > MAP_SCALE)) || ((y < 1)&&(y > MAP_SCALE)) )
	{
		printf("輸入座標錯誤！\n");
		return;
	}
	
	re_set:/*以防第一次踩到地雷*/
	for ( i = 1 ; i <= MAP_SCALE ; i++ )
		for ( j = 1 ; j <= MAP_SCALE ; j++ )
			map_status[i][j] += map_value[i-1][j-1] + map_value[i-1][j] + map_value[i-1][j+1] + map_value[i][j-1] + map_value[i][j+1] + map_value[i+1][j-1] + map_value[i+1][j] + map_value[i+1][j+1];
	
	for ( i = 1 ; i <= MAP_SCALE ; i++ )
		for ( j = 1 ; j <= MAP_SCALE ; j++ )
			if ( map_value[i][j] == 1 )
				map_status[i][j] = BOOM;
	
	if ( (counter == 0) && (map_status[x][y] == BOOM) )
	{
		initialize();
		goto re_set;
	}
	else
		counter++;

	switch ( map_status[x][y] )
	{
		case BOOM:
			flag = 2;
			return;
		case 0:
			find_space(x, y);
			break;
		default:
			map_print[i][j] = 1;
			break;
	}

}

void find_space( int x, int y )
{
	static int check[ MAP_SCALE + 2 ][ MAP_SCALE + 2 ] = {0};
	
	if ( check[x][y] == 1 )
		return;

	check[x][y] = 1;
	
	if ( map_status[x][y] != 0 )
		return;

	map_print[x][y] = 1;
	map_print[x][y-1] = 1;
	map_print[x][y+1] = 1;
	map_print[x-1][y] = 1;
	map_print[x+1][y] = 1;

	find_space( x-1, y);
	find_space( x+1, y);
	find_space( x, y-1);
	find_space( x, y+1);
	
}

void flg()
{
	int x, y;
	int i, j;
	static int boom_left = BOOM_NUMBER;
	printf("請輸入 (x,y)\n");
	scanf("%d%d", &x, &y);

	if ( ((x < 1)&&(x > MAP_SCALE)) || ((y < 1)&&(y > MAP_SCALE)) )
	{
		printf("輸入座標錯誤！\n");
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
			printf("該位置無法樹旗！\n");
			return;
		}

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
	int i, j, k;

	system("clear");

	putchar(' ');

	for ( i = 1 ; i <= MAP_SCALE ; i++ )
		printf("%2d", i%10);
	putchar(10);

	for ( i = 1 ; i <= MAP_SCALE ; i++ )
	{
		printf("%2d", i%10);
		
		for ( j = 1 ; j <= MAP_SCALE ; j++ )
		{
			switch ( map_print[i][j] )
			{
				case 0:
					printf(" -");
					break;
				
				case 1:
					if ( map_status[i][j] != 0 || map_status[i][j] != BOOM )
						printf("%2d", map_status[i][j]);
					if ( map_status[i][j] == 0 )
						printf("  ");
					if ( map_status[i][j] == BOOM )
						printf(" *");
					break;

				case 2:
					printf(" $");
					break;

				default:	
					break;
			}
		}
		putchar(10);
	}

	putchar(10);
	
	printf("1. d x y = 在(x,y)座標踩下去\n");
	printf("2. f x y = 在(x,y)座標標旗子\n");
	printf("3. q     = 放棄遊戲(印出地雷)\n");
	printf("請輸入指令：");

}

void win()
{
	int i, j;

	system("clear");
    
    printf("Congratulation, You Win!!\n");
    
	usleep(100000);

	for ( i = 1 ; i <= MAP_SCALE ; i++ )
		for ( j = 1 ; j <= MAP_SCALE ; j++ )
			if ( map_print[i][j] != 2 )
				map_print[i][j] = 1;
}

void loss()
{
	int i, j;
    
	system("clear");
    
    printf("Sorry, You Loss!!\n");
    
	usleep(100000);

	for ( i = 1 ; i <= MAP_SCALE ; i++ )
		for ( j = 1 ; j <= MAP_SCALE ; j++ )
			if ( map_status[i][j] == BOOM )
				map_print[i][j] = 1;
}

void byebye()
{
	printf("\n\n");
	printf("========================================================\n");
	printf("|                 踩地雷 made by hydai                 |\n");
	printf("|                                                      |\n");
	printf("|             Think you for playing my game!           |\n");
	printf("|                  See you next time!                  |\n");
	printf("|                                                      |\n");
	printf("========================================================\n");
}
