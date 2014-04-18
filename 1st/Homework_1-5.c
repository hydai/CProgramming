//
//  main.c
//  Homework 1-5
//
//  Created by 戴宏穎 on 12/9/24.
//  Copyright (c) 2012年 戴 宏穎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI  3.14159265

int main(int argc, const char * argv[])
{
    double x,y;
    scanf("%lf%lf", &x, &y);
    
    printf("sin(degree x) = %lf\n", sin(x * PI /180));
    printf("cos(degree x) = %lf\n", cos(x * PI /180));
    printf("tan(degree x) = %lf\n", tan(x * PI /180));
    printf("atan(degree x) = %lf\n", atan(x * PI /180));
    printf("sqrt(y) = %lf\n", sqrt(y));
    printf("x^y = %lf\n", pow(x,y));
    printf("log(y) = %lf\n", log(y));
    printf("floor(y) = %lf\n", floor(y));
    printf("ceil(y) = %lf\n", ceil(y));
    
//  system("pause");
    return 0;
}

