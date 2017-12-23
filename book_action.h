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
    char title[100];//we need to handle longer titles
    char author[100];//same
    char publisher[100];//same
    char ISBN[30];
    dateStruct date;
    int copies;
    int current;
    char category[30];
    int borrowing_number;
} book;

extern book book_array[100];
extern int books_displayed[100];
extern int current_book_index;
extern int books_displayed_number;
extern int book_delete_success;

int insert_book();
void show(book toShow);
void search_title(char search[]);
int search_ISBN(book books[100], char subtitle[]);
void search_author(char search[]);
void search_publisher(char search[]);
void add_copy(char ISBN[],int* num_copies);
void delete_book(int index);
#endif // BOOK_ACTION_H_INCLUDED
