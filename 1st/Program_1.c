#include <stdio.h>
#include <math.h>
#define PI 3.14159265

int is_right_angle(double r);

int main(void)
{
    //宣告變數
    int a, b, c;
    char name[10];
    double radian;

    //input
    scanf("%s%d%d%d", name, &a, &b, &c);

    //計算
    radian = acos( ((pow(a,2) + pow(b,2) - pow(c,2)) / (2*a*b)) );

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
