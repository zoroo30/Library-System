typedef struct
{
    char book_isbn[10];
    int member_id;
    dateStruct date_issued;
    dateStruct date_should_return;
    dateStruct date_returned;
} borrowing_record;

borrowing_record br[100];

void borrow(char book_isbn[10], int member_id){

}
