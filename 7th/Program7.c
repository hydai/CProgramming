/*
 * Program 7 - Address Book
 *
 * Author : PIatan
 * Ver1.0:
 *    insert
 *    update
 *    delete
 *    sort
 *    show
 *    save
 *    exit
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1000
#define MAX_INPUT_DATA 100000

typedef struct {
    int id;
    char* name;
    char* email;
    char* phone;
}Entry;

void welcome();
void read();
void command();
void insert();
void update();
void delete_();
void sort_();
int compare();
void show();
void save();
void exit_();

Entry data[MAX_INPUT_DATA];
int tail = 0;

int main(int argc, const char *argv[])
{
    welcome();
    read();
    while (1) {
        command();
    }
    return 0;
}

void welcome(void)
{
    printf("===================================================\n");
    printf("|               Address Book Ver 1.0              |\n");
    printf("|                  Author : PIatan                |\n");
    printf("|                                                 |\n");
    printf("|                  The way to use :               |\n");
    printf("|       First, initial data read from in.txt      |\n");
    printf("|                Then, you can use :              |\n");
    printf("|            insert, update, delete, sort         |\n");
    printf("|                  show, save, exit               |\n");
    printf("===================================================\n");
}

void read(void)
{
    FILE *fp;
    char *cut_pt, *pt;
    char buffer[MAX_INPUT_LEN];
    fp = fopen( "in.txt", "r" );
    if ( fp == NULL ) {
        printf("Can not open the file!\n");
        exit(1);
    }
    
    while ( fgets( buffer, sizeof(buffer), fp ) ) {
        
        if ( buffer[0] == '\n' ) {
            continue;
        } 

        pt = strstr(buffer, "\n");
        if ( pt != NULL ) {
            *pt = '\0';
        }
       
        
        /* cut id */
        cut_pt = strtok( buffer, "," );
        data[tail].id = atoi(cut_pt);
        /* cut name */
        cut_pt = strtok( NULL, "," );
        data[tail].name = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
        strcpy( data[tail].name, cut_pt );
        /* cut email */
        cut_pt = strtok( NULL, "," );
        data[tail].email = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
        strcpy( data[tail].email, cut_pt );
        /* cut phone */
        cut_pt = strtok( NULL, "," );
        data[tail].phone = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
        strcpy( data[tail].phone, cut_pt );
        
        tail++;
    }
    
    fclose(fp);
    return;
}

void command(void)
{
    char buffer[100];
    printf(">");
    fscanf( stdin, "%s", buffer );
    if ( !strcmp( buffer, "insert" ) ) {
        insert();
        return;
    }
    else if ( !strcmp( buffer, "update" ) ) {
        update();
        return;
    }
    else if ( !strcmp( buffer, "delete" ) ) {
        delete_();
        return;
    }
    else if ( !strcmp( buffer, "sort" ) ) {
        sort_();
        return;
    }
    else if ( !strcmp( buffer, "show" ) ) {
        show();
        return;
    }
    else if ( !strcmp( buffer, "save" ) ) {
        save();
        return;
    }
    else if ( !strcmp( buffer, "exit" ) ) {
        exit_();
        return;
    }
    else
    {
        printf("Wrong command!\n");
        return;
    }
}

void insert(void)
{
    char *cut_pt, *pt;
    char buffer[MAX_INPUT_LEN];
    printf("( id ) >> ");
    fscanf( stdin, "%d", &data[tail].id );
    getchar();
    printf("( data ) >> ");
    fgets( buffer, sizeof(buffer), stdin );
    
    
    pt = strstr(buffer, "\n");
    if ( pt != NULL ) {
        *pt = '\0';
    }
    
    /* cut name */
    cut_pt = strtok( buffer, "," );
    data[tail].name = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[tail].name, cut_pt );
    /* cut email */
    cut_pt = strtok( NULL, "," );
    data[tail].email = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[tail].email, cut_pt );
    /* cut phone */
    cut_pt = strtok( NULL, "," );
    data[tail].phone = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[tail].phone, cut_pt );
    
    tail++;
    return;
}

void update(void)
{
    int i, tmp_id, want_tail;
    char buffer[MAX_INPUT_LEN], *cut_pt, *pt;
    printf("( id ) >> ");
    fscanf( stdin, "%d", &tmp_id );
    getchar();

    for ( i = 0 ; i < tail ; i++ ) {
        if ( data[i].id == tmp_id ) {
            want_tail = i;
            break;
        }
    }
    
    free( data[want_tail].name );
    free( data[want_tail].email );
    free( data[want_tail].phone );
    
    
    printf("( data ) >> ");
    fgets( buffer, sizeof(buffer), stdin );
    
    pt = strstr(buffer, "\n");
    if ( pt != NULL ) {
        *pt = '\0';
    }
    
    /* cut name */
    cut_pt = strtok( buffer, "," );
    data[want_tail].name = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[want_tail].name, cut_pt );
    /* cut email */
    cut_pt = strtok( NULL, "," );
    data[want_tail].email = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[want_tail].email, cut_pt );
    /* cut phone */
    cut_pt = strtok( NULL, "," );
    data[want_tail].phone = (char *) malloc ( (strlen(cut_pt)+1) * sizeof(char) );
    strcpy( data[want_tail].phone, cut_pt );

    return;
}

void delete_(void)
{
    int i, tmp_id, want_tail;
    if ( tail < 1 ) {
        printf("There is no element!!\n");
        return;
    }
    printf("( id ) >> ");
    fscanf( stdin, "%d", &tmp_id );
    
    
    for ( i = 0 ; i < tail ; i++ ) {
        if ( data[i].id == tmp_id ) {
            want_tail = i;
            break;
        }
    }
    
    free( data[want_tail].name );
    free( data[want_tail].email );
    free( data[want_tail].phone );
    
    data[want_tail].id = data[tail-1].id;
    data[want_tail].name = data[tail-1].name;
    data[want_tail].email = data[tail-1].email;
    data[want_tail].phone = data[tail-1].phone;
    
    data[tail-1].name = NULL;
    data[tail-1].email = NULL;
    data[tail-1].phone = NULL;

    tail--;
    
    return;
}

int compare( const void *a, const void *b )
{
    return (*(Entry *)a).id < (*(Entry *)b).id ? -1 : 1;
}

void sort_(void)
{
    qsort( data, tail, sizeof(Entry), compare );
}

void show(void)
{
    int i;
    for ( i = 0 ; i < tail ; i++ ) {
        printf("%d    %s    %s    %s\n", data[i].id, data[i].name, data[i].email, data[i].phone);
    }
}

void save(void)
{
    FILE *fp;
    fp = fopen( "in.txt", "w" );
    int i;
    for ( i = 0 ; i < tail ; i++ ) {
        fprintf(fp, "%d,%s,%s,%s\n", data[i].id, data[i].name, data[i].email, data[i].phone);
    }
    fclose(fp);
}

void exit_(void)
{
    printf("===================================================\n");
    printf("|                                                 |\n");
    printf("|               Address Book Ver 1.0              |\n");
    printf("|                  Author : PIatan                |\n");
    printf("|                                                 |\n");
    printf("===================================================\n");
    exit(0);
}
