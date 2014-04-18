#include <stdio.h>

#define name_len 100
#define ID_len 5

struct list
{
    int id;
    char name[name_len];
    int score;
};

struct list find_max( struct list input[ID_len] )
{
    int i;
    struct list max;
    max = input[0];
    
    for ( i = 0 ; i < ID_len ; i++ )
        if ( input[i].score > max.score )
            max = input[i];

    return max;
}

void print_result( struct list input )
{
    printf("id:%d\n", input.id);
    printf("name:%s\n", input.name);
    printf("score:%d\n", input.score);
}

int main()
{
    struct list data[ID_len], student;
    int i;
    
    printf("id\tname\tscore\n");
    
    for ( i = 0 ; i < ID_len ; i++ )
        scanf("%d%s%d", &data[i].id, data[i].name, &data[i].score);
    
    student = find_max( data );
    
    print_result( student );
    
    return 0;
}