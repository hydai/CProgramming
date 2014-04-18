#include <stdio.h>
#include <stdlib.h>

struct list
{
    int id;
    double x;
    double y;
};

int main()
{
    int n;
    int i;
    double area = 0;
    printf("n:?\n");
    scanf("%d", &n);
    
    struct list *ptr;
	ptr = ( struct list* )  malloc( (n+1) * sizeof( struct list ));
    
    printf("點座標：\nid\tx\ty\n");
    for ( i = 0 ; i < n ; i++ )
        scanf("%d%lf%lf", &ptr[i].id, &ptr[i].x, &ptr[i].y);
    
    ptr[n] = ptr[0];
    
    for ( i = 0 ; i < n ; i++ )
    {
        area += ptr[i].x * ptr[i+1].y;
        area -= ptr[i].y * ptr[i+1].x;
    }
    
    area *= 0.5;
    
    printf("面積： %lg\n", (area<0)?-area:area);
    free(ptr);
    return 0;
}
