//
//  main.c
//  Homework 1-2
//
//  Created by 戴宏穎 on 12/9/23.
//  Copyright (c) 2012年 戴 宏穎. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>



int main(int argc, const char * argv[])
{
    char first_name[10], last_name[10];
    
    //input
    
    printf("Your first name: ");
    scanf("%s", first_name);
    printf("Your last name: ");
    scanf("%s", last_name);
    
    
    //output
    printf("Hello, %s %s\n", first_name, last_name);
    
    system("pause");
    return 0;
}

