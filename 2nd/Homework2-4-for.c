#include <stdio.h>

int main()
{
	int max, min, temp;
	
	scanf("%d%d", &max, &min);
	
	if(min > max)
	{
		temp = min;
		min = max;
		max = temp;
	}

	for( ; (min != 0 ) ; )
	{
		max %= min;
		//swap
		temp = min;
		min = max;
		max = temp;
	}

	printf("%d\n", max);

	return 0;
}

/*
 原本想法，參數優化
 
 for( ; (min != 1 ) ; )
 {
 max %= min;
 //swap
 temp = min;
 min = max;
 max = temp;
 
 if( min == 0)
 break;
 }
 
 if( min == 0)
 printf("%d\n", max);
 else
 printf("%d\n", min);
 
 */