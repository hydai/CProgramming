#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 23
#define col 80

void print_playway()
{
	printf("-------------------------------------------------\n");
	printf("|                                               |\n");
	printf("|     How to play the Conway's Game of Life     |\n");
	printf("|                                               |\n");
	printf("|               Glider: input 1                 |\n");
	printf("|         Lightweight spaceship: input 2        |\n");
	printf("|               Pulsar: input 3                 |\n");
	printf("|               Random: input 4~100             |\n");
	printf("|                                               |\n");
	printf("-------------------------------------------------\n");
}

void random_map( int map[ row + 2 ][ col + 2 ], int input )
{
	int how_many, rand_row, rand_col;
	int flag_map[ row + 2 ][ col + 2 ] = {0};

	how_many = row * col * input / 100;
	srand( time(NULL) );

	while( how_many != 0 )
	{
		rand_row = rand() % row + 1;
		rand_col = rand() % col + 1;

		if( flag_map[ rand_row ][ rand_col ] == 0 )
		{
			flag_map[ rand_row ][ rand_col ] = 1;
			map[ rand_row ][ rand_col ] = 1;
			how_many--;
		}
	}
}

void initialize( int map[ row + 2 ][ col + 2 ], int input )
{
	int i, j, k;
	switch ( input )
	{
		case 1:	/*Glider*/
			map[11][40] = 1;
			map[11][41] = 1;
			map[11][42] = 1;
			map[12][40] = 1;
			map[13][41] = 1;
			break;
		case 2:	/*Lightweight spaceship*/
			map[11][40] = 1;
			map[11][43] = 1;
			map[12][39] = 1;
			map[13][39] = 1;
			map[13][43] = 1;
			map[14][39] = 1;
			map[14][40] = 1;
			map[14][41] = 1;
			map[14][42] = 1;
			break;
		case 3:/*Pulsar*/
			/*左上方*/
			map[6][36] = 1;
			map[6][37] = 1;
			map[7][37] = 1;
			map[7][38] = 1;
			map[8][34] = 1;
			map[8][37] = 1;
			map[8][39] = 1;
			map[9][34] = 1;
			map[9][35] = 1;
			map[9][36] = 1;
			map[9][38] = 1;
			map[9][39] = 1;
			map[10][35] = 1;
			map[10][37] = 1;
			map[10][39] = 1;
			map[11][36] = 1;
			map[11][37] = 1;
			map[11][38] = 1;
			
			/*右上方*/
			for( i = 6 ; i < 12 ; i++ )
				for( j = 41, k = 2 ; j < 47 ; j++, k+=2 )
					map[i][j] = map[i][j-k];
		
			/*下方*/
			for( i = 13, k = 2 ; i < 19 ; i++, k+=2 )
				for( j = 34 ; j < 47 ; j++ )
					map[i][j] = map[i - k][j];
			break;

		default:
			random_map( map, input );
			break;
	}
}

void proceed( int current[ row + 2 ][ col + 2 ] )
{
	int tmp[ row + 2 ][ col + 2 ] = {0};

	int i, j;

	/*印出圖形*/
	for( i = 1 ; i <= row ; i++ )
		for( j = 1 ; j <= col ; j++ )
			if ( j == col )
				printf("%c\n", ( current[i][j] )?'*':' ');
			else
				printf("%c", ( current[i][j] )?'*':' ');
	/*清空暫存*/
	for( i = 1 ; i <= row ; i++ )
		for( j = 1 ; j <= col ; j++ )
			tmp[i][j] = 0;

	/*掃瞄周圍個數*/
	for( i = 1 ; i <= row ; i++ )
		for( j = 1 ; j <= col ; j++ )
			tmp[i][j] += ( current[i-1][j-1] + current[i-1][j] + current[i-1][j+1] + current[i][j-1] + current[i][j+1] + current[i+1][j-1] + current[i+1][j] + current[i+1][j+1] );
	
	/*判斷並存入下次的值*/
	for( i = 1 ; i <= row ; i++ )
		for( j = 1 ; j <= col ; j++ )
		{
			switch ( tmp[i][j] )
			{
				case 3:
					current[i][j] = 1;
					break;

				case 2:
					break;

				default:
					current[i][j] = 0;
					break;
			}
		}
	
	usleep(100000);
}

int main( int argc, char *argv[] )
{
	int map[ row + 2 ][ col + 2 ] = {};/*含邊界*/
	int input;
	
	if ( argc != 2 )
	{
		printf("沒有傳入引數，或是傳入錯誤格式！\n");
		goto exit;
	}

	input = atoi( argv[1] );

	printf("%d\n", input );

	sleep(3);
	system("clear");

	if ( (input > 0) && (input <= 100) )
	{
		initialize( map, input );
		
		do
		{
			proceed( map );
			system("clear");
		}while( 1 );
	}
	else
	{
		printf("Input error! Please input by the right format!\n");
		goto exit;
	}

	exit:
	print_playway();
	return 0;
}
