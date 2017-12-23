#include "borrowing.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "validation.h"
#include "members.h"

/*
typedef struct
{
    char book_isbn[10];
    int member_id;
    dateStruct date_issued;
    dateStruct date_should_return;
    dateStruct date_returned;
} borrow;

*/

borrow borrow_array[100] = {{"23213-123",1,{10,2,2005},10,{10,2,2005},{0,0,0}},
                            {"23213-12123",1,{10,2,2005},10,{10,2,2005},{0,0,0}},
                            {"23213-12123",2,{10,2,2005},10,{10,2,2005},{0,0,0}}};
static int i=3;

int borrows_displayed[100];
int borrows_displayed_number = 0;

int current_borrow_index = -1, borrow_edit_success = 0, borrow_delete_success = -1;


int insert_borrow(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(i != 100 || index != -1) {
        borrow inserted;
        char buffer[11];
        char ISBN_holder[30];
        char previous_ISBN[30];
        int previous_day = 0;
        char term;

        if(index != -1){
            strcpy(previous_ISBN,borrow_array[index].book_isbn);
            previous_day = borrow_array[index].date_returned.day;
        }
        printf("\nenter (./now) for today's date\n");
        input("\nEnter borrow ISBN (required) [30] : ",ISBN_holder,30,"ISBN",1);
        int is_exist = !check_ISBN(ISBN_holder);
        errors_number = 0;
        if(!(strcmp(ISBN_holder,".") == 0 && index != -1) && is_exist && copies_left(ISBN_holder) > 0)
            strcpy(inserted.book_isbn,ISBN_holder);
        else if(strcmp(ISBN_holder,"-") == 0)
            addError("ISBN field cannot be left empty","");
        else if(!(strcmp(ISBN_holder,".") == 0 && index != -1) && !is_exist)
            addError("There is no book with this ISBN","");

        input("Enter number member ID (required) : ",buffer,11,"Member ID",1);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                if(validateInteger(buffer) != 0){
                    sscanf(buffer,"%d\n",&inserted.member_id);
                    if(!check_member_ID(inserted.member_id)){
                        addError("There is no user with this ID","");
                    } else if(member_books_number(inserted.member_id,index) == 3)
                        addError("This member has borrowed 3 books already","");
                } else {
                    addError("There is no user with this ID", "");
                }
            }
        }
        else
        {
            inserted.member_id = borrow_array[index].member_id;
        }

        input("Enter borrowing date dd/mm/yyyy or dd-mm-yyyy (required) : ",buffer,11,"Borrowing date",1);
        if(strcmpi(buffer,"./now") != 0) {
            if (!(index != -1 && strcmp(buffer,".") == 0))
            {
                if(strcmp(buffer,"-") != 0){
                    switch(validateDate(buffer)){
                        case 1:
                            sscanf(buffer,"%d/%d/%d",&inserted.date_issued.day,&inserted.date_issued.month,&inserted.date_issued.year);
                        case 2:
                            sscanf(buffer,"%d-%d-%d",&inserted.date_issued.day,&inserted.date_issued.month,&inserted.date_issued.year);
                        default:
                            break;
                    }
                } else {
                        sscanf("0/0/0","%d/%d/%d",&inserted.date_issued.day,&inserted.date_issued.month,&inserted.date_issued.year);
                }
            }
            else
            {
                inserted.date_issued = borrow_array[index].date_issued;
            }
        }
        else
        {
            today(buffer);
            sscanf(buffer,"%d/%d/%d",&inserted.date_issued.day,&inserted.date_issued.month,&inserted.date_issued.year);
        }

        input("Days until return date (required) : ",buffer,11,"Days",1);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid integer for the days number","");
                    case 1:
                        sscanf(buffer,"%d\n",&inserted.skip_days);
                        if(inserted.skip_days < 0){
                            addError("days number can not be a negative value","");
                        }else
                        {
                            add_days(buffer,inserted.skip_days,inserted.date_issued.day,inserted.date_issued.month,inserted.date_issued.year);
                            sscanf(buffer,"%d/%d/%d",&inserted.date_should_return.day,&inserted.date_should_return.month,&inserted.date_should_return.year);
                        }
                    default:
                        break;
                }
            }
        }
        else
        {
            inserted.skip_days = borrow_array[index].skip_days;
            add_days(buffer,inserted.skip_days,inserted.date_issued.day,inserted.date_issued.month,inserted.date_issued.year);
            sscanf(buffer,"%d/%d/%d",&inserted.date_should_return.day,&inserted.date_should_return.month,&inserted.date_should_return.year);
        }

        input("Enter returning date dd/mm/yyyy or dd-mm-yyyy : ",buffer,11,"Returning date",0);
        if(strcmpi(buffer,"./now") != 0) {
            if (!(index != -1 && strcmp(buffer,".") == 0))
            {
                if(strcmp(buffer,"-") != 0){
                    switch(validateDate(buffer)){
                        case 1:
                            sscanf(buffer,"%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                        case 2:
                            sscanf(buffer,"%d-%d-%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                        default:
                            break;
                    }
                } else {
                        sscanf("0/0/0","%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                }
            }
            else
            {
                inserted.date_returned = borrow_array[index].date_returned;
            }
        }
        else
        {
            today(buffer);
            sscanf(buffer,"%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
        }

        if(inserted.date_returned.day != 0)
            if(compare_dates(inserted.date_issued,inserted.date_returned)>0)
                addError("Returning date cannot be earlier than borrowing date","");

        if(errors_number == 0) {
            printSuccess((index == -1) ? "The borrow data has been successfully added!" : "The borrow data has been successfully updated!");
            if(index == -1)
            {
                borrow_array[i] = inserted;

                if(inserted.date_returned.day == 0)
                    book_array[book_index(ISBN_holder)].current--;
                //printf("%s  -  %04d  -  %d  -  %s", borrow_array[i].book_isbn, borrow_array[i].member_id,borrow_array[i].skip_days, buffer);
                i++;
            } else {
                borrow_edit_success = 1;
                if(strcmp(ISBN_holder,".") != 0)
                    strcpy(borrow_array[index].book_isbn,inserted.book_isbn);

                borrow_array[index].member_id = inserted.member_id;
                borrow_array[index].date_issued = inserted.date_issued;
                borrow_array[index].date_should_return = inserted.date_should_return;
                borrow_array[index].date_returned = inserted.date_returned;

                if(strcmp(borrow_array[index].book_isbn,previous_ISBN) == 0){
                    if(previous_day != borrow_array[index].date_returned.day && previous_day == 0)
                        book_array[book_index(borrow_array[index].book_isbn)].current++;
                    else if(previous_day != borrow_array[index].date_returned.day && borrow_array[index].date_returned.day == 0)
                        book_array[book_index(borrow_array[index].book_isbn)].current--;
                }
                else {
                    if(previous_day != borrow_array[index].date_returned.day && previous_day == 0)
                    {
                        book_array[book_index(previous_ISBN)].current++;
                    }
                    else if(previous_day != borrow_array[index].date_returned.day && borrow_array[index].date_returned.day == 0)
                    {
                        book_array[book_index(borrow_array[index].book_isbn)].current--;
                    }
                    else if(previous_day == borrow_array[index].date_returned.day && previous_day == 0)
                    {
                        book_array[book_index(previous_ISBN)].current++;
                        book_array[book_index(borrow_array[index].book_isbn)].current--;
                    }
                }
            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 borrowing operations",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_borrow_index = -1;
    return 0;
}

int member_books_number(int member_id , int borrow_index){
    int y, books_number = 0;
    for(y = 0; y<i; y++) {
        if(borrow_array[y].member_id == member_id && y != borrow_index && borrow_array[y].date_returned.day == 0)
            books_number++;
    }
    return books_number;
}

void edit_book_isbn(char old_ISBN[],char new_ISBN[]){
    int y;
    for(y = 0; y<i; y++) {
        if(strcmpi(borrow_array[y].book_isbn,old_ISBN) == 0)
            strcpy(borrow_array[y].book_isbn,new_ISBN);
    }
    return;
}


int current_copies(int book_index, int new_copies_nubmer){
    int y = 0, borrowed_books_number = 0;
    for(y = 0; y<i; y++){
        if(strcmpi(borrow_array[y].book_isbn,book_array[book_index].ISBN) == 0 && borrow_array[y].date_returned.day == 0){
            borrowed_books_number++;
        }
    }
    return new_copies_nubmer - borrowed_books_number;
}

void today(char buffer[]){
    strcpy(buffer,"");
    time_t curtime;
    time(&curtime);
    struct tm *info = localtime( &curtime );
    strftime(buffer,80,"%d/%m/%Y", info);
    return;
}

void add_days(char buffer[], int skip, int d, int m, int y){
    strcpy(buffer,"");
    // Represent the date as struct tm.
    // The subtractions are necessary for historical reasons.
    struct tm  t = { 0 };
    t.tm_mday = d;
    t.tm_mon = m-1;
    t.tm_year = y-1900;

    // Add 'skip' days to the date.
    t.tm_mday += skip;
    mktime(&t);

    // Print the date in ISO-8601 format.
    strftime(buffer, 30, "%d/%m/%Y", &t);
    return;
}


int edit_return_date(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(i != 100 || index != -1) {
        borrow inserted;
        char buffer[11];
        int previous_day = 0;
        if(index != -1){
            previous_day = borrow_array[index].date_returned.day;
        }

        input("Enter returning date dd/mm/yyyy or dd-mm-yyyy : ",buffer,11,"Returning date",0);
        if(strcmpi(buffer,"./now") != 0) {
            if (!(index != -1 && strcmp(buffer,".") == 0))
            {
                if(strcmp(buffer,"-") != 0){
                    switch(validateDate(buffer)){
                        case 1:
                            sscanf(buffer,"%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                        case 2:
                            sscanf(buffer,"%d-%d-%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                        default:
                            break;
                    }
                } else {
                        sscanf("0/0/0","%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
                }
            }
            else
            {
                inserted.date_returned = borrow_array[index].date_returned;
            }
        }
        else
        {
            today(buffer);
            sscanf(buffer,"%d/%d/%d",&inserted.date_returned.day,&inserted.date_returned.month,&inserted.date_returned.year);
        }

        if(inserted.date_returned.day != 0)
            if(compare_dates(borrow_array[index].date_issued,inserted.date_returned)>0)
                addError("Returning date cannot be earlier than borrowing date","");


        if(errors_number == 0) {
            printSuccess((index == -1) ? "The borrow data has been successfully added!" : "The borrow data has been successfully updated!");
            if(index == -1)
            {
                borrow_array[i] = inserted;
                //printf("%s  -  %s  -  %s  -  %s  -  %s  -  %d  -  %d  -  %s", borrow_array[i].title, borrow_array[i].author, borrow_array[i].publisher, borrow_array[i].ISBN, buffer, borrow_array[i].copies, borrow_array[i].current, borrow_array[i].category);
                i++;
            } else {
                borrow_edit_success = 1;

                borrow_array[index].date_returned = inserted.date_returned;

                if(previous_day != borrow_array[index].date_returned.day && previous_day == 0)
                    book_array[book_index(borrow_array[index].book_isbn)].current++;
                else if(previous_day != borrow_array[index].date_returned.day && borrow_array[index].date_returned.day == 0)
                    book_array[book_index(borrow_array[index].book_isbn)].current--;

            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 borrows",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_borrow_index = -1;
    return 0;
}

int display_borrows(borrow borrows[100]) {
    if(i != 0) {
        int y;
        borrows_displayed_number = 0;
        for(y = 0; y<i; y++) {
            add_borrow_record(y);
        }
    }

    int z;

    if(borrows_displayed_number == 1) {
        display_borrow(borrows_displayed[0]);
    }
    else if(borrows_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-15s   %-7s   %-15s   %-15s   %-15s   %-15s\n","BOOK ISBN","BOOK TITLE","MEMBER ID","MEMBER NAME","BORROWING DATE","DATE DUE TO RETURN","DATE RETURNED");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(z=0;z<borrows_displayed_number;z++)
            display_borrow_record(borrows,borrows_displayed[z]);
    }

    if(borrow_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(borrow_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    borrow_delete_success = -1;

    return i;
}
void add_borrow_record(int y) {
    borrows_displayed[borrows_displayed_number] = y;
    borrows_displayed_number++;
}

void display_borrow_record(borrow borrows[100], int y) {
    if(borrow_edit_success == 1 && current_borrow_index == y)
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 47);

    char name[55];
    get_name(name,member_index(borrows[y].member_id),member_array);

    if(borrows[y].date_returned.day != 0)
        //%-30s   %-15s   %-7s   %-15s   %-10s   %-10s   %-10s
        printf("%-30s   %-13.13s%-2.2s   %-04d        %-13.13s%-2.2s   %02d/%02d/%04d        %02d/%02d/%04d           %02d/%02d/%04d\n",
               borrows[y].book_isbn,book_array[book_index(borrows[y].book_isbn)].title,(strlen(book_array[book_index(borrows[y].book_isbn)].title)>13) ? ".." : "",
               borrows[y].member_id,name,(strlen(name)>13) ? ".." : "",
               borrows[y].date_issued.day, borrows[y].date_issued.month, borrows[y].date_issued.year,
               borrows[y].date_should_return.day, borrows[y].date_should_return.month, borrows[y].date_should_return.year,
               borrows[y].date_returned.day, borrows[y].date_returned.month, borrows[y].date_returned.year);
    else
        printf("%-30s   %-13.13s%-2.2s   %-04d        %-13.13s%-2.2s   %02d/%02d/%04d        %02d/%02d/%04d           -         \n",
               borrows[y].book_isbn,book_array[book_index(borrows[y].book_isbn)].title,(strlen(book_array[book_index(borrows[y].book_isbn)].title)>13) ? ".." : "",
               borrows[y].member_id,name,(strlen(name)>13) ? ".." : "",
               borrows[y].date_issued.day, borrows[y].date_issued.month, borrows[y].date_issued.year,
               borrows[y].date_should_return.day, borrows[y].date_should_return.month, borrows[y].date_should_return.year);

    if(borrow_edit_success == 1 && current_borrow_index == y){
        borrow_edit_success = 0;
        current_borrow_index = -1;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}


int search_borrows(borrow borrows[100]){
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, found = 1,previous_borrows_displayed_number = borrows_displayed_number, number, is_date, dd,mm,yy;
    borrows_displayed_number = 0;
    input("Enter search term : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -1;}
    if(strcmp(search_txt,"./edit") == 0 && current_borrow_index != -1) {return -2;}
    if(strcmp(search_txt,"./return") == 0 && current_borrow_index != -1) {return -3;}
    if(strcmp(search_txt,"./delete") == 0 && current_borrow_index != -1) {return -4;}
    int search_again = checkSearchText(search_txt);
    clrscr();
    operation_header(9, "Advanced search (edit - delete)");
    if(strcmp(search_txt,"-") == 0)
    {
        display_borrows(borrows);
        return;
    }

    for(y = 0; y<i; y++)
    {

        char name[55];
        get_name(name,member_index(borrows[y].member_id),member_array);

        if(search_again && previous_borrows_displayed_number != 0 && previous_borrows_displayed_number != 1)
        {
            found = 0;
            for(z = 0; z<previous_borrows_displayed_number; z++)
            {
                if(borrows_displayed[z] == y)
                {
                    found = 1;
                    break;
                }
            }
        }
        errors_number = 0;
        if(found == 1){
            if(strcmpi(borrows[y].book_isbn,search_txt) == 0 || stristr(book_array[book_index(borrows[y].book_isbn)].title,search_txt) != NULL || stristr(name,search_txt) != NULL)
            {
                add_borrow_record(y);
            }
            else if(validateInteger(search_txt))
            {
                sscanf(search_txt,"%d\n",&number);
                if(borrows[y].member_id == number || (((borrows[y].date_issued.day == number || borrows[y].date_issued.month == number || borrows[y].date_issued.year == number) || (borrows[y].date_should_return.day == number || borrows[y].date_should_return.month == number || borrows[y].date_should_return.year == number) || (borrows[y].date_returned.day == number || borrows[y].date_returned.month == number || borrows[y].date_returned.year == number)) && number != 0))
                    add_borrow_record(y);
            }
            else if(is_date = validateDate(search_txt))
            {
                switch(is_date){
                    case 1:
                        sscanf(search_txt,"%d/%d/%d",&dd,&mm,&yy);
                    case 2:
                        sscanf(search_txt,"%d-%d-%d",&dd,&mm,&yy);
                    default:
                        break;
                }
                if((borrows[y].date_issued.day == number && borrows[y].date_issued.month == number && borrows[y].date_issued.year == number)
                 || (borrows[y].date_should_return.day == number && borrows[y].date_should_return.month == number && borrows[y].date_should_return.year == number)
                 || (borrows[y].date_returned.day == number && borrows[y].date_returned.month == number && borrows[y].date_returned.year == number))
                    add_borrow_record(y);
            }
        }
    }
    if(borrows_displayed_number == 1) {
        display_borrow(borrows_displayed[0]);
    }
    else if(borrows_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-15s   %-7s   %-15s   %-15s   %-15s   %-15s\n","BOOK ISBN","BOOK TITLE","MEMBER ID","MEMBER NAME","BORROWING DATE","DATE DUE TO RETURN","DATE RETURNED");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(z=0;z<borrows_displayed_number;z++)
            display_borrow_record(borrows,borrows_displayed[z]);
    }

    if(borrow_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(borrow_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    borrow_delete_success = -1;

    printf("\nYou searched for : %s ", search_txt);

    return borrows_displayed_number;
}

//void replace_records()


void display_borrow(int index)
{
    char name[55];
    get_name(name,member_index(borrow_array[index].member_id),member_array);

    display_info("BOOK ISBN : ",borrow_array[index].book_isbn);
    display_info("BOOK TITLE : ",book_array[book_index(borrow_array[index].book_isbn)].title);
    display_int_info("MEMBER ID : ",borrow_array[index].member_id);
    display_info("MEMBER NAME : ",name);
    display_date_info("DATE ISSUED : ",borrow_array[index].date_issued.day, borrow_array[index].date_issued.month, borrow_array[index].date_issued.year);
    display_date_info("DATE DUE TO RETURN : ",borrow_array[index].date_should_return.day, borrow_array[index].date_should_return.month, borrow_array[index].date_should_return.year);
    display_date_info("DATE RETURNED : ",borrow_array[index].date_returned.day, borrow_array[index].date_returned.month, borrow_array[index].date_returned.year);
    printf("\n");
    current_borrow_index = index;
    return;
}

void delete_borrow(int index)
{
    int j=index;

    if(borrow_array[index].date_returned.day == 0)
        book_array[book_index(borrow_array[index].book_isbn)].current++;

    if(index!=-1)
    {
        while(j<i)
        {
            borrow_array[j]=borrow_array[j+1];
            j++;
        }
        i--;
        current_borrow_index = -1;
        borrow_delete_success = 1;
    }
    else printf("\nThis borrow doesn't exist");
    return;
}


/*book book_array[3];
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
      if(member_array[index_member].booksBorrowed == 3) return false;//member borrowed 3 books already
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
    while(start<mm){//num members in system
        member_array[start]=member_array[start+1];
        start ++;
    }
    mm--;
    return;
}}
*/
