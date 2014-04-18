#include <stdio.h>

struct ID_table
{
	char sex;
	int per_num[9];
	char birth_location;
}

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KBLU "\x18[34m"




int main()
{
	struct ID_table ID;
	input( &ID );
	produce_ID( &ID );
	print_graph( &ID );
	return 0;
}
