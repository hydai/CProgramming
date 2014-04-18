#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
 * get_time_asctime
 *
 * This function shows that how to use "localtime" and "asctime" to 
 * show current time without saving the value of current time
 *
 */
void get_time_asctime()
{
	// Initiate the variable which is about time_infomation.
	time_t timer=time(NULL);

	/*
	 * This function will show the current time, date, and year.
	 *
	 * "localtime" will get the current time from the input time_t variable.
	 * "asctime" will transform the data type from time_t to string.
	 *
	 * You can get more info about time.h on this website:
	 * http://www.acm.uiuc.edu/webmonkeys/book/c_guide/2.15.html
	 */
	printf("The current time is %s\n", asctime(localtime(&timer)));
	
}

/*
 * get_time_and_save_value
 *
 * This function shows how to get current time by getting its value and saving it.
 *
 */
void get_time_and_save_value()
{
	// Initiate the variable which is about time_infomation.
	time_t timer;
	// Variables to save info about hour, min, and sec.
	int hour, min, sec;
	// Get the information about current time
	// You can ignore how to use structure variable.
	// If you want to use this way to get time. 
	// For now, you just need to follow the pattern of this sample function.
	struct tm *time_ptr;
	
	/*
	 * Put info about current time into "hour, min, and sec variables"
	 * For now, you don't need to know the detail about this part.
	 * If you want to use this way to get time, you just need to follow 
	 * the pattern of this sample function.
	 */
	timer = time(NULL);
	time_ptr = localtime(&timer);
	hour = time_ptr->tm_hour;
	min = time_ptr->tm_min; 
	sec = time_ptr->tm_sec;
	printf("Current time (HH:MM:SS) is %u:%u:%u\n", hour, min, sec);

}

int main()
{

	//One way to show current time by asctime()
	int i;
	for(i = 0 ; i < 10 ; i++)
	{
		get_time_asctime();
		usleep(1000000);
		system("clear");
	}

	//Another way to show current time by getting time information and saving its value.

	get_time_and_save_value();
	
	system("clear");
	printf("The End of the animation.\n");
	return 0;
}
