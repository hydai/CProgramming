#include <stdio.h>

#define LEN 10

void get_array( int A[LEN][LEN], int B[LEN][LEN], int *counter )
{
	scanf("%d", &*counter);
	int i, j;
	for( i = 0 ; i < *counter ; i++ )
		for( j = 0 ; j < *counter ; j++ )
			scanf("%d", &A[i][j]);

	for( i = 0 ; i < *counter ; i++ )
		for( j = 0 ; j < *counter ; j++ )
			scanf("%d", &B[i][j]);
}

void print_add( int A[LEN][LEN], int B[LEN][LEN], int *counter )
{
	int i, j;

	for( i = 0 ; i < *counter ; i++ )
		for( j = 0 ; j < *counter ; j++ )
		{
			printf("%d ", ( A[i][j] + B[i][j] ));
			if( j == *counter - 1 )
				printf("\n");
		}
}

int main()
{
	int A[LEN][LEN] = {0}, B[LEN][LEN] = {0}; 
	int N;

	get_array( A, B, &N );
	print_add( A, B, &N );
	
	return 0;
}
