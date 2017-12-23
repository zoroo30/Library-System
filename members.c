#include "members.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "validation.h"



member member_array[100];

static int i = 0;
static int member_next_id = 0;
int members_displayed[100];
int members_displayed_number = 0;

int current_member_index = -1, member_edit_success = 0, member_delete_success = -1;

void initialize_members()
{
    i=read_members(member_array,"members.dat");
    if(i != 0)
        i = i-1;
    member_next_id = maxID() + 1;

}
void save_members()
{
    write_members(member_array,i,"members.dat");
}
int maxID()
{
    int y,max = 0;
    if(i != 0)
        max = member_array[0].ID;
    for(y = 1; y<i; y++){
        if(member_array[y].ID>max){
            max = member_array[y].ID;
        }
    }
    return max;
}
int insert_member(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(i != 100 || index != -1) {
        member inserted;
        char buffer[13];
        char email_holder[100];
        char mobile_holder[13];

        if(index == -1){
            inserted.ID = member_next_id;
            inserted.booksBorrowed = 0;
            printf("\nMember ID : %04d", member_next_id);
        }
        else{
            inserted.ID = member_array[index].ID;
            printf("\nMember ID : %04d", member_array[index].ID);
        }

        input("\nEnter member first name (required) [25] : ",inserted.first_name,25,"First name",1);
        input("Enter member last name (required) [25] : ",inserted.last_name,25,"Last name",1);

        input("Enter city [100] : ",inserted.address.city,100,"City",0);
        input("Enter street [100] : ",inserted.address.street,100,"Street",0);

        input("Enter building number [100] : ",buffer,11,"Building number",0);
        inserted.address.buildNum = 0;
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
        inserted.age = 0;
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

        input("Enter member mobile number (01XXXXXXXXX) : ",mobile_holder,12,"mobile",0);
        if(strcmp(mobile_holder,"-") == 0)
            strcpy(inserted.mobile,"-");
        else if(!(strcmp(mobile_holder,".") == 0 && index != -1) && validateMobile(mobile_holder))
            strcpy(inserted.mobile,mobile_holder);


        input("Enter member email : ",email_holder,100,"email",0);
        if(strcmp(email_holder,"-") == 0)
            strcpy(inserted.email,"-");
        else if(!(strcmp(email_holder,".") == 0 && index != -1) && check_email(email_holder,index))
            if(validateEmail(email_holder))
                strcpy(inserted.email,email_holder);
            else
                addError("Enter a valid email address","");


        if(errors_number == 0) {
            printSuccess((index == -1) ? "The member data has been successfully added!" : "The member data has been successfully updated!");
            if(index == -1)
            {
                member_array[i] = inserted;
                //printf("%04d  -  %s %s  -  (%d  -  %s  -  %s)  -  %s  -  %s  -  %d",member_array[i].ID, member_array[i].first_name, member_array[i].last_name, member_array[i].address.buildNum,member_array[i].address.street, member_array[i].address.city, member_array[i].email, member_array[i].mobile, member_array[i].age);
                i++;
                member_next_id++;
            } else {
                member_edit_success = 1;
                if(strcmp(inserted.first_name,".") != 0)
                    strcpy(member_array[index].first_name,inserted.first_name);
                if(strcmp(inserted.last_name,".") != 0)
                    strcpy(member_array[index].last_name,inserted.last_name);
                if(strcmp(inserted.address.street,".") != 0)
                    strcpy(member_array[index].address.street,inserted.address.street);
                if(strcmp(inserted.address.city,".") != 0)
                    strcpy(member_array[index].address.city,inserted.address.city);

                member_array[index].address.buildNum = inserted.address.buildNum;
                member_array[index].age = inserted.age;

                if(strcmp(mobile_holder,".") != 0)
                    strcpy(member_array[index].mobile,inserted.mobile);

                if(strcmp(email_holder,".") != 0)
                    strcpy(member_array[index].email,inserted.email);
            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 members",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_member_index = -1;
    return 0;
}

int display_members(member members[100]) {
    if(i != 0) {
        int y;
        members_displayed_number = 0;
        for(y = 0; y<i; y++) {
            add_member_record(y);
        }
    }

    int z;

    if(members_displayed_number == 1) {
        display_member(members_displayed[0]);
    }
    else if(members_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-7s   %-30s   %-30s   %-15s   %-30s   %-10s\n","ID","NAME","ADDRESS","MOBILE","EMAIL","AGE");
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

    return i;
}

void add_member_record(int y) {
    members_displayed[members_displayed_number] = y;
    members_displayed_number++;
}

void display_member_record(member members[100], int y) {
    if(member_edit_success == 1 && current_member_index == y)
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 47);
    //printf("\n%-10s   %-51s   %-50s   %-15s   %-30s   %-10s\n","ID","NAME","ADDRESS","MOBILE","EMAIL","AGE");

    char address[200];
    char name[55];

    get_address(address,y,members);
    get_name(name,y,members);

    if(members[y].age != 0)
        //%-30.30s   %-30.30s   %-15.15s   %-15.15s
        printf("%04d      %-28.28s%-2.2s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-28.28s%-2.2s   %-10d\n",
               members[y].ID,name,(strlen(name)>28) ? ".." : "",address,(strlen(address)>28) ? ".." : "",
               members[y].mobile,(strlen(members[y].mobile)>13) ? ".." : "",
               members[y].email,(strlen(members[y].email)>28) ? ".." : "",members[y].age);
    else
        printf("%04d      %-28.28s%-2.2s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-28.28s%-2.2s   %-10s\n",
               members[y].ID,name,(strlen(name)>28) ? ".." : "",address,(strlen(address)>28) ? ".." : "",
               members[y].mobile,(strlen(members[y].mobile)>13) ? ".." : "",
               members[y].email,(strlen(members[y].email)>28) ? ".." : "", "-");

    if(member_edit_success == 1 && current_member_index == y){
        member_edit_success = 0;
        current_member_index = -1;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void get_address(char address[200],int y,member members[]){
    strcpy(address,"");

    if(members[y].address.buildNum != 0)
    {
        sprintf(address,"%ld", members[y].address.buildNum);
        strcat(address," ");
    }

    if(strcmp(members[y].address.street,"-") != 0)
    {
        strcat(address,members[y].address.street);
        strcat(address," ");
    }

    if(strcmp(members[y].address.city,"-") != 0)
        strcat(address,members[y].address.city);

    if(strcmp(members[y].address.street,"-") == 0 && strcmp(members[y].address.city,"-") == 0 && members[y].address.buildNum == 0)
    {
        strcat(address,"-");
    }
    return;
}

void get_name(char name[55],int y,member members[]){
    strcpy(name,"");

    strcpy(name,members[y].first_name);
    strcat(name," ");
    strcat(name,members[y].last_name);
    return;
}


int search_members(member members[100]){
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, found = 1,previous_members_displayed_number = members_displayed_number, number;
    members_displayed_number = 0;
    input("Enter search term : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -1;}
    if(strcmp(search_txt,"./edit") == 0 && current_member_index != -1) {return -2;}
    if(strcmp(search_txt,"./delete") == 0 && current_member_index != -1) {return -3;}
    int search_again = checkSearchText(search_txt);
    char name[55];
    char address[200];
    clrscr();
    operation_header(6, "Advanced search (edit - delete)");
    if(strcmp(search_txt,"-") == 0)
    {
        display_members(members);
        return;
    }

    for(y = 0; y<i; y++)
    {
        get_address(address,y,members);
        get_name(name,y,members);
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
            if(stristr(name,search_txt) != NULL || stristr(address,search_txt) != NULL || stristr(members[y].email,search_txt) != NULL || strcmp(members[y].mobile,search_txt) == 0)
            {
                add_member_record(y);
            }
            else if(validateInteger(search_txt))
            {
                sscanf(search_txt,"%d\n",&number);
                if(number != 0 && (members[y].ID == number || members[y].age == number))
                    add_member_record(y);
            }
        }
    }
    if(members_displayed_number == 1) {
        display_member(members_displayed[0]);
    }
    else if(members_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-7s   %-30s   %-30s   %-15s   %-30s   %-10s\n","ID","NAME","ADDRESS","MOBILE","EMAIL","AGE");
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

    return members_displayed_number;
}

void display_member(int index)
{
    char name[55];
    char address[200];
    get_address(address,index,member_array);
    get_name(name,index,member_array);
    display_int_info("MEMBER ID : ",member_array[index].ID);
    display_info("NAME : ",name);
    display_info("ADDRESS : ",address);
    display_info("MOBILE : ",member_array[index].mobile);
    display_info("EMAIL : ",member_array[index].email);
    if(member_array[index].age != 0)
        display_int_info("AGE : ",member_array[index].age);
    else
        display_info("AGE : ", "-");
    display_int_info("BORROWED BOOKS : ",member_books_number(member_array[index].ID,-1));
    printf("\n");
    current_member_index = index;
    return;
}

/*
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
/*void add_copy(char ISBN[],int* num_copies)
{
    if(search_ISBN(ISBN)!=-1)
    {
        *num_copies+=1;
    }
    else printf("\nThis member doesn't exist");
}*/

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


int check_email(char email_holder[],int index){
    int y;
    for(y = 0; y<i; y++){
        if(strcmpi(member_array[y].email,email_holder) == 0)
        {
            if(index == -1 || strcmpi(member_array[index].email,email_holder) != 0)
            {
                addError("This email is already used for another member!","");
                return 0;
            }
        }
    }
    return 1;
}

int check_member_ID(int member_ID){
    int y;
    for(y = 0; y<i; y++){
        if(member_array[y].ID == member_ID)
        {
            return 1;
        }
    }
    return 0;
}

int member_index(int id){
    int y;
    for(y = 0; y<i; y++){
        if(member_array[y].ID == id)
        {
            return y;
        }
    }
    return -1;
}

