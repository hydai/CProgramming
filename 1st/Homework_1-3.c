//
//  main.c
//  Homework 1-3
//
//  Created by 戴宏穎 on 12/9/23.
//  Copyright (c) 2012年 戴 宏穎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    char name[10];
    int ch,en,math;
    
    //input 
    scanf("%s", name);
    scanf("%d%d%d", &ch, &en, &math);
    //output
    printf("Name\tChinese\tEnglish\tMath\n");
    printf("%s\t%d\t%d\t%d\t", name, ch, en, math);
    

//  system("pause");
    return 0;
}

