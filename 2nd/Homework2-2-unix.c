#include <stdio.h>
#include <unistd.h>

#define COUNT_INIT 10

int main()
{
	int frame_counter, counter=COUNT_INIT;
    
	int i,j,space;
    
	for (frame_counter = 0; frame_counter <= 10; frame_counter++) {
        
		/*
		 * Clean the screen
		 */
		system("clear"); //in UNIX environment
        
		/*
		 * Counting down
		 */
		printf("Counting down: %d\n", counter);
		counter--;
		
		//print stars
		for(i = 0 ; i < 20 ; i++ )
		{
            //print space
            for(space = 0 ; space < (10 - counter - 1) ; space++)
                printf(" ");
            
			//print star
			for(j = 0 ; j <= i ; j++)
                printf("*");
			printf("\n");
		}
		/*
		 * Do nothing for one second
		 *
		 * usleep(x) means that it will do nothing for x microsecond. (i.e. waiting for x*10^(-6) second)
		 *
		 * You can also use sleep(y). It means that it will do nothing for y second.
		 */
		usleep(1000000);
	}
	
	/*
	 * Final content on the screen
	 */
	system("clear"); //in UNIX environment
	printf("The End of the animation.\n");
    
	return 0;
}

/*
 原本想法，後做簡化
 //print stars
 for(i = 0 ; i < 20 ; i++ )
 {
 
 //print star
 for(j = 0 ; j <= i ; j++)
 {
 if(j == 0)
 for(space = 0 ; space < (10 - counter - 1) ; space++)
 printf(" ");
 
 printf("*");
 
 if(j == i)
 printf("\n");
 }
 }
 */
