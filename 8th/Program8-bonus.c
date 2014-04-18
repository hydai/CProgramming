#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int honai(int in);
int f(int in);

int count = 0;
int main(int argc, const char *argv[])
{
    int input, i;
    FILE *fp, *op;
    if (argc!=3) {
        printf("Input Error!\n");
        exit(1);
    }
    op = fopen(argv[2], "w");
    fp = fopen(argv[1], "r");
    if (fp==NULL) {
        printf("File Error!\n");
        exit(1);
    }
    while (fscanf(fp, "%d", &input)==1) {
 
        input /= 3;

        count = honai(input);
    
        fprintf(op, "%d\n", count);
    }
    fclose(op);
    fclose(fp);
    return 0;
}

int f(int in)
{
    if (in == 0) {
        return 0;
    }
    else {
        return 3*f(in-1)+6;
    }
}

int honai(int in)
{
    if (in == 1) {
        return 2*f(in-1)+3;
    }
    else {
        return honai(in-1)+2*f(in-1)+3;
    }
}
