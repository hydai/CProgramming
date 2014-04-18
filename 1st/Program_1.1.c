#include <stdio.h>
#include <math.h>
#define PI 3.14159265

int is_right_angle(double r);
void sort(int *a,int *b,int *c);

int main(void)
{
    //宣告變數
    int a, b, c;
    char name[10];
    double radian;

    //input
    scanf("%s%d%d%d", name, &a, &b, &c);

	//exchange
	sort(&a,&b,&c);
    //計算
    radian = acos( (pow(a,2) + pow(b,2) - pow(c,2)) / (2*a*b) );

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

int is_right_angle(double r)
{
    return fabs(r - PI/2) < 1e-5;
}

void sort(int *a, int *b, int *c)
{
	int temp[3], i, j, exch;
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
