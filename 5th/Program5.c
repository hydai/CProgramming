#include <stdio.h>
#include <stdlib.h>

struct ID_list
{
	int id;
	int score;
};

void insection_sort( struct ID_list in[], int n )
{
	int i, j;
	struct ID_list tmp;

	for ( i = 1 ; i < n ; i++ )
	{
		tmp = in[i];

		j = i - 1;

		while ( j >= 0 && in[j].score < tmp.score )
		{
			in[ j + 1 ] = in[ j ];
			j--;
		}
	
		in[ j + 1 ] = tmp;
	}
}

int main()
{
	int n, m;
	int i,len = 0;

	FILE *fp;
    
    fp = fopen ("prob5-input.txt", "w");
    
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
	//printf("How many data do you want to input? (n:)");
	//scanf("%d", &n);
	printf("Which data do you want to know? (m:)");
	scanf("%d", &m);

	struct ID_list *student_id = (struct ID_list *) malloc( 1000000 * sizeof(struct ID_list) );

    /*
	printf("id\tscore\n");
	for ( i = 0 ; i < n ; i++ )
	{
		printf("%d\t", i+1);
		student_id[i].id = i + 1;
		scanf("%d", &student_id[i].score);
	}
     */
    
    while (!feof(fp)) {
        fscanf(fp, "%d%d", &student_id[len].id, &student_id[len].score);
        len++;
    }

	insection_sort( student_id, len );

    rewind(fp);
    fprintf(fp, "id\tscore\n");
   
	for ( i = 0 ; i < len ; i++ )
	{
		fprintf(fp, "%d\t%d\n", student_id[i].id, student_id[i].score);
	}
    
	fprintf(fp, "第%d筆id: %d\nscore: %d\n", m, student_id[ m - 1 ].id, student_id[ m - 1 ].score);

	free(student_id);
    fclose (fp);
	
    return 0;
}
