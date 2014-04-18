#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KBLU "\x1B[34m"
#define MAX_col 81
#define MAX_row 59
char taiwan_map[59][83] =
{
    {"    ..```  ``                                                                    \n"},
    {"    `..,.``,,                                                                    \n"},
    {"      `..``..                                              `..`                  \n"},
    {"                                                          `....`                 \n"},
    {"                                                      `` ...,...`  ..`,.`.`      \n"},
    {"                                                      ..`,.,,....` ..`..`.`      \n"},
    {"                                                      `......`......``           \n"},
    {"                                                    ..,,....``........     .     \n"},
    {"                                                 `......,...``........`          \n"},
    {"                                                `,,,,,,,,,.,.`.,........         \n"},
    {"                                             `,.:,,,,,:,..`-,..,`.,.``.          \n"},
    {"                                            ```.``.```......,.....````           \n"},
    {"                                         `.........``````..,`````````.`          \n"},
    {"                                         `.........```````.``````````.           \n"},
    {"                                        ,,,,.,,..```````.``...:,,,..             \n"},
    {"                                      ..`.,,.:,,:,...``.```,..:,.,.`             \n"},
    {"                                     ..,,.`.,`.,,...```````.````````             \n"},
    {"                                  `.`..``...````...````.````````.`               \n"},
    {"                                  `.`.....``.....``````..`````````               \n"},
    {"        ` `````                   `````..```..`````````..``````.``               \n"},
    {"    `. `..``..`                 `.``````....```````````....,..,.`                \n"},
    {"  ``..                          .,....,..``````````````.,..,.,:.                 \n"},
    {"  ``.`                          .,..,.:,```````````````...`....`                 \n"},
    {"                               ``.``....```````````````.````````                 \n"},
    {"                               .```````.``````````````.`````````                 \n"},
    {"                             ``````````..```.,.,,.:,...```````.                  \n"},
    {"              ``            `..,.,,.,,.`.```.....`..``.````````                  \n"},
    {"              `             ```.....,,...`````````````.````````                  \n"},
    {"            ``.``.`....`    .````````....`````````````.``````.`                  \n"},
    {"            .``..,`,,.,`   ``````.....`....```````````.``````.                   \n"},
    {"           `,`,..`  ` `    `````...`````.....```````..````````                   \n"},
    {"             .,.``         `...,...````````..```````.`````````                   \n"},
    {"              ``           .,,,,.,,..``````..`````...`````````                   \n"},
    {"                           `,,.,..,...`````....,...```````````                   \n"},
    {"                           `.`.............,......`````````..                    \n"},
    {"                         ......................````````...`                      \n"},
    {"                         .,...................`....,.,,.``                       \n"},
    {"                          `...................`....,.,,..`                       \n"},
    {"                      ```.`............,..,...``````````.                        \n"},
    {"                      ...,`,,.......,,.:,,:..``````````.`                        \n"},
    {"                      ``   ``................```````````                         \n"},
    {"                             ..........````.`..``````.                           \n"},
    {"                             `......```````.``.``````.        ``                 \n"},
    {"                              ..,...``````..``.`````.`        '`                 \n"},
    {"                              ......```````....```..`                            \n"},
    {"                               `.........`.`````.                                \n"},
    {"                                `..,,.,,,,,````.`                                \n"},
    {"                                 `.,,.,.,,,.```.                                 \n"},
    {"                                   ....``...````                                 \n"},
    {"                                    `.````..``.`        .,                       \n"},
    {"                                 `   `.```.```.        ,.'                       \n"},
    {"                                 .     .``..```        ``                        \n"},
    {"                                       `..`.```                                  \n"},
    {"                                        ......`                                  \n"},
    {"                                        `.```.`                                  \n"},
    {"                                         ..````                                  \n"},
    {"                                         ..`..`                                  \n"},
    {"                                         .`.`.`                                  \n"},
    {"                                         .``.                                    \n"}
};


struct ID_table
{
	char sex;
	int per_num[9];
	int birth_location;
    char result[11];
};

void input( struct ID_table *ID )
{
    char in;
    scanf("%c", &in);
    ID -> sex = in;
    ID -> per_num[0] = (in == 'M')?1:2;
}

void produce_ID( struct ID_table *ID )
{
    int lacation_value, check_number;
    int i;
    
    ID -> birth_location = rand() % 26;
    
    switch( ID -> birth_location )
    {
        case 0:
            lacation_value = 10;
            break;
            
        case 1:
            lacation_value = 11;
            break;
            
        case 2:
            lacation_value = 12;
            break;
            
        case 3:
            lacation_value = 13;
            break;
            
        case 4:
            lacation_value = 14;
            break;
            
        case 5:
            lacation_value = 15;
            break;
            
        case 6:
            lacation_value = 16;
            break;
            
        case 7:
            lacation_value = 17;
            break;
            
        case 8:
            lacation_value = 34;
            break;
            
        case 9:
            lacation_value = 18;
            break;
            
        case 10:
            lacation_value = 19;
            break;
            
        case 11:
            lacation_value = 20;
            break;
            
        case 12:
            lacation_value = 21;
            break;
            
        case 13:
            lacation_value = 22;
            break;
            
        case 14:
            lacation_value = 35;
            break;
            
        case 15:
            lacation_value = 23;
            break;
            
        case 16:
            lacation_value = 24;
            break;
            
        case 17:
            lacation_value = 25;
            break;
            
        case 18:
            lacation_value = 26;
            break;
            
        case 19:
            lacation_value = 27;
            break;
            
        case 20:
            lacation_value = 28;
            break;
            
        case 21:
            lacation_value = 29;
            break;
            
        case 22:
            lacation_value = 32;
            break;
            
        case 23:
            lacation_value = 30;
            break;
            
        case 24:
            lacation_value = 31;
            break;
            
        case 25:
            lacation_value = 33;
            break;
        default :
            lacation_value = 0;
            break;
    }
    
    for( i = 1 ; i < 8 ; i++ )
        ID -> per_num[i] = rand()%10;
    
	check_number = (lacation_value / 10) * 1 + (lacation_value % 10) * 9 + ID -> per_num[0] * 8 + ID -> per_num[1] * 7 + ID -> per_num[2] * 6 + ID -> per_num[3] * 5 + ID -> per_num[4] * 4 + ID -> per_num[5] * 3 + ID -> per_num[6] * 2 + ID -> per_num[7] * 1;
    
	if( (check_number % 10) != 0 )
		ID -> per_num[8] = 10 - check_number % 10;
	else
		ID -> per_num[8] = 0;
    
    
    ID -> result[0] = ID -> birth_location + 65;
    for( i = 1 ; i < 10 ; i++ )
        ID -> result[i] = ID -> per_num[i-1] + '0';
    ID -> result[10] = '\0';
}

void find_location( int location, int *row, int *col)
{
    switch( location )
    {
        case 0:
            //printf("出生地：臺北市\n");
            *row = 6;
            *col = 60;
            break;
            
        case 1:
            //printf("出生地：臺中市\n");
            *row = 17;
            *col = 42;
            break;
            
        case 2:
            //printf("出生地：基隆市\n");
            *row = 5;
            *col = 64;
            break;
            
        case 3:
            //printf("出生地：臺南市\n");
            *row = 40;
            *col = 28;
            break;
            
        case 4:
            //printf("出生地：高雄市\n");
            *row = 47;
            *col = 34;
            break;
            
        case 5:
            //printf("出生地：新北市\n");
            *row = 8;
            *col = 65;
            break;
            
        case 6:
            //printf("出生地：宜蘭縣\n");
            *row = 14;
            *col = 66;
            break;
            
        case 7:
            //printf("出生地：桃園縣\n");
            *row = 7;
            *col = 53;
            break;
            
        case 8:
            //printf("出生地：嘉義市\n");
            *row = 30;
            *col = 37;
            break;
            
        case 9:
            //printf("出生地：新竹縣\n");
            *row = 10;
            *col = 54;
            break;
            
        case 10:
            //printf("出生地：苗栗縣\n");
            *row = 12;
            *col = 46;
            break;
            
        case 11:
            //printf("出生地：臺中縣\n");
            *row = 16;
            *col = 48;
            break;
            
        case 12:
            //printf("出生地：南投縣\n");
            *row = 24;
            *col = 48;
            break;
            
        case 13:
            //printf("出生地：彰化縣\n");
            *row = 21;
            *col = 34;
            break;
            
        case 14:
            //printf("出生地：新竹市\n");
            *row = 9;
            *col = 48;
            break;
            
        case 15:
            //printf("出生地：雲林縣\n");
            *row = 27;
            *col = 32;
            break;
            
        case 16:
            //printf("出生地：嘉義縣\n");
            *row = 32;
            *col = 30;
            break;
            
        case 17:
            //printf("出生地：臺南縣\n");
            *row = 37;
            *col = 33;
            break;
            
        case 18:
            //printf("出生地：高雄縣\n");
            *row = 44;
            *col = 38;
            break;
            
        case 19:
            //printf("出生地：屏東縣\n");
            *row = 53;
            *col = 43;
            break;
            
        case 20:
            //printf("出生地：花蓮縣\n");
            *row = 28;
            *col = 62;
            break;
            
        case 21:
            //printf("出生地：臺東縣\n");
            *row = 44;
            *col = 52;
            break;
            
        case 22:
            //printf("出生地：金門縣\n");
            *row = 20;
            *col = 7;
            break;
            
        case 23:
            //printf("出生地：澎湖縣\n");
            *row = 28;
            *col = 16;
            break;
            
        case 24:
            //printf("出生地：陽明山管理局\n");
            *row = 8;
            *col = 65;
            break;
            
        case 25:
            //printf("出生地：連江縣\n");
            *row = 0;
            *col = 5;
            break;
        default :
            break;
    }
}

void print_graph( struct ID_table *ID )
{
    int i, j;
    int row = 0, col = 0;
    int tmp_row = 0, tmp_col = 0;
    
    find_location( ID -> birth_location, &row, &col);
    
    if( ID -> sex == 'M' )
        printf("%s", KBLU);
    else
        printf("%s", KRED);
    for( i = 0 ; i <= row ; i++ )
    {
        system("clear");
        for( j = 0 ; j < 59 ; j++ )
            if( i == j )
                printf("%.*s%s%s", tmp_row, taiwan_map[j], ID -> result, taiwan_map[j] + 10);
            else
                printf("%s", taiwan_map[j]);
        usleep(100000);
    }
    for( i = 0 ; i <= col ; i++ )
    {
        system("clear");
        for( j = 0 ; j < 59 ; j++ )
            if( j == row )
            {
                printf("%.*s%s%s", tmp_col, taiwan_map[j], ID -> result, taiwan_map[j] + 10 + tmp_col);
                tmp_col++;
            }
            else
                printf("%s", taiwan_map[j]);
        usleep(100000);
    }
    
}
/*
void print_result( struct ID_table *ID )
{
    printf("%c", ID -> birth_location + 65);
    int i;
    for( i = 0 ; i < 9 ; i++ )
        printf("%d", ID -> per_num[i]);
    printf("\n");
}*/


void print_result( struct ID_table *ID )
{
    printf("%s\n", ID -> result);
}
int main()
{
	srand(time(NULL));
	struct ID_table ID;
    
	input( &ID );
	produce_ID( &ID );
	//print_graph( &ID );
	print_result( &ID );
    printf("%s\n", KNRM);
    return 0;
}