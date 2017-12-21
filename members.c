#include "members.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "validation.h"

/*
 = {{"Mohamed",1,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",2,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",3,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",4,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",5,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",6,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"},
                            {"Mohamed",7,{1,"street","city"},"1097664886",11,"mohamed@yahoo.com"}}
                            */

member member_array[100];
int members_number = 0;
int member_displayed[100];
int memeber_displayed_number = 0;

int current_member_index = -1, member_edit_success = 0, member_delete_success = -1;


int insert_member(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(members_number != 100 || index != -1) {
        member inserted;
        char buffer[13];
        char email_holder[100];

        inserted.ID = members_number;
        input("\nEnter member name (required) [100] : ",inserted.name,100,"Name",1);

        input("Enter city [100] : ",inserted.address.city,100,"address",0);
        input("Enter street [100] : ",inserted.address.street,100,"street",0);

        input("Enter building number [100] : ",buffer,11,"building number",0);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid integer for the building number","");
                    case 1:
                        sscanf(buffer,"%d\n",&inserted.address.buildNum);
                        if(inserted.address.buildNum < 0){
                            addError("Building number can not be a negative value","");
                        }
                    default:
                        break;
                }
            }
        }
        else
        {
            inserted.address.buildNum = member_array[index].address.buildNum;
        }

        input("Enter member age : ",buffer,11,"Age",0);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid integer for the age","");
                    case 1:
                        sscanf(buffer,"%d\n",&inserted.age);
                        if(inserted.age < 0){
                            addError("Age can not be a negative value","");
                        }
                    default:
                        break;
                }
            }
        }
        else
        {
            inserted.age = member_array[index].age;
        }

        input("Enter member mobile number : 01",buffer,11,"mobile",0);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid mobile number","");
                    case 1:
                        sscanf(buffer,"%l\n",&inserted.mobile);
                        if((int)inserted.mobile < 0){
                            addError("Enter a valid mobile number","");
                        }
                    default:
                        break;
                }
            }
        }
        else
        {
            strcpy(inserted.mobile,member_array[index].mobile);
        }


        input("Enter member email [100] : ",inserted.email,30,"email",0);

        if(errors_number == 0) {
            printSuccess((index == -1) ? "The member data has been successfully added!" : "The member data has been successfully updated!");
            if(index == -1)
            {
                member_array[members_number] = inserted;
                //printf("%s  -  %s  -  %s  -  %s  -  %s  -  %d  -  %d  -  %s", member_array[i].title, member_array[i].author, member_array[i].publisher, member_array[i].ISBN, buffer, member_array[i].copies, member_array[i].current, member_array[i].category);
                members_number++;
            } else {
                member_edit_success = 1;
                if(strcmp(inserted.name,".") != 0)
                    strcpy(member_array[index].name,inserted.name);
                if(strcmp(inserted.address.street,".") != 0)
                    strcpy(member_array[index].address.street,inserted.address.street);
                if(strcmp(inserted.address.city,".") != 0)
                    strcpy(member_array[index].address.street,inserted.address.street);

                member_array[index].address.buildNum = inserted.address.buildNum;
                member_array[index].age = inserted.age;

                if(strcmp(inserted.mobile,".") != 0)
                    strcpy(member_array[index].mobile,inserted.mobile);


                if(strcmp(inserted.email,".") != 0)
                    strcpy(member_array[index].email,inserted.email);
            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 members",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_member_index = -1;
    return 0;
}



/*
int display_members(member members[100]) {
    if(i != 0) {
        int y;
        members_displayed_number = 0;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-30s   %-15s   %-15s   %-18s   %-10s   %-10s   %-15s\n","
               member ISBN","
               member TITLE","AUTHOR","PUBLISHER","PUBLICATION DATE","COPIES","AVALIBLE","CATEGORY");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(y = 0; y<i; y++) {
            add_
            member_record(y);
            display_

            member_record(


                          members,y);
        }
    }

    if(member_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(member_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    member_delete_success = -1;

    return i;
}

void add_

member_record(int y) {
    members_displayed[
    members_displayed_number] = y;

    members_displayed_number++;
}

void display_member_record(
                           member
                           members[100], int y) {
    if(member_edit_success == 1 && current_
       member_index == y)
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 47);

    if(members[y].date.day != 0)
        //%-30.30s   %-30.30s   %-15.15s   %-15.15s
        printf("%-30s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-13.13s%-2.2s   %02d/%02d/%04d           %-10d   %-10d   %-13.13s%-2.2s\n",members[y].ISBN,members[y].title,(strlen( members[y].title)>28) ? ".." : "",members[y].author,(strlen(members[y].author)>13) ? ".." : "",members[y].publisher,(strlen(members[y].publisher)>13) ? ".." : "",members[y].date.day,members[y].date.month,members[y].date.year,members[y].copies,members[y].current, members[y].category,(strlen(members[y].category)>13) ? ".." : "");
    else
        printf("%-30s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-13.13s%-2.2s   -                    %-10d   %-10d   %-13.13s%-2.2s\n",members[y].ISBN,members[y].title,(strlen(members[y].title)>28) ? ".." : "",members[y].author,(strlen(members[y].author)>13) ? ".." : "",members[y].publisher,(strlen(members[y].publisher)>13) ? ".." : "", members[y].copies, members[y].current, members[y].category,(strlen(members[y].category)>13) ? ".." : "");

    if(member_edit_success == 1 && current_member_index == y){
        member_edit_success = 0;
        current_member_index = -1;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

int search_members(member members[100]){
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, found = 1,previous_members_displayed_number = members_displayed_number, number, is_date, dd,mm,yy;
    members_displayed_number = 0;
    input("Enter search term : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -1;}
    if(strcmp(search_txt,"./edit") == 0 && current_member_index != -1) {return -2;}
    if(strcmp(search_txt,"./copies") == 0 && current_member_index != -1) {return -3;}
    if(strcmp(search_txt,"./delete") == 0 && current_member_index != -1) {return -4;}
    int search_again = checkSearchText(search_txt);
    clrscr();
    operation_header(0, "Search members");
    if(strcmp(search_txt,"-") == 0)
    {
        display_members(members);
        return;
    }

    for(y = 0; y<i; y++)
    {
        if(search_again && previous_members_displayed_number != 0 && previous_members_displayed_number != 1)
        {
            found = 0;
            for(z = 0; z<previous_members_displayed_number; z++)
            {
                if(members_displayed[z] == y)
                {
                    found = 1;
                    break;
                }
            }
        }
        errors_number = 0;
        if(found == 1){
            if(strcmpi(members[y].ISBN,search_txt) == 0 || stristr(members[y].title,search_txt) != NULL || stristr(members[y].author,search_txt) != NULL || stristr(members[y].publisher,search_txt) != NULL || stristr(members[y].category,search_txt) != NULL)
            {
                add_member_record(y);
            }
            else if(validateInteger(search_txt))
            {
                sscanf(search_txt,"%d\n",&number);
                if(members[y].copies == number || members[y].current == number || ((members[y].date.day == number || members[y].date.month == number || members[y].date.year == number) && number != 0))
                    add_member_record(y);
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
                if(members[y].date.day == dd && members[y].date.month == mm && members[y].date.year == yy)
                    add_member_record(y);
            }
        }
    }
    if(members_displayed_number == 1) {
        display_member(members_displayed[0]);
    }
    else if(members_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-30s   %-15s   %-15s   %-18s   %-10s   %-10s   %-15s\n","member ISBN","member TITLE","AUTHOR","PUBLISHER","PUBLICATION DATE","COPIES","AVALIBLE","CATEGORY");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(z=0;z<members_displayed_number;z++)
            display_member_record(members,members_displayed[z]);
    }

    if(member_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(member_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    member_delete_success = -1;

    printf("\nYou searched for : %s ", search_txt);

    return books_displayed_number;
}

//void replace_records()
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

void display_member(int index)
{
    display_info("member ISBN : ",member_array[index].ISBN);
    display_info("member TITLE : ",member_array[index].title);
    display_info("AUTHOR : ",member_array[index].author);
    display_info("PUBLISHER : ",member_array[index].publisher);
    display_date_info("PUBLICATION DATE : ",member_array[index].date.day, member_array[index].date.month, member_array[index].date.year);
    display_int_info("COPIES : ",member_array[index].copies);
    display_int_info("AVALIBLE : ",member_array[index].current);
    display_info("CATEGORY : ",member_array[index].category);
    printf("\n");
    current_
    member_index = index;
    return;
}

void search_title(char search[])
{
    int j=0;
    while(strstr(member_array[j].title,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(member_array[j].title,search)== NULL) printf("\nOur library doesn't have this member\n");
    else display_member(j);

}

int search_ISBN(member members[100], char subtitle[])
{
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, previous_members_displayed_number = members_displayed_number;
    members_displayed_number = 0;
    input("Enter member ISBN : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -2;}
    else if(strcmp(search_txt,"./search") == 0) {return -3;}
    clrscr();
    operation_header(0, subtitle);

    for(y = 0; y<i; y++)
    {
        if(strcmpi(members[y].ISBN,search_txt) == 0)
        {
            add_member_record(y);
        }
    }

    if(members_displayed_number == 1) {
        display_member(members_displayed[0]);
    } else if (members_displayed_number != 0){
        display_info("the same ISBN is used for more than 1 member","");
    }

    printf("\nYou searched for : %s ", search_txt);

    return members_displayed_number;
}

void search_author(char search[])
{
    int j=0;
    while(strstr(member_array[j].author,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(member_array[j].author,search)== NULL) printf("\nOur library doesn't have this member\n");
    else display_member(j);

}
void search_publisher(char search[])
{
    int j=0;
    while(strstr(member_array[j].publisher,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(member_array[j].publisher,search)== NULL) printf("\nOur library doesn't have this member\n");
    else display_member(j);

}
void add_copy(char ISBN[],int* num_copies)
{
    if(search_ISBN(ISBN)!=-1)
    {
        *num_copies+=1;
    }
    else printf("\nThis member doesn't exist");
}
void delete_member(int index)
{
    int j=index;
    if(index!=-1)
    {
        while(j<i)
        {
          member_array[j]=member_array[j+1];
          j++;
        }
        i--;
        current_member_index = -1;
        member_delete_success = 1;
    }
    else printf("\nThis member doesn't exist");
    return;
}

int check_ISBN(char ISBN_holder[]){
    int y;
    for(y = 0; y<i; y++){
        if(strcmpi(member_array[y].ISBN,ISBN_holder) == 0)
        {
            addError("This ISBN is already used for another member!","");
            return 0;
        }
    }
    return 1;
}
*/

