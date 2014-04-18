#include <stdio.h>
#include <stdlib.h>

struct ID_table
{
	int ID_number;
	int year, institution, department, other;
};

void produce_ID( struct ID_table *ID )
{
	ID -> year = rand() % 4 + 98;
	
	
	int institution_temp = rand() % 2;
	
	if( institution_temp == 0 )
		ID -> institution = 4;
	else
		ID -> institution = 6;
	
	ID -> department = rand() % 10;

	ID -> other = rand() % 1000;
}
ㄇ
void print_ID( struct ID_table *ID )
{
	printf("%d%02d%d%03d\n", ID -> year, ID -> institution, ID -> department, ID -> other);
}

int main()
{
	struct ID_table ID;
	
	srand(time(NULL));
    
	produce_ID( &ID );
	print_ID( &ID );

	return 0;
}
