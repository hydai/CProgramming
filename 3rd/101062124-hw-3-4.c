#include <stdio.h>

void input( char *ID )
{
    scanf("%s", ID);
}

void check_and_print( char *ID )
{
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
    input( ID );
    check_and_print( ID );
	return 0;
}