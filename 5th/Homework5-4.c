#include <stdio.h>
#include <time.h>

#define len 5


char color[] = "SHDC";
//char color[] = "♠♥♦♣";
char number[] = "234567890JQKA";
int flag = 0;
int done[4][13] = {0};

struct card_t
{
	int card_color;
	int num;
	int card_value;//for sorting
} card[len];

void insertion_sort()
{
	int i, j;
	struct card_t tmp;

	//transform value for sorting
	for ( i = 0 ; i < len ; i++ )
	{
		card[i].card_value = ( 4 - card[i].card_color ) * 100 + card[i].num;
	}

	//sorting algorithm
	for ( i = 1 ; i < len ; i++ )
	{
		tmp = card[i];
		j = i - 1;
		while ( j > 0 && card[j].card_value < tmp.card_value )
		{
			card[j+1] = card[j];
			j--;
		}
	
		card[j+1] = tmp;
	}
}

void rand_card()
{
    int i = 0;
    while ( i < 5 )
    {
        card[i].card_color = rand() % 4;
        card[i].num = rand() % 13;
        
        if ( done[ card[i].card_color ][ card[i].num ] == 1 )
            continue;
        
        done[ card[i].card_color ][ card[i].num ] = 1;
        i++;
    }
}

void find_kind()
{
    int i;
    for ( i = 0 ; i < 5 ; i++ )
    {
        if( card[i].card_color == card[0].card_color )
            flag += 1;
        else
            flag = 0;
    }
}

void print_result()
{
    int i, j;
	for ( i = 0 ; i < 4 ; i++ )
		for ( j = 0 ; j < 13 ; j++ )
    	{
			if ( done[i][j] == 1 )
			{
        		printf("%c ", color[ i ]);
        		if ( j == 8 )
            		printf("10\n");
        		else
            		printf("%c\n", number[ j ]);
    		}
		}

    if ( flag == 5 )
        printf("同花!!\n");
    else
        printf("不是同花!!\n");
}

int main()
{
    srand(time(NULL));

    printf("S = 黑桃, H = 紅心, D = 方塊, C = 梅花\n");
    rand_card();
    find_kind();
	insertion_sort();
	print_result();
    
    return 0;
}
