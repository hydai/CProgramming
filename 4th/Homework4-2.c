#include <stdio.h>

#define LEN 100

int main()
{
	int input, counter, temp;
	int T[LEN];
	int i = 0, j;
    
	scanf("%d", &input);
	counter = input * input;
	
	while( counter != 0 )
	{
		scanf("%d", &T[i]);
		counter--;
		i++;
	}
    
	for( i = 0 ; i < input ; i++ )
		for( j = i ; j < input ; j++ )
		{
			temp = T[ i + input * j ];
			T[ i + input * j ] = T[ j + input * i ];
			T[ j + input * i ] = temp;
		}
	printf("\n");
	for( i = 0 ; i < input ; i++ )
	{
		for( j = 0 ; j < input ; j++ )
			printf("%d ", T[ i*input + j ]);
		printf("\n");
	}
	return 0;
}
