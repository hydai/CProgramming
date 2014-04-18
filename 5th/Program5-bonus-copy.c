#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TMES 100000

struct student
{
	int id;
	int score;
    int total;
};

typedef struct student std_t;

void quicksort( std_t in[], int left, int right )
{
	std_t tmp;
	int i, j;
	//terminal situation
	if ( left >= right )
		return;

	i = left + 1;
	j = right;

	while ( 1 )
	{
		while ( i <= right )		//不超過界限
		{
			if ( in[i].total < in[left].total )
				break;
			
			i++;
		}
	
		while ( j > left )		//不低於界限
		{
			if ( in[j].total > in[left].total )
				break;

			j--;
		}

		if ( i > j )
            break;
        
		tmp = in[i];
		in[i] = in[j];
		in[j] = tmp;
	}

	tmp = in[left];
	in[left] = in[j];
	in[j] = tmp;

	//左右分區
	quicksort( in, left, j - 1 );
	quicksort( in, j + 1, right );
}

int main(void)
{
    double runtime;
    int k;
    time_t start,finish;
	int want_order;
	FILE *fp;
	std_t *std = (std_t*)malloc(5000*sizeof(std_t));

	fp = fopen ("bonus_input.txt", "r+");

	if ( fp == NULL )
	{
		printf("Can not find the input file!\n");
		exit(1);
	}
	else if ( feof (fp) )
	{
		printf("There is nothing!\n");
		exit(1);
	}

    printf("pass1\n");
	int i = 0;
	int tmp_in_id, tmp_in_score;

	scanf("%d", &want_order);

	while ( fscanf(fp, "%d%d", &tmp_in_id, &tmp_in_score) == 2 )
    {
        std[i].id = tmp_in_id;
        std[i].score = tmp_in_score;
		i++;
    }
    
    for ( k = 0 ; k < i ; k++ )
    {
        std[k].total = std[k].score * TMES + (i - std[k].id);
    }
    
	start=clock();
    //**************
    //sort function
    
	quicksort( std, 0, i-1 );	
	
    //printf("pass3\n");
	//**************
    finish=clock();
    runtime=((double)(finish - start) / CLOCKS_PER_SEC); //execution time
	
	printf("runtime = %lf\n", runtime);

    rewind(fp);
    fprintf(fp, "output\n");
    
	int j;
	for ( j = 0 ; j < i ; j++ )
	{
		fprintf(fp, "%d %d %d\n", std[j].id, std[j].score, std[j].total);
	}

	fprintf(fp, "The %dth id = %d\n", want_order, std[want_order-1].id);
	fprintf(fp, "      score = %d\n", std[want_order-1].score);

	fclose(fp);
	
	return 0;
}
