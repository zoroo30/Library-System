#ifndef BORROW_H_INCLUDED
#define BORROW_H_INCLUDED
bool borrowing_info(void);
void save_today(void);
void return_book(char ISBN[],char date[]);
void remove_member(int);
#endif // BORROW_H_INCLUDED
