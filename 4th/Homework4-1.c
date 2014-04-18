#include <stdio.h>

#define LEN 8

void swap( int *a, int *b )
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;

}

int main()
{
	int T[LEN][LEN];
	int scale;
	
	scanf("%d", &scale);
    
	int i, j;
    //get
	for( i = 0 ; i < scale ; i++ )
		for( j = 0 ; j < scale ; j++ )
			scanf("%d", &T[i][j]);
    //exchange
    for( i = 0 ; i < scale ; i++)
		for( j = i ; j < scale ; j++ )
			swap(&T[i][j], &T[j][i]);
    //print
	printf("\n");
    for( i = 0 ; i < scale ; i++)
	{
		for( j = 0 ; j < scale ; j++ )
			printf("%d ", T[i][j]);
		printf("\n");
	}
	return 0;
}
