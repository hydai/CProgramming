#include <stdio.h>
#include <math.h>

struct mid_point_t
{
	double x;
	double y;
};

struct point_t
{
	double x;
	double y;
	double distance;
	struct mid_point_t mid_pt; 
};

struct point_t find_dis_mid( struct point_t A, struct point_t B )
{
	struct point_t tmp;
	
	tmp.distance = sqrt( pow(A.x-B.x, 2.0) + pow(A.y-B.y, 2.0) );
	tmp.mid_pt.x = (A.x + B.x)/2.0;
	tmp.mid_pt.y = (A.y + B.y)/2.0;
	return tmp;
}

int main()
{
	int i;
	struct point_t pt[2], result;

	for( i = 0 ; i < 2 ; i++ )
	{
		printf("Please input the point: (x,y)\n");
		scanf("%lf%lf", &pt[i].x, &pt[i].y);
		result = find_dis_mid( pt[0], pt[1]);
	}

	printf("Distance:%lg\n", result.distance);
	printf("Mid point:(%lg,%lg)\n", result.mid_pt.x, result.mid_pt.y);

	return 0;
}
