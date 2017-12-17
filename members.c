#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "member.h"
#include "book_action.h"
#include"validation.h"
#include"borrow.h"

book book_array[50];
member member_array[50];
borrow borrow_array[50];
/**int bk=0;
int mm=0;
int rw=0;**/
int search_ID(int ID)
{
    int j=0;
    while(member_array[j].ID!=ID && j<2)
    {
        j++;
    }
    if(member_array[j].ID!=ID) return -1;
    else return j;

}
void registeration(void)
{

    //when register auto-initialize numOfBooksBorrowed to zero
    fgets(member_array[mm].name,sizeof(member_array[mm].name),stdin);
    scanf("%d",&(member_array[mm].ID));
    scanf("%d",&(member_array[mm].address.buildNum));
    fgets(member_array[mm].address.city,sizeof(member_array[mm].address.city),stdin);
    fgets(member_array[mm].address.street,sizeof(member_array[mm].address.street),stdin);
    scanf("%d%d",&(member_array[mm].mobile),&(member_array[mm].age));
    fgets(member_array[mm].email.name,sizeof(member_array[mm].email.name),stdin);
    fgets(member_array[mm].email.domain,sizeof(member_array[mm].email.domain),stdin);
    member_array[mm].booksBorrowed=0;
    mm++;
    return ;

}
