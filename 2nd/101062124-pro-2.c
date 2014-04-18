#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MAX 15

int get_hour()
{
    int hour;
    time_t timer;
	
   	struct tm *time_ptr;
    
    timer = time(NULL);
	time_ptr = localtime(&timer);
	hour = time_ptr->tm_hour;
    
    return hour;
}

int get_sec()
{
    int sec;
    time_t timer;
	
   	struct tm *time_ptr;
    
	timer = time(NULL);
	time_ptr = localtime(&timer);
	sec = time_ptr->tm_sec;
    
    return sec;
}

int gcd(int max, int min)
{
	int temp;
    
	if(min > max)
	{
		temp = min;
		min = max;
		max = temp;
	}
    
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
		return max;
	else
		return min;
}

int main()
{
	int nowcounter,counter = MAX;
	int i, space, star;
    
    //build the fib index
	unsigned long long int fib[50];
	fib[0] = 0;
	fib[1] = 1;
	
	for( i = 2 ; i < 50 ; i++)
		fib[i] = fib[i-1] + fib[i-2];


	int fib_counter;
	//print
	for( nowcounter = 0 ; nowcounter < counter ; nowcounter++ )
	{
        system("clear");
        
		fib_counter =  get_sec() % 4;

		//fib_counter = ( get_sec() % 4 ) * ( rand() % 3 );
        for( i = 0 ; i <= fib[ fib_counter + 2 ] ; i++)
        {
            for( space = 0 ; space < nowcounter ; space++ )
                printf(" ");
		
			for( star = 0 ; star <= gcd( get_hour(), (get_sec() + 1 ) ); star++ )
                printf("*");
            
            printf("\n");
        }
        
        usleep(1000000);
	
	}

	system("clear");
    printf("The End of the animation.\n");

	return 0;
}
