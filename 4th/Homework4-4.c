#include <stdio.h>

#define LEN 20

void start( int stack[] )
{
	int i;

	printf("Please input the first five number:\n");
	for ( i = 0 ; i < 5 ; i++ )
		scanf("%d", &stack[i]);
	
	printf("-------------------------\n");
	printf("|      How to use ?     |\n");
	printf("| 1.add:  use \" a int \" |\n");
	printf("| 2.pop:  use \" p \"     |\n");
	printf("| 3.exit: use \" EOF \"   |\n");
	printf("|                       |\n");
	printf("------------------------|\n");
}

void add( int stack[], int *length, int add_num )
{
	if( *length > 20 )
	{
		printf("裡頭元素已經滿了！\n");
		return;
	}
	stack[*length] = add_num;
	(*length)++;
}

void pop( int stack[], int *length )
{
	if( *length <= 0 )
	{
		printf("裡頭已經沒有元素了！\n");
		return;
	}
	printf("%d\n", stack[ (*length) - 1 ]);
	(*length)--;
}

void print_all( int stack[], int *length )
{
	int i = *length;
	while ( i != 0 )
	{
		printf("%d ", stack[ (*length) - i ]);
		i--;
	}
	printf("\n");
}

int main()
{
	int stack[LEN] = {0};
	char excu;
	int input, length = 5;

	start( stack );
	while( ~scanf("%c", &excu) )
	{
		switch(excu)
		{
			case 'a':
				scanf("%d", &input);
				add(stack, &length, input);
				break;
			case 'p':
				pop(stack, &length);
				break;
			default:
				break;
		}
	}

	print_all(stack, &length);
	return 0;
}
