#include <stdio.h>
#include <stdlib.h>
#include "navigation.h"
#include <string.h>

void lower_string(char *string)
{
    int i;
    for(i = 0; string[i]; i++){
      string[i] = tolower(string[i]);
    }
    return;
}

int main()
{
    load_menu(-1,"");

    /*while(1) {
        insert_member(-1);
    }*/

    /*char *str;
    strcpy(str,"MOHAMED");

    lower_string(str);
    printf("%s",str);

    char Name[100];
    char search[100];

    printf("Enter your string : ");
    fgets(Name,100,stdin);

    while(1){
        printf("Enter search text : ");
        fgets(search,100,stdin);

        size_t n = strlen(search);
        if (n > 0 && search[n-1] == '\n') {
            search[n-1] = 0;
        }

        if(stristr( Name, search) != NULL)
            printf("Found!");
        else
            printf("Not found!");
        printf("\n");
    }*/

    return 0;
}

