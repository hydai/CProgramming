// test.p.cpp : 定義主控台應用程式的進入點。
//

#include <stdio.h>
#include <stdlib.h>

int input_and_check( char *ID )
{
	printf("請輸入身份證字號:");
    scanf("%s", ID);
    int flag = 0;//false
	//第一個不是大寫字母
	if( (ID[0] < 'A') || (ID[0] > 'Z') )
		flag = 0;
	//後九碼有非數字
	int i;
	for( i = 1 ; i < 10 ; i++ )
		if( (ID[i] > '9') || (ID[i] < '0') )
			flag = 0;
	//check_rule
    int name_value;
    switch( ID[0] - 65 )
    {
        case 0:
            name_value = 10;
            break;
            
        case 1:
            name_value = 11;
            break;
            
        case 2:
            name_value = 12;
            break;
            
        case 3:
            name_value = 13;
            break;
            
        case 4:
            name_value = 14;
            break;
            
        case 5:
            name_value = 15;
            break;
            
        case 6:
            name_value = 16;
            break;
            
        case 7:
            name_value = 17;
            break;
            
        case 8:
            name_value = 34;
            break;
            
        case 9:
            name_value = 18;
            break;
            
        case 10:
            name_value = 19;
            break;
            
        case 11:
            name_value = 20;
            break;
            
        case 12:
            name_value = 21;
            break;
            
        case 13:
            name_value = 22;
            break;
            
        case 14:
            name_value = 35;
            break;
            
        case 15:
            name_value = 23;
            break;
            
        case 16:
            name_value = 24;
            break;
            
        case 17:
            name_value = 25;
            break;
            
        case 18:
            name_value = 26;
            break;
            
        case 19:
            name_value = 27;
            break;
            
        case 20:
            name_value = 28;
            break;
            
        case 21:
            name_value = 29;
            break;
            
        case 22:
            name_value = 32;
            break;
            
        case 23:
            name_value = 30;
            break;
            
        case 24:
            name_value = 31;
            break;
            
        case 25:
            name_value = 33;
            break;
        default :
            name_value = 0;
            break;
    }
    
	for( i = 1 ; i < 10 ; i++ )
		ID[i] -= 48;
    
	int check_number;
	check_number = (name_value / 10) * 1 + (name_value % 10) * 9 + ID[1] * 8 + ID[2] * 7 + ID[3] * 6 + ID[4] * 5 + ID[5] * 4 + ID[6] * 3 + ID[7] * 2 + ID[8] * 1 + ID[9] * 1;
	if( (check_number % 10) != 0 )
		flag = 0;
	else
		flag = 1;
	return flag;
}

void print( char *ID )
{
	if( ID[1] == 1  )
		printf("性別:男性\n");
	else
		printf("性別:女性\n");
    
    switch( ID[0] - 65 )
    {
        case 0:
            printf("出生地：臺北市\n");
            break;
            
        case 1:
            printf("出生地：臺中市\n");
            break;
            
        case 2:
            printf("出生地：基隆市\n");
            break;
            
        case 3:
            printf("出生地：臺南市\n");
            break;
            
        case 4:
            printf("出生地：高雄市\n");
            break;
            
        case 5:
            printf("出生地：新北市\n");
            break;
            
        case 6:
            printf("出生地：宜蘭縣\n");
            break;
            
        case 7:
            printf("出生地：桃園縣\n");
            break;
            
        case 8:
            printf("出生地：嘉義市\n");
            break;
            
        case 9:
            printf("出生地：新竹縣\n");
            break;
            
        case 10:
            printf("出生地：苗栗縣\n");
            break;
            
        case 11:
            printf("出生地：臺中縣\n");
            break;
            
        case 12:
            printf("出生地：南投縣\n");
            break;
            
        case 13:
            printf("出生地：彰化縣\n");
            break;
            
        case 14:
            printf("出生地：新竹市\n");
            break;
            
        case 15:
            printf("出生地：雲林縣\n");
            break;
            
        case 16:
            printf("出生地：嘉義縣\n");
            break;
            
        case 17:
            printf("出生地：臺南縣\n");
            break;
            
        case 18:
            printf("出生地：高雄縣\n");
            break;
            
        case 19:
            printf("出生地：屏東縣\n");
            break;
            
        case 20:
            printf("出生地：花蓮縣\n");
            break;
            
        case 21:
            printf("出生地：臺東縣\n");
            break;
            
        case 22:
            printf("出生地：金門縣\n");
            break;
            
        case 23:
            printf("出生地：澎湖縣\n");
            break;
            
        case 24:
            printf("出生地：陽明山管理局\n");
            break;
            
        case 25:
            printf("出生地：連江縣\n");
            break;
        default :
            printf("格式錯誤!\n");
            break;
    }
}

int main()
{
    char ID[11];
    
	int temp;
    
	do{
		temp = input_and_check( ID );
	}while(temp != 1);
    
	print( ID );
	return 0;
}
