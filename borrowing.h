typedef struct
{
    char book_isbn[10];
    int member_id;
    //dateStruct date_issued;
    //dateStruct date_should_return;
    //dateStruct date_returned;
} borrowing_record;

borrowing_record br[100];

/*void borrow(char book_isbn[10], int member_id){

}*/

#ifndef BORROW_H_INCLUDED
#define BORROW_H_INCLUDED
int borrowing_info(void);
void save_today(void);
void return_book(char ISBN[],char date[]);
void remove_member(int);
#endif // BORROW_H_INCLUDED
