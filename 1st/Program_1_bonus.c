#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int is_right_angle(double r);
int factorial(int n);
double my_acos(double length);
void sort(double *a,double *b,double *c);


int main(void)
{
	//宣告變數
	char name[10];
	double a,b,c;
	double radian;

	//input
	scanf("%s%lf%lf%lf", name, &a, &b, &c);

    sort(&a, &b, &c);
    
	//運算過程
	radian = my_acos( ( pow(a,2.0) + pow(b,2.0) - pow(c,2.0) ) / (2*a*b) ); 
	
	//輸出角度值
	printf("                   a^2+b^2-c^2 \n");
	printf("Radian C = arccos -------------  = %lf \n", radian);
	printf("                       2ab     \n");

	//判斷是否為正三角形
	if(is_right_angle(radian)) {
		printf("This is a right triangle. \n");
    	} else {
        	printf("This is not a right triangle. \n");
    	}

    	//印出寫作者
    	printf("written by %s \n", name);

	return 0;
}


int factorial(int n)
{
	int i,temp = 1;
	for(i=1;i<=n;i++)
		temp *= i;
	return temp;
}

double my_acos(double length)
{
	double radian = ( PI / 2 );
	double temp = 0;
	int i;

	for( i = 0 ; i < 10 ; i++)
	{
		temp += ( (factorial( 2*i ) / ( pow( 2, (2* (double) i) ) * pow( factorial( i ), 2.0 ) ) ) * ( pow( length, ( 2* (double) i + 1 ) ) / ( 2* (double) i + 1 ) ) );
	}
	return ( radian - temp );
}

int is_right_angle(double r)
{
	    return fabs(r - PI/2) < 1e-5;
}

void sort(double *a, double *b, double *c)
{
	double temp[3], exch;
	int i, j;
	temp[0] = *a;
	temp[1] = *b;
	temp[2] = *c;
    
	for(i = 1; i >= 0; i--)
		for(j = 0; j <= i; j++)
			if( temp[j] > temp[j+1]){
				exch = temp[j];
				temp[j] = temp [j+1];
				temp[j+1] = exch;
			}
	*a = temp[0];
	*b = temp[1];
	*c = temp[2];
}
