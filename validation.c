#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "validation.h"

char errors[10][150];
int errors_number = 0;

void input(char *message,char *string,int length,char *field_name,int required)
{
    int x = 0;

    printf("%s",message);
    fgets(string,length,stdin);
    if(*string != '\n' && strcmp(string,"-\n") != 0) {
        while(*string)
        {
            if(*string == '\n')
            {
                *string = '\0';
                return;
            }
            x++;
            if(x == length)
            {
                *string = '\0';
                return;
            }
            string++;
        }
        scanf("%*[^\n]");scanf("%*c");//clear upto newline
    }
    else if(required) {strcpy(string,"-"); addError(" field must not be left empty!\0", field_name);}
    else {strcpy(string,"-");}
    return;
}

int checkSearchText(char buffer[]){

    int c1;
    c1 = sscanf(buffer,",%[^\t\n]", buffer);
    if(c1 != 1)
    {
        return 0;
    }
    return 1;
}

char* stristr( const char* str1, const char* str2 )
{
    const char* p1 = str1 ;
    const char* p2 = str2 ;
    const char* r = *p2 == 0 ? str1 : 0 ;

    while( *p1 != 0 && *p2 != 0 )
    {
        if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )
        {
            if( r == 0 )
            {
                r = p1 ;
            }

            p2++ ;
        }
        else
        {
            p2 = str2 ;
            if( r != 0 )
            {
                p1 = r + 1 ;
            }

            if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )
            {
                r = p1 ;
                p2++ ;
            }
            else
            {
                r = 0 ;
            }
        }

        p1++ ;
    }

    return *p2 == 0 ? (char*)r : 0 ;
}


void addError(const char *error, char *field_name) {
    errors_number++;
    strcpy(errors[errors_number-1],field_name);
    errors[errors_number-1][strlen(field_name)] = '\0';
    strcat(errors[errors_number-1],error);
    return;
}

void printErrors(char *operation) {
    int i;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
    printf("\n\n==> %s operation has been failed because of the following errors :\n", operation);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12);
    for(i = 0; i<errors_number; i++){
        printf("    * %s \n", errors[i]);
    }
    errors_number = 0;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return;
}

void printSuccess(char *Message) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 47);
    printf("\n\n==> %s\n", Message);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return;
}


void RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

int validateNegative(int n)
{
    if(n<0) return false;
    else return true;
}


int validateInteger(char buffer[]){

    int c1, num;
    char term = NULL;
    char temp[100];
    strcpy(temp,buffer);
    RemoveSpaces(temp);
    c1 = sscanf(temp,"%d%c", &num, &term);
    if(c1 != 1 || term != NULL)
    {
        return 0;
    }
    return 1;
}

int validateDate(char buffer[]){

    int d,m,y;
    int c1 = 0, c2 = 0;

    /*
    printf("Enter The Date : ");
    scanf("%10s",buffer);
    while(getchar() != '\n');
    */

    //use sscanf to extract numbers from string with formast dd/mm/yyyy
    c1 = sscanf(buffer,"%d/%d/%d",&d,&m,&y);
    if(c1!=3)
        c2 = sscanf(buffer,"%d-%d-%d",&d,&m,&y);


    if(c1!=3&&c2!=3) //check if sscanf couldn't fill all variables with numbers
    {
        addError("Enter a valid date please dd/mm/yyyy or dd-mm-yyyy\0","");
    }
    else //validate those numbers entered
    {
        if(d<=0||d>31) addError("Enter a valid day please\0","");
        else if(m<=0||m>12) addError("Enter a valid month please\0","");
        else if(y>2017||y<1900) addError("The year should be between 1900 and 2017\0","");
        else {return c1 == 3 ? 1 : 2;}
    }
    return 0;
}

int validateMail(char *s)
{
    int length=strlen(s), ind1=0, ind2=0, ind3=0;
    int i,j,k;

    if ( (s[0]<'a') || (s[0]>'z') ) return 0;
    else
    {
    for (i=1;i<length;i++)
    {
        if (s[i]=='@')
        {
            ind1=i+1;
            break;
        }
        else
            if ( (s[i]<'a') || (s[i]>'z') ) return 0;
    }


    for (j=ind1;j<length;j++)
    {
        if (s[j]=='.')
        {
            ind2=j+1;
            break;
        }
        else
            if ( (s[j]<'a') || (s[j]>'z') ) return 0;
    }


    for (k=ind2;k<length;k++)
    {
        if (s[k]=='.')
        {
            ind3=k+1;
            break;
        }
        else
            if ( (s[k]<'a') || (s[k]>'z') ) return 0;
    }
    }


    if (s[ind3] == 'i' && s[ind3+1] == 'l') return 1;
    else return 0;
}
