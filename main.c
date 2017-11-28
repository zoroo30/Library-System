##include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
COORD coord = {0, 0};
void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

typedef struct
{
    int day;
    int month;
    int year;
} dateStruct;

typedef struct
{
    int buildNum;
    char street[10];
    char city[10];
} addressStruct;

typedef struct
{
    char name[10];
    char domain[10];

} emailStruct;

typedef struct
{
    char title[10];//we need to handle longer titles
    char author[10];//same
    char publisher[10];//same
    int ISBN;
    dateStruct* date;
    int copies;
    int current;
} book;

typedef struct
{
    char name[10];
    int ID;
    addressStruct* address;
    long int mobile;
    int age;
    emailStruct* email;
} member;
typedef struct
{
    member* whoBorrow;
    book* whatBorrow;
    dateStruct* whenBorrow;
    dateStruct* whenReturn;
} borrow;
char category[][20]= {"Computer Science","Electrical","Architecture","Civil","Mechanical","Encyclopedia"};
void mainMenu(void)
{
    FILE* ptr;
    char menu,sub;
    system("COLOR f");
    gotoxy(15,5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU ");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n");
    gotoxy(20,8);
    printf("\xDB\xDB\xDB\xDB\xB2\xB2  Book Management");
    gotoxy(50,8);
    printf(">> B");
    gotoxy(20,10);
    printf("\xDB\xDB\xDB\xDB\xB2\xB2  Member Management");
    gotoxy(50,10);
    printf(">> M");
    gotoxy(20,12);
    printf("\xDB\xDB\xDB\xDB\xB2\xB2  Administrative Action");
    gotoxy(50,12);
    printf(">> A");
    gotoxy(20,14);
    printf("\xDB\xDB\xDB\xDB\xB2\xB2  Save");
    gotoxy(50,14);
    printf(">> S");
    gotoxy(20,16);
    printf("\xDB\xDB\xDB\xDB\xB2\xB2  exit\n");
    gotoxy(50,16);
    printf(">> E");
    gotoxy(20,18);
    printf("Please Make A Selection ");
    menu=getchar();
    switch(menu)
    {
    case('b'||'B'):

        gotoxy(20,8);
        printf("\xDB\xDB\xDB\xDB\xB2\xB2 1. Insert a new book");
        gotoxy(20,10);
        printf("\xDB\xDB\xDB\xDB\xB2\xB2 2. Search for a book");
        gotoxy(20,12);
        printf("\xDB\xDB\xDB\xDB\xB2\xB2 3. Add new copy");
        gotoxy(20,14);
        printf("\xDB\xDB\xDB\xDB\xB2\xB2 4. Delete book");
        printf("Please Make A Selection : ");
        sub=getchar();
        switch(sub)
        {
        case'1' :
        {
            book insert;
            gotoxy(15,5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Insert A Book ");
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n");
           // function to read inserted book to a file
            gotoxy(20,10);
            printf("Title:");
            printf("Author :");
            gotoxy(20,14);
            printf("Publisher :");
            gotoxy(20,16);
            printf("ISBN :");
            gotoxy(20,18);
            printf("Date :");
            gotoxy(20,20);
            printf("Number of copies :");
            gotoxy(20,22);
            printf("Available copies :");
            gotoxy(20,24);
            printf("select a category :");
            gotoxy(24,26);
            printf("*Computer Science *Electrical *Architecture *Civil *Mechanical *Encyclopedia");

        }

        }
    }}

    // case'2' :
    //case'3' :
    //case'4' :
    //case'5' :
    //default :



    int main()
    {
        mainMenu();
        return 0;
    }

