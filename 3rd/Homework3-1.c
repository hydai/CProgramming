#include <stdio.h>

struct ID_table
{
	int ID_number;
	int per_num[9];
	int year, department;
	int ID_length;
	int flag;
};

void get_number( struct ID_table *ID )
{
	scanf("%d", &ID -> ID_number);
	
	int temp = ID -> ID_number;
	
	int i = 0;
	while( temp != 0 )
	{
		ID -> per_num[i] = temp % 10;
		temp /= 10;
		i++;
	}
	
	ID -> ID_length = i;
}

void is_right( struct ID_table *ID )
{
    ID -> year = ID -> per_num[8]*100 + ID ->  per_num[7]*10 + ID -> per_num[6];
    
	if( (ID -> year == 101) || (ID -> year == 100) || (ID -> year == 99) || (ID -> year == 98) )
		ID -> flag = 1;
	else
		ID -> flag = 0;
    
    ID -> department = ID -> per_num[5]*10 + ID -> per_num[4];
    
    if( ((ID -> department == 6) || (ID -> department == 4)) && (ID -> flag == 1) )
		ID -> flag = 1;
	else
		ID -> flag = 0;
}

void print_result( struct ID_table *ID)
{
	if( ID -> flag == 1 )
		printf("此學號為正確之格式!\n");
	else
		printf("此學號為錯誤之格式!\n");
}

int main()
{
	struct ID_table ID;
	
	int i;
	for(i = 0 ; i < 9 ; i++)
		ID.per_num[i] = 0;
    
	get_number( &ID );
	is_right( &ID );
	print_result( &ID );
    
	return 0;
}