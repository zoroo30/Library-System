#include "book_action.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "validation.h"

/*
typedef struct
{
    char title[100];//we need to handle longer titles
    char author[100];//same
    char publisher[100];//same
    char ISBN[30];
    dateStruct date;
    int copies;
    int current;
    char category[30];
} book;
*/

book book_array[100] = {{"Welcome To C","Ahmed Tarek kamal aboughanima","-","23213-123-12123",{10,2,2005},20,20,"-"},
                        {"Lord of The rings","nour","-","23213-123",{0,0,0},5,5,"-"},
                        {"Lord of The flies","nour","-","23213-12123",{0,0,0},5,5,"-"},
                        {"The lord","malek","-","q23213-123-12123",{0,0,0},5,5,"-"},
                        {"Book","Ahmed Tarek","-","Q23213-123-12123",{3,4,2010},3,3,"-"},
                        {"NOt book","Ahmed Tarek","-","23213-123-12123",{20,3,2011},6,6,"-"},
                        {"Blah blah","Ahmed Tarek","-","23213-123-12123",{3,1,1998},12,12,"-"},
                        {"no yes","Ahmed Tarek","-","23213-123-12123",{7,11,1997},1,1,"-"}};
int i=8;

int books_displayed[100];
int books_displayed_number = 0;

int current_book_index = -1, edit_success = 0, book_delete_success = -1;

int insert_book(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(i != 100 || index != -1) {
        book inserted;
        char buffer[11];
        char ISBN_holder[30];
        char term;

        input("\nEnter book ISBN (required) [30] : ",ISBN_holder,30,"ISBN",1);
        if(!(strcmp(ISBN_holder,".") == 0 && index != -1) && check_ISBN(ISBN_holder))
            strcpy(inserted.ISBN,ISBN_holder);

        input("Enter book title (required) [100] : ",inserted.title,100,"Title",1);
        input("Enter author name [100] : ",inserted.author,100,"Author",0);
        input("Enter publisher [100] : ",inserted.publisher,100,"Publisher",0);


        input("Enter date of publication dd/mm/yyyy or dd-mm-yyyy : ",buffer,11,"Date",0);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateDate(buffer)){
                    case 1:
                        sscanf(buffer,"%d/%d/%d",&inserted.date.day,&inserted.date.month,&inserted.date.year);
                    case 2:
                        sscanf(buffer,"%d-%d-%d",&inserted.date.day,&inserted.date.month,&inserted.date.year);
                    default:
                        break;
                }
            } else {
                    sscanf("0/0/0","%d/%d/%d",&inserted.date.day,&inserted.date.month,&inserted.date.year);
            }
        }
        else
        {
            inserted.date = book_array[index].date;
        }

        input("Enter number of copies (required) : ",buffer,11,"Copies number",1);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid integer for the copies number","");
                    case 1:
                        sscanf(buffer,"%d\n",&inserted.copies);
                        if(inserted.copies < 0){
                            addError("Number of copies can not be a negative value","");
                        }else
                            inserted.current = inserted.copies;
                    default:
                        break;
                }
            }
        }
        else
        {
            inserted.copies = book_array[index].copies;
            inserted.current = book_array[index].current;
        }

        input("Enter book category [30] : ",inserted.category,30,"Category",0);

        if(errors_number == 0) {
            printSuccess((index == -1) ? "The book data has been successfully added!" : "The book data has been successfully updated!");
            if(index == -1)
            {
                book_array[i] = inserted;
                //printf("%s  -  %s  -  %s  -  %s  -  %s  -  %d  -  %d  -  %s", book_array[i].title, book_array[i].author, book_array[i].publisher, book_array[i].ISBN, buffer, book_array[i].copies, book_array[i].current, book_array[i].category);
                i++;
            } else {
                edit_success = 1;
                if(strcmp(ISBN_holder,".") != 0)
                    strcpy(book_array[index].ISBN,inserted.ISBN);
                if(strcmp(inserted.title,".") != 0)
                    strcpy(book_array[index].title,inserted.title);
                if(strcmp(inserted.author,".") != 0)
                    strcpy(book_array[index].author,inserted.author);
                if(strcmp(inserted.publisher,".") != 0)
                    strcpy(book_array[index].publisher,inserted.publisher);

                book_array[index].date = inserted.date;
                book_array[index].copies = inserted.copies;
                book_array[index].current = inserted.current;

                if(strcmp(inserted.category,".") != 0)
                    strcpy(book_array[index].category,inserted.category);
            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 books",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_book_index = -1;
    return 0;
}

int edit_copies(int index)
{
    errors_number = 0;

    if(index != -1) {
        printf("\nEnter '.' if you want to keep the previous field value\n");
    }

    if(i != 100 || index != -1) {
        book inserted;
        char buffer[11];

        input("\nEnter number of copies (required) : ",buffer,11,"Copies number",1);
        if (!(index != -1 && strcmp(buffer,".") == 0))
        {
            if(strcmp(buffer,"-") != 0){
                switch(validateInteger(buffer)){
                    case 0:
                        addError("Enter a valid integer for the copies number","");
                    case 1:
                        sscanf(buffer,"%d\n",&inserted.copies);
                        if(inserted.copies < 0){
                            addError("Number of copies can not be a negative value","");
                        }else
                            inserted.current = inserted.copies;
                    default:
                        break;
                }
            }
        }
        else
        {
            inserted.copies = book_array[index].copies;
            inserted.current = book_array[index].current;
        }

        if(errors_number == 0) {
            printSuccess((index == -1) ? "The book data has been successfully added!" : "The book data has been successfully updated!");
            if(index == -1)
            {
                book_array[i] = inserted;
                //printf("%s  -  %s  -  %s  -  %s  -  %s  -  %d  -  %d  -  %s", book_array[i].title, book_array[i].author, book_array[i].publisher, book_array[i].ISBN, buffer, book_array[i].copies, book_array[i].current, book_array[i].category);
                i++;
            } else {
                edit_success = 1;

                book_array[index].copies = inserted.copies;
                book_array[index].current = inserted.current;

            }
            return 1;
        }
    } else {addError("library cannot accommodate more than 100 books",""); }
    printErrors((index == -1) ? "Adding" : "Editing");
    current_book_index = -1;
    return 0;
}

int display_books(book books[100]) {
    if(i != 0) {
        int y;
        books_displayed_number = 0;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-30s   %-15s   %-15s   %-18s   %-10s   %-10s   %-15s\n","BOOK ISBN","BOOK TITLE","AUTHOR","PUBLISHER","PUBLICATION DATE","COPIES","AVALIBLE","CATEGORY");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(y = 0; y<i; y++) {
            add_book_record(y);
            display_book_record(books,y);
        }
    }

    if(book_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(book_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    book_delete_success = -1;

    return i;
}

void add_book_record(int y) {
    books_displayed[books_displayed_number] = y;
    books_displayed_number++;
}

void display_book_record(book books[100], int y) {
    if(edit_success == 1 && current_book_index == y)
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 47);

    if(books[y].date.day != 0)
        //%-30.30s   %-30.30s   %-15.15s   %-15.15s
        printf("%-30s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-13.13s%-2.2s   %02d/%02d/%04d           %-10d   %-10d   %-13.13s%-2.2s\n",books[y].ISBN,books[y].title,(strlen(books[y].title)>28) ? ".." : "",books[y].author,(strlen(books[y].author)>13) ? ".." : "",books[y].publisher,(strlen(books[y].publisher)>13) ? ".." : "", books[y].date.day, books[y].date.month, books[y].date.year, books[y].copies, books[y].current, books[y].category,(strlen(books[y].category)>13) ? ".." : "");
    else
        printf("%-30s   %-28.28s%-2.2s   %-13.13s%-2.2s   %-13.13s%-2.2s   -                    %-10d   %-10d   %-13.13s%-2.2s\n",books[y].ISBN,books[y].title,(strlen(books[y].title)>28) ? ".." : "",books[y].author,(strlen(books[y].author)>13) ? ".." : "",books[y].publisher,(strlen(books[y].publisher)>13) ? ".." : "", books[y].copies, books[y].current, books[y].category,(strlen(books[y].category)>13) ? ".." : "");

    if(edit_success == 1 && current_book_index == y){
        edit_success = 0;
        current_book_index = -1;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

int search_books(book books[100]){
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, found = 1,previous_books_displayed_number = books_displayed_number, number, is_date, dd,mm,yy;
    books_displayed_number = 0;
    input("Enter search term : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -1;}
    if(strcmp(search_txt,"./edit") == 0 && current_book_index != -1) {return -2;}
    if(strcmp(search_txt,"./copies") == 0 && current_book_index != -1) {return -3;}
    if(strcmp(search_txt,"./delete") == 0 && current_book_index != -1) {return -4;}
    int search_again = checkSearchText(search_txt);
    clrscr();
    operation_header(0, "Search books");
    if(strcmp(search_txt,"-") == 0)
    {
        display_books(books);
        return;
    }

    for(y = 0; y<i; y++)
    {
        if(search_again && previous_books_displayed_number != 0 && previous_books_displayed_number != 1)
        {
            found = 0;
            for(z = 0; z<previous_books_displayed_number; z++)
            {
                if(books_displayed[z] == y)
                {
                    found = 1;
                    break;
                }
            }
        }
        errors_number = 0;
        if(found == 1){
            if(strcmpi(books[y].ISBN,search_txt) == 0 || stristr(books[y].title,search_txt) != NULL || stristr(books[y].author,search_txt) != NULL || stristr(books[y].publisher,search_txt) != NULL || stristr(books[y].category,search_txt) != NULL)
            {
                add_book_record(y);
            }
            else if(validateInteger(search_txt))
            {
                sscanf(search_txt,"%d\n",&number);
                if(books[y].copies == number || books[y].current == number || ((books[y].date.day == number || books[y].date.month == number || books[y].date.year == number) && number != 0))
                    add_book_record(y);
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
                if(books[y].date.day == dd && books[y].date.month == mm && books[y].date.year == yy)
                    add_book_record(y);
            }
        }
    }
    if(books_displayed_number == 1) {
        display_book(books_displayed[0]);
    }
    else if(books_displayed_number != 0) {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 27);
        printf("\n%-30s   %-30s   %-15s   %-15s   %-18s   %-10s   %-10s   %-15s\n","BOOK ISBN","BOOK TITLE","AUTHOR","PUBLISHER","PUBLICATION DATE","COPIES","AVALIBLE","CATEGORY");
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for(z=0;z<books_displayed_number;z++)
            display_book_record(books,books_displayed[z]);
    }

    if(book_delete_success == 0){
        display_info("  Delete operation has been canceled  ","");
    } else if(book_delete_success ==1) {
        display_info("  The record has been deleted  ","");
    }

    book_delete_success = -1;

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

void display_book(int index)
{
    display_info("BOOK ISBN : ",book_array[index].ISBN);
    display_info("BOOK TITLE : ",book_array[index].title);
    display_info("AUTHOR : ",book_array[index].author);
    display_info("PUBLISHER : ",book_array[index].publisher);
    display_date_info("PUBLICATION DATE : ",book_array[index].date.day, book_array[index].date.month, book_array[index].date.year);
    display_int_info("COPIES : ",book_array[index].copies);
    display_int_info("AVALIBLE : ",book_array[index].current);
    display_info("CATEGORY : ",book_array[index].category);
    printf("\n");
    current_book_index = index;
    return;
}

void search_title(char search[])
{
    int j=0;
    while(strstr(book_array[j].title,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].title,search)== NULL) printf("\nOur library doesn't have this book\n");
    else display_book(j);

}

int search_ISBN(book books[100], char subtitle[])
{
    char search_txt[100];
    strcpy(search_txt,"");
    int y, z, previous_books_displayed_number = books_displayed_number;
    books_displayed_number = 0;
    input("Enter Book ISBN : ", search_txt, 100, "", 0);
    if(strcmp(search_txt,"./menu") == 0) {return -2;}
    else if(strcmp(search_txt,"./search") == 0) {return -3;}
    clrscr();
    operation_header(0, subtitle);

    for(y = 0; y<i; y++)
    {
        if(strcmpi(books[y].ISBN,search_txt) == 0)
        {
            add_book_record(y);
        }
    }

    if(books_displayed_number == 1) {
        display_book(books_displayed[0]);
    } else if (books_displayed_number != 0){
        display_info("the same ISBN is used for more than 1 book","");
    }

    printf("\nYou searched for : %s ", search_txt);

    return books_displayed_number;
}

void search_author(char search[])
{
    int j=0;
    while(strstr(book_array[j].author,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].author,search)== NULL) printf("\nOur library doesn't have this book\n");
    else display_book(j);

}
void search_publisher(char search[])
{
    int j=0;
    while(strstr(book_array[j].publisher,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].publisher,search)== NULL) printf("\nOur library doesn't have this book\n");
    else display_book(j);

}
/*void add_copy(char ISBN[],int* num_copies)
{
    if(search_ISBN(ISBN)!=-1)
    {
        *num_copies+=1;
    }
    else printf("\nThis book doesn't exist");
}*/
void delete_book(int index)
{
    int j=index;
    if(index!=-1)
    {
        while(j<i)
        {
            book_array[j]=book_array[j+1];
            j++;
        }
        i--;
        current_book_index = -1;
        book_delete_success = 1;
    }
    else printf("\nThis book doesn't exist");
    return;
}

int check_ISBN(char ISBN_holder[]){
    int y;
    for(y = 0; y<i; y++){
        if(strcmpi(book_array[y].ISBN,ISBN_holder) == 0)
        {
            addError("This ISBN is already used for another book!","");
            return 0;
        }
    }
    return 1;
}
