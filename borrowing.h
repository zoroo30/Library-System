typedef struct
{
    char book_isbn[10];
    int member_id;
    dateStruct date_issued;
    dateStruct date_should_return;
    dateStruct date_returned;
} borrowing_record;

borrowing_record br[100];

/*void borrow(char book_isbn[10], int member_id){

}*/

int borrow_book()
{
    char buf_borrow[10];
    char buf_back[10];
    char buf_return[10];
    bool validity=true;
    fgets(borrow_array[rw].whatBorrow.ISBN,sizeof(borrow_array[rw].whatBorrow.ISBN),stdin);
    int index=search_ISBN(borrow_array[rw].whatBorrow.ISBN);
    if(index!=-1)
    {
        --(book_array[bk].current);
    }
    else return -1;
    scanf("%d",&(borrow_array[rw].whoBorrow.ID));
    getc(stdin);
    int index_=search_ID(borrow_array[rw].whoBorrow.ID);
    if(index_ != -1) (member_array[mm].booksBorrowed++);
    else return -1;
    fgets(buf_borrow,sizeof(buf_borrow),stdin);
    validity = vali_date(buf_borrow);
    if(validity) sscanf(buf_borrow,"%d/%d/%d",&(borrow_array[rw].whenBorrow.day),
                            &(borrow_array[rw].whenBorrow.month),&(borrow_array[rw].whenBorrow.year));
    else return -1;
    fgets(buf_back,sizeof(buf_back),stdin);
    validity = vali_date(buf_back);
    if(validity) sscanf(buf_back,"%d/%d/%d",&(borrow_array[rw].whenBack.day),
                            &(borrow_array[rw].whenBack.month),&(borrow_array[rw].whenBack.year));
    else return -1;


}
