#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
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

/*
int check_email(char buffer[])
{
    int c1;
    char name[100];
    char domain[100];
    int count=0, special_count = 0, counter = 0;

    while(buffer[counter]!='\0')
    {
        if(!((buffer[counter]>='a' && buffer[counter]<='z') || (buffer[counter]>='A' && buffer[counter]<='Z')) && !(buffer[counter]>='0' && buffer[counter]<='9'))
            special_count++;

        counter++;
    }

    c1 = sscanf(buffer,"%[^@]@%[^.].com",name,domain);

    if(c1 == 2)
    {
        if( isalpha(name[0]) || isalpha(domain[0]) || special_count>)
            return 1;
    }
    addError("Enter a valid email address","");
    return 0;

    //int isEmail = Regax.IsMatch(emailString, @"\A(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?)\Z", RegexOptions.IgnoreCase);
    //return isEmail;
}*/

int isdotdash ( const char c )
{
  switch ( c )
  {
    case '.':
    case '-':
      return 1;
  }
  return 0;
} // isdotdash

char *to_ascii(const char *inputstring) {

   // allocate the maximum needed to store the ascii represention:
   char *output = malloc(sizeof(char) * (strlen(inputstring) * 4 + 1));
   char *output_end = output;

   if (!output) // allocation failed! omg!
      exit(EXIT_FAILURE);

   *output_end = '\0';
   for (; *inputstring; ++inputstring) {
      output_end += sprintf(output_end, "%u ", *inputstring);
      //assert(output_end == '\0');
   }

  return output;
}


int validateEmail(char *EM_Addr)
{
  int count = 0;
int i = 0;
char conv_buf[100];
char *c, *domain;
char *special_chars = "()<>@,;:\"[]";

/* The input is in EBCDIC so convert to ASCII first */
strcpy(conv_buf,EM_Addr);
toascii(conv_buf);
/* convert the special chars to ASCII */
toascii(special_chars);

for(c = conv_buf; *c; c++) {
   /* if '"' and beginning or previous is a '.' or '"' */
   if (*c == 34 && (c == conv_buf || *(c - 1) == 46 || *(c - 1) == 34)) {
      while (*++c) {
         /* if '"' break, End of name */
         if (*c == 34)
            break;
         /* if '' and ' ' */
         if (*c == 92 && (*++c == 32))
            continue;
         /* if not between ' ' & '~' */
         if (*c <= 32 || *c > 127)
            return 0;
         }
      /* if no more characters error */
      if (!*c++)
         return 0;
      /* found '@' */
      if (*c == 64)
         break;
      /* '.' required */
      if (*c != 46)
         return 0;
      continue;
      }
   if (*c == 64) {
      break;
      }
   /* make sure between ' ' && '~' */
   if (*c <= 32 || *c > 127) {
      return 0;
      }
   /* check special chars */
   if (strchr(special_chars, *c)) {
      return 0;
      }
   } /* end of for loop */
/* found '@' */
/* if at beginning or previous = '.' */
if (c == conv_buf || *(c - 1) == 46)
   return 0;
/* next we validate the domain portion */
/* if the next character is NULL */
/* need domain ! */
if (!*(domain = ++c))
   return 0;
do {
   /* if '.' */
   if (*c == 46) {
      /* if beginning or previous = '.' */
      if (c == domain || *(c - 1) == 46)
         return 0;
      /* count '.' need at least 1 */
      count++;
      }
   /* make sure between ' ' and '~' */
   if (*c <= 32 || *c >= 127)
      return 0;
   if (strchr(special_chars, *c))
      return 0;
   } while (*++c); /* while valid char */
return (count >= 1); /* return true if more than 1 '.' */
}


int validateMobile(char buffer[]){
    int c1;
    long mobile=0;
    int count=0;
    c1 = sscanf(buffer,"0%ld",&mobile);

    if(c1 == 1)
    {
        count = floor(log10(mobile)) + 1;
        int first_digit = mobile/(int)pow(10,count-1);
        if(count == 10)
            if(first_digit == 1)
                return 1;
    }
    addError("Enter a valid mobile number","");
    return 0;
}

void display_error(char message[]) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
    printf("\n  %s  ",message);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return;
}

void display_info(char title[], char message[]) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
    printf("\n%30s",title);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf(" %s",message);
    return;
}

void display_date_info(char title[], int d, int m, int y) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
    printf("\n%30s",title);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    if(d != 0)
        printf(" %02d/%02d/%04d",d,m,y);
    else
        printf(" -");
    return;
}

void display_int_info(char title[], int integer) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
    printf("\n%30s",title);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf(" %d",integer);
    return;
}
