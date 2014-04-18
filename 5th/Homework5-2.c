#include <stdio.h>
#include <math.h>

#define len 3

struct list
{
	int id;
	double x;
	double y;
};

void find_and_print_max( struct list in[] )
{
	int i;
	int min_entry = 0;
	struct list tmp;

	tmp = in[0];

	/*去除最小x值*/
	for( i = 0 ; i < len ; i++ )
	{
		if( tmp.x > in[i].x )
		{	
			tmp = in[i];
			min_entry = i;
		}
	}

	/*找最大值*/
	for( i = 0 ; i < len ; i++ )
	{
		if( i == min_entry )
			continue;

		tmp = in[i];

		if( tmp.y < in[i].y )
			tmp = in[i];
	}
	
	printf("max: point %d (%lg,%lg)\n", tmp.id, tmp.x, tmp.y);
}

void is_right_triangle( struct list in[] )
{
	double a, b, c;
	short flag = 0, i;
	a = pow(in[0].x-in[1].x, 2.0) + pow(in[0].y-in[1].y, 2.0);
	b = pow(in[1].x-in[2].x, 2.0) + pow(in[1].y-in[2].y, 2.0);
	c = pow(in[0].x-in[2].x, 2.0) + pow(in[0].y-in[2].y, 2.0);

	if( ( a+b == c ) || ( a+c == b ) || ( b+c == a ) )
		flag = 1;
    if( (a == 0) || (b == 0) || (c == 0))
        flag = 0;
	if(flag == 1)
		printf("This is a right triangle.\n");
	else
		printf("This is not a right triangle.\n");
}


int main()
{
	struct list ID[len];
	int i;
	printf("id\tx\ty\n");
	
	for( i = 0 ; i < len ; i++ )
		scanf("%d%lf%lf", &ID[i].id, &ID[i].x, &ID[i].y);
	
	
	find_and_print_max( ID );
	is_right_triangle( ID );

	return 0;
}
