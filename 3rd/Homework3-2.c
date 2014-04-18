#include <stdio.h>

struct ID_table
{
	int ID_number;
	int per_num[9];
	int year, institution, department;
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

void depart_class( struct ID_table *ID )
{
    ID -> year = ID -> per_num[8]*100 + ID ->  per_num[7]*10 + ID -> per_num[6];
	ID -> institution = ID -> per_num[5]*10 + ID -> per_num[4];
	ID -> department = ID -> per_num[3];
}

void is_right( struct ID_table *ID )
{
	if( (ID -> year == 101) || (ID -> year == 100) || (ID -> year == 99) || (ID -> year == 98) )
		ID -> flag = 1;
	else
		ID -> flag = 0;
    
    if( ((ID -> institution == 6) || (ID -> institution == 4)) && (ID -> flag == 1) )
		ID -> flag = 1;
	else
		ID -> flag = 0;
}

void print_result( struct ID_table *ID)
{
	char years_ch[4][20] = { {"大四"}, {"大三"}, {"大二"}, {"大一"}};
	char institution_ch[2][20] = { {"人文社會學院"}, {"電機資訊學院"}};
	char department_ch[2][10][100] = { { {"跨系所招生"}, {"中國文學系"}, {"外國語文學系"}, {"歷史研究所"}, {"語言學研究所"}, {"社會學研究所"}, {"人類學研究所"}, {"哲學研究所"}, {"人文社會學院學士班"}, {"台灣文學研究所"}}, { {"電機資訊學院學士班"}, {"電機工程學系"}, {"資訊工程學系"}, {"電子工程研究所"}, {"通訊工程研究所"}, {"資訊系統與應用研究所"}, {"光電工程研究所"}, {"電資院積體電路產業專班"}, {"電資院半導體元件及製程專班"}, {"電資院電力電子專班"}}};
    
    if( ID -> flag == 0 )
    {
        printf("輸入格式錯誤！\n請重新輸入：");
        return;
    }
	int institution_temp;
	if( ID -> institution == 4)
		institution_temp = 0;
	else
		institution_temp = 1;
    
	printf("年級:%s\n", years_ch[ ID -> year - 98 ]);
	printf("學院:%s\n", institution_ch[ institution_temp ]);
	printf("系所:%s\n", department_ch[ institution_temp ][ ID -> department]);
}

int main()
{
	struct ID_table ID;
	
	int i;
	
    
    do{
        for(i = 0 ; i < 9 ; i++)
            ID.per_num[i] = 0;
        
        get_number( &ID );
        depart_class( &ID );
        is_right( &ID );
        print_result( &ID );
    }while(ID.flag != 1);
    
	return 0;
}
