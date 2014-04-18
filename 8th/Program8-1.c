#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void honai(int in);

unsigned long long int f[MAX];

int main(int argc, const char *argv[])
{
    int input, count = 0, i;
    FILE *fp;
    if (argc!=2) {
        printf("Input Error!\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp==NULL) {
        printf("File Error!\n");
        exit(1);
    }
    fscanf(fp,"%d", &input);

    f[0] = 0;
   
    count = honai(input);
    
    for (i = input/2 - 1; i >= 0; i--) {
        count += 2*f[i] + 3;
    }
    printf("%d\n", count);
    fclose(fp);
    return 0;
}

int honai(int in)
{
    if (in/2 == 0) {
        return 4;
    }
    else {
        return 3*honai(in-2);
    }
}
