#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "borrowing.h"
#include "members.h"
#include "book_action.h"

int write_books(book a[], int items, const char * fileName);
int read_books(book a[], const char * fileName);
int write_members(member a[], int items, const char * fileName);
int read_members(member a[], const char * fileName);
int write_borrowed(borrow a[], int items, const char * fileName);
int read_borrowed(borrow a[], const char * fileName);

#endif // FILES_H_INCLUDED
