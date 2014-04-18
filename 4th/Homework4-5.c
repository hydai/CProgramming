#include <stdio.h>
#include <stdlib.h>

#define LEN 10

short T[LEN][LEN] = {0};

void clear()
{
	int i, j;
	for ( i = 0 ; i < LEN ; i++ )
		for ( j = 0 ; j < LEN ; j++ )
			if ( i == j )
				T[i][j] = 1;
}

void print_result( int N )
{
	int i, j;
	for ( i = 0 ; i < N ; i++ )
		for ( j = 0 ; j < N ; j++ )
		{	
			printf("%d ", T[i][j]);
			if ( j == N - 1 )
				printf("\n");
		}
}

int main(int argc, char *argv[])
{
	
	clear();
	
	int N;

	if ( argc == 1 )
		printf("usage: %s <size>\n", argv[0]);
	else
	{
		N = atoi( argv[1] );
		print_result( N );
	}

	return 0;
}
