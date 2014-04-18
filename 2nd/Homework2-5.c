#include <stdio.h>

int main()
{
	unsigned long long int fib[100] = { 0 };

	int i,input;

	scanf("%d", &input);
	
	fib[0] = 0;
	fib[1] = 1;

	for(i = 2 ; i <= input ; i++)
		fib[i] = fib[i-1] + fib[i-2];

	for(i = 0 ; i<=input ; i++)
	{
		if( input == 0 )
		{
			printf("%llu\n", fib[0]);
			break;
		}
		else if( input == 1 )
		{
			printf("%llu, %llu\n", fib[0], fib[1]);
			break;
		}
		else
		{
			if( i == input)
				printf("%llu\n", fib[i]);
			else
				printf("%llu, ", fib[i]);
		}
	}

	return 0;
}
