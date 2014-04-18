#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN 1000
#define MAX_VA_LEN 100
#define MAX_LINE_LEN 100

#define NONE "\033[m"
#define L_GREEN "\033[1;32;32m"
#define L_BLUE "\033[1;32;34m"

enum type { Type_specifier, Namespace, Assign_op, Unary_op, Valuespace, Pass_mode, End_mode };

typedef struct {
   enum type O_type;
   char namespace[ MAX_BUF_LEN ];
   int used;
} Object;

void initialize();

int check_unary( int line, int statement, int current_term );
int check_name_rule( int line, int statement, int current_term );
int check_name_assign( int line, int statement, int current_term );
int check_grammer( int line, int statement );
void print_result();

Object object[MAX_LINE_LEN][MAX_VA_LEN][MAX_VA_LEN];
char namespace[MAX_VA_LEN][MAX_BUF_LEN];
char tmp_statement[MAX_LINE_LEN][MAX_VA_LEN][MAX_BUF_LEN];
int line_statement[MAX_LINE_LEN];
int term_number[MAX_LINE_LEN][MAX_VA_LEN];
int namespace_used_count = 0;


int main(int argc, const char *argv[])
{
   int i, status = 1;
   int line_count, statement_count, term_count;
   char buffer[ MAX_BUF_LEN ];
   FILE *fp;
   char *pt = NULL, *tmp_pt = NULL;
   int flag = 0;

   if (argc < 2) {
      printf("Please key in the file!\n");
      exit(1);
   }

   for (i = 1; i < argc; i++) {

      initialize();
      status = 1;

      fp = fopen( argv[i], "r");
      printf("===In \"%s\"===\n", argv[i]);

      line_count = 0;
      while ( fgets( buffer, sizeof(buffer), fp) != NULL ) {
         statement_count = 0;
         term_count = 0;
         line_count++;

         pt = strstr(buffer,"\n");
         if ( pt != NULL ) {
            *pt = '\0';
         }
         
         /* cut statement */
         if ( strstr(buffer, ";") == NULL ) {
            flag = 1;
         }
         pt = strtok(buffer, ";");
   //printf("pass1: %s\n", pt);
         while ( pt!=NULL ) {
            strncpy( tmp_statement[line_count][statement_count], pt, MAX_BUF_LEN );
            tmp_pt = strstr( tmp_statement[line_count][statement_count], "//");
            if ( (tmp_pt == NULL) && (flag == 0) ) {
               strcat( tmp_statement[line_count][statement_count], " ;");
            }
    //        else {
      //         printf("%d %d\n", line_count, statement_count);
        //    }
   //printf("pass2: %s\n", tmp_statement[line_count][statement_count]);
            statement_count++;
            pt = strtok(NULL, ";");
         }
         line_statement[line_count] = statement_count;
   //printf("count: %d\n", line_statement[line_count]);

         statement_count = 0;
         /* reset the count for memory the while i */
         while ( statement_count < line_statement[line_count] ) {
            /* toke the statement */
            
            term_count = 0;
            /* first check it has // or not */
    //printf("final1\n");
            pt = strstr( tmp_statement[line_count][statement_count], "//" );
            if ( pt != NULL ) {
               object[line_count][statement_count][term_count].used = 1;
               object[line_count][statement_count][term_count].O_type = Pass_mode;
               strncpy( object[line_count][statement_count][term_count].namespace, tmp_statement[line_count][statement_count], MAX_BUF_LEN );
               break;
            }
    //printf("final2\n");
            /* second check the ";" */ 
            pt = strstr( tmp_statement[line_count][statement_count], ";" );
            if ( pt == NULL ) {
               status = 0;
               goto fault;
            }
            
    //printf("final3\n");
            /* check grammer */
            /* first token the statement */
            pt = strtok( tmp_statement[line_count][statement_count] , " ");
            while ( pt != NULL ) {
               object[line_count][statement_count][term_count].used = 1;
               strncpy( object[line_count][statement_count][term_count].namespace, pt, MAX_BUF_LEN );
               term_count++;
               //printf("%d %s\n", term_count, object[line_count][term_count-1].namespace);
               pt = strtok(NULL, " ");
            }
            
    //printf("final4\n");
            term_number[line_count][statement_count] = term_count;

    //printf("%d %d\n", line_count, statement_count);
            status = check_grammer( line_count, statement_count );
            
    //printf("final5\n");
            if ( status == 0 ) {
               goto fault;
            }
            statement_count++;
         }
      }

      fault:
      if ( status == 0 ) {
         printf("Error: Line%d\n", line_count);
      }
   //printf("final\n");

      if ( status == 1 ) {
         print_result();
      }
      
      fclose(fp);
   }
   return 0;
}

void initialize()
{
    int i, j, k;
    memset(namespace, 0, MAX_VA_LEN * MAX_BUF_LEN);
    for (i = 0; i < MAX_LINE_LEN; i++) {
       for (j = 0; j < MAX_VA_LEN; j++) {
          for (k = 0; k < MAX_BUF_LEN; k++) {
             object[i][j][k].used = 0;
          }
          term_number[i][j] = 0;
       }
       line_statement[i] = 0;
    }
}

int check_name_rule( int line, int statement, int current_term )
{
    int status = 1;
    if ( object[line][statement][current_term+1].O_type != Assign_op ) {
        return 0;
    }
    else {
        if ( object[line][statement][current_term+2].O_type == Valuespace ) {
            if ( object[line][statement][current_term+3].O_type == End_mode ) {
               return 1;
            }
            else if ( object[line][statement][current_term+3].O_type == Unary_op) {
               status = check_unary( line, statement, current_term+3 );
            }
            else {
               status = 0;
            }
        }
        else if ( object[line][statement][current_term+2].O_type == Namespace ) {
            if ( !check_name_assign( line, statement, current_term+2 ) ) {
               return 0;
            }
            
            if ( object[line][statement][current_term+3].O_type == End_mode ) {
               return 1;
            }
            else if ( object[line][statement][current_term+3].O_type == Unary_op) {
               status = check_unary( line, statement, current_term+3 );
            }
            else {
               status = 0;
            }
        }
        else {
            status = 0;
        }
    }  
    
    return status;
}

int check_grammer( int line, int statement )
{
    int status = 1;
    int current_term = 0;
//printf("term num: %d\n", term_number[line][statement]);
    while ( current_term < term_number[line][statement] ) {
        /* check if it is type_assign */
        if ( !strcmp(object[line][statement][current_term].namespace,"int" ) ) {
            /* int type */
            object[line][statement][current_term].O_type = Type_specifier;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"long" ) ) {
            /* long type */
            object[line][statement][current_term].O_type = Type_specifier;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"short" ) ) {
            /* short type */
            object[line][statement][current_term].O_type = Type_specifier;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"float" ) ) {
            /* float type */
            object[line][statement][current_term].O_type = Type_specifier;
            current_term++;
            continue;
        }
        
        /* check if it is assign_op || unary_op */
        if ( !strcmp(object[line][statement][current_term].namespace,"=" ) ) {
            /* assign_op */
            object[line][statement][current_term].O_type = Assign_op;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"+" ) ) {
            /* unary_op_+ */
            object[line][statement][current_term].O_type = Unary_op;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"-" ) ) {
            /* unary_op_- */
            object[line][statement][current_term].O_type = Unary_op;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"*" ) ) {
            /* unary_op_* */
            object[line][statement][current_term].O_type = Unary_op;
            current_term++;
            continue;
        }
        if ( !strcmp(object[line][statement][current_term].namespace,"/" ) ) {
            /* unary_op_/ */
            object[line][statement][current_term].O_type = Unary_op;
            current_term++;
            continue;
        }
        
        /* check if it is value */
        switch( object[line][statement][current_term].namespace[0] ) {
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                object[line][statement][current_term].O_type = Valuespace;
                current_term++;
                continue;
            default:
                break;
        }
        
        /* check if it is ; */
        if ( !strcmp(object[line][statement][current_term].namespace,";" ) ) {
            /* End_mode */
            object[line][statement][current_term].O_type = End_mode;
            current_term++;
            continue;
        }
        
        /* other is name */
        object[line][statement][current_term].O_type = Namespace;
        current_term++;
    }
    
    /* check grammer */
    current_term = 0;

       
    /* check if the first term is a type assignment || a name. If it's not both, then fail! */
    switch ( object[line][statement][current_term].O_type ) {
       case Type_specifier:
          if ( object[line][statement][current_term+1].O_type != Namespace ) {
             return 0;
          }
          else {
             strncpy( namespace[ namespace_used_count ], object[line][statement][current_term+1].namespace, MAX_BUF_LEN );
             namespace_used_count++;
                
             if ( object[line][statement][current_term+2].O_type == Assign_op ) {
                status = check_name_rule( line, statement, current_term + 1 );
             }
             else if ( object[line][statement][current_term+2].O_type == End_mode ){
                status = 1;
                break;
             }
             else {
                return 0;
             }
          }
          break;

       case Namespace:

          if ( !check_name_assign( line, statement, current_term ) ) {
             return 0;
          }
          status = check_name_rule( line, statement, current_term );
          break;
           
       default:
          status = 0;
          break;
    }
   
   return status;
}

void print_result()
{
   int i, j, k;
   for (i = 0; i < MAX_LINE_LEN; i++) {
      for (j = 0; j <= line_statement[i]; j++) {
         for (k = 0; k <= term_number[i][j]; k++) {
            //printf("\nnow: %s\n", object[i][j][k].namespace);
            if ( object[i][j][k].used == 1 ) {
               switch ( object[i][j][k].O_type ) {
                  case Type_specifier:
                     printf( L_GREEN "%s" NONE, object[i][j][k].namespace);
                     break;
                  case Assign_op:
                     printf( L_BLUE "%s" NONE, object[i][j][k].namespace);
                     break;
                  case Namespace:
                     printf("%s", object[i][j][k].namespace);
                     break;
                  case End_mode:
                     printf("%s", object[i][j][k].namespace);
                     break;
                  case Pass_mode:
                     printf("%s", object[i][j][k].namespace);
                     break;
                  default:
                     printf("%s", object[i][j][k].namespace);
                     break;
               }
            }
            else {
               break;
            }
            printf(" ");
         }
         if ( j == line_statement[i]-1 ) {
            printf("\n");
         }
      }
   }
}

int check_name_assign( int line, int statement, int current_term )
{
    int i, assign_or_not = 0;
    /* check name has already assigned */
    if ( namespace_used_count == 0 ) {
        return 0;
    }
    else {
        for (i = 0; i < namespace_used_count; i++) {
            if ( !strcmp(object[line][statement][current_term].namespace, namespace[i]) ) {
                assign_or_not ++;
            }
        }
        if ( assign_or_not == 0 ) {
            return 0;
        }
    }
    return 1;
}

int check_unary( int line, int statement, int current_term )
{
   int status = 1;
   if ( current_term + 2 >= term_number[line][statement] ) {
      return 0;
   }
   
   
   if ( object[line][statement][current_term+1].O_type == Valuespace ) {
      if ( object[line][statement][current_term].namespace[0] == '/' ) {
         if ( !strcmp( object[line][statement][current_term+1].namespace, "0") ) {
            return 0;
         }
      }
      if ( object[line][statement][current_term+2].O_type == End_mode ) {
         return 1;
      }
      else if ( (object[line][statement][current_term+2].O_type == Unary_op) && ((current_term + 3) < term_number[line][statement]) ) {
         status = check_unary( line, statement, current_term+2);
      }
      else {
         status = 0;
      }
   }
   else if ( object[line][statement][current_term+1].O_type == Namespace ) {
      if ( !check_name_assign( line, statement, current_term+1 ) ) {
         return 0;
      }
      
      if ( object[line][statement][current_term+2].O_type == End_mode ) {
         return 1;
      }
      else if ( (object[line][statement][current_term+2].O_type == Unary_op) && ((current_term + 3) < term_number[line][statement]) ) {
         status = check_unary( line, statement, current_term+2 );
      }
      else {
         status = 0;
      }
   }
   else {
      status = 0;
   }  
    
   return status;
}
