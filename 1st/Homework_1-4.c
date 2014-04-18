//
//  main.c
//  Homework 1-4
//
//  Created by 戴宏穎 on 12/9/23.
//  Copyright (c) 2012年 戴 宏穎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char * argv[])
{
    int height, weight;
    float BMI;
    scanf("%d%d", &height, &weight);
    float height_m = (float) height / 100;    
    BMI = (float) weight / pow(height_m, 2.0);
    
    printf("%f", BMI);
//  system("pause");
    return 0;
}
