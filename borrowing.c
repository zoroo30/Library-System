#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include"member.h"
#include"book_action.h"
#include"validation.h"
book book_array[3];
borrow borrow_array[2];
member member_array[2];
int bk=3,brw=2,mm=2;
bool borrowing_info(){

    char temp_return[11],temp_due[11];
    int index_book=search_ISBN(borrow_array[0].whatBorrow.ISBN);
    int index_member=search_ID(borrow_array[0].whoBorrow.ID);
    scanf("%d",&(borrow_array[0].whoBorrow.ID));
    getchar();
    if(index_member==-1)
        return false;
    else
    {
      if(member_array[index_member].booksBorrowed == 3) return false;/**member borrowed 3 books already**/
      else ++(member_array[index_member].booksBorrowed);
    }
    getchar();
    fgets(borrow_array[0].whatBorrow.ISBN,sizeof(borrow_array[0].whatBorrow.ISBN),stdin);
    if(index_book==-1)
    return false;
    book_array[index_book].current-=1;
    getchar();
    fgets(temp_due,sizeof(temp_due),stdin);
    if(!vali_date(temp_due)) return false;
    sscanf(temp_due,"%d/%d/%d",&(borrow_array[0].whenBack.day),&(borrow_array[0].whenBack.month),&borrow_array[0].whenBack.year);
    getchar();
    fgets(temp_return,sizeof(temp_return),stdin);
    //if((temp_return)!=NULL)//user input wasn't null......problem......
    //{
        if(!vali_date(temp_return)) return false;
        sscanf(temp_return,"%d/%d/%d",&(borrow_array[0].whenReturn.day),&(borrow_array[0].whenReturn.month),&borrow_array[0].whenReturn.year);
        return true;
    //}

}
void save_today(){
    time_t curtime;
    time(&curtime);
    struct tm *info = localtime( &curtime );
    char buffer[12];
    strftime(buffer,80,"%d/%m/%Y", info);
    sscanf(buffer,"%d/%d/%d",&(borrow_array[0].whenBorrow.day),&(borrow_array[0].whenBorrow.month),&(borrow_array[0].whenBorrow.year));
    return;
}
void return_book(char ISBN[],char date[])
{
    int index=search_ISBN(ISBN);
    borrow_array[index].whatBorrow.current+=1;
    int x=sscanf(date,"%d/%d/%d",&(borrow_array[index].whenReturn.day),&(borrow_array[index].whenReturn.month),&borrow_array[index].whenReturn.year);
    if(x!=3) sscanf(date,"%d-%d-%d",&(borrow_array[index].whenReturn.day),&(borrow_array[index].whenReturn.month),&borrow_array[index].whenReturn.year);
    return;
}
void remove_member(int ID){
int index=search_ID(ID);
int num_book=member_array[index].booksBorrowed;
if(num_book!=0) {printf("you can't leave our system without returning the %d books borrowed\n",num_book); return;}
else {
    int start=index;
    while(start<mm/*num members in system*/){
        member_array[start]=member_array[start+1];
        start ++;
    }
    mm--;
    return;
}}
