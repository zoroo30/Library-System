#ifndef BOOK_ACTION_H_INCLUDED
#define BOOK_ACTION_H_INCLUDED

typedef struct
{

    int day;
    int month;
    int year;
} dateStruct;

typedef struct
{

    int buildNum;//use validateNegative
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
    char ISBN[10];
    dateStruct date;
    int copies;
    int current;
    int times_borrowed;
} book;

typedef struct
{
    char name[10];
    int ID;
    addressStruct address;
    int mobile;
    int age;
    emailStruct email;
    //add number of books borrowed field initialized to zero
    int booksBorrowed;
} member;
typedef struct
{

    member whoBorrow;
    book whatBorrow;
    dateStruct whenBorrow;
    dateStruct whenReturn;
    dateStruct whenBack;
} borrow;

void insert_book(void);
void show(book toShow);
void search_title(char search[]);
int search_ISBN(char search[]);
void search_author(char search[]);
void search_publisher(char search[]);
void add_copy(char ISBN[],int* num_copies);
void delete_book(char ISBN[]);

#endif // BOOK_ACTION_H_INCLUDED
