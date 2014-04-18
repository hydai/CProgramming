#include <stdio.h>
#include <stdlib.h>

void hanoi(int n, int *count)
{
	if(n == 1) // 1 -> 3
	{
		*count += 6;
	}
	else
	{
		hanoi(n-1, &*count); // clear the upper
		*count += 3;         // 1 -> 2
		hanoi(n-1, &*count); // return the upper
		*count += 3;         // 2 -> 3
		hanoi(n-1, &*count); // take upper to 3
	}
}

void hanoi3(int n, int *count)
{
	int i;
	
	for(i = n; i > 1; i--)
	{
		hanoi(i-1, &*count); // move the upper to 3
		*count += 2;         // move the lower to 2
		hanoi(i-1, &*count); // move the upper to 1
		*count += 1;	     // move the last one to 3
	}
}
int main( int argc, char* argv[])
{
	FILE *fp, *op;
	int count, input;

        if ( argc != 3 ) {
            printf("Input ERROR!!\n");
            exit(1);
        }

	fp = fopen(argv[1], "r");
	op = fopen(argv[2], "w");

	if( fp == NULL )
	{
		printf("Cannot open the file!!\n");
		exit(1);
	}
	
	while ( fscanf(fp, "%d", &input) == 1 )
	{
	        input /= 3;
		count = 3;
		hanoi3( input, &count );
		fprintf( op, "%d\n", count);
	}
	
	fclose(fp);
	fclose(op);
	
	return 0;
}
