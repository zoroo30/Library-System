
/*void borrow(char book_isbn[10], int member_id){

}*/

#ifndef BORROW_H_INCLUDED
#define BORROW_H_INCLUDED
#include "book_action.h"


typedef struct
{
    int id;
    char book_isbn[30];
    int member_id;
    dateStruct date_issued;
    int skip_days;
    dateStruct date_should_return;
    dateStruct date_returned;
} borrow;

extern borrow borrow_array[100];
extern int borrows_displayed[100];
extern int current_borrow_index;
extern int borrows_displayed_number;
extern int borrow_delete_success;

int borrowing_info(void);
void save_today(void);
void return_book(char ISBN[],char date[]);
void remove_member(int);
#endif // BORROW_H_INCLUDED
