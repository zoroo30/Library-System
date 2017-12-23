#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "borrowing.h"
#include "members.h"
#include "book_action.h"
#include "files.h"
int write_books(book a[], int items, const char * fileName)
{
    FILE* ptr = fopen(fileName,"wb");
    if(! ptr) return 0; // TODO: better error handling
    fwrite( a, sizeof(book), items, ptr);
    fclose(ptr);
    return 1;
}
int read_books(book a[], const char * fileName)
{
    FILE* ptr = fopen(fileName,"rb");
    if( !ptr ) return 0;
    int n=0;
    while(!feof(ptr))
    {
        fread(&a[n],sizeof(book),1,ptr);
        n++;
    }

    fclose(ptr);
    return n ;
}

int write_members(member a[], int items, const char * fileName)
{
    FILE* ptr = fopen(fileName,"wb");
    if(! ptr) return 0;
    fwrite( a, sizeof(member), items, ptr);
    fclose(ptr);
    return 1;
}
int read_members(member a[], const char * fileName)
{
    FILE* ptr = fopen(fileName,"rb");
    if( !ptr ) return 0;
    int n=0;
    while(!feof(ptr))
    {
        fread(&a[n],sizeof(member),1,ptr);
        n++;
    }

    fclose(ptr);
    return n ;
}
int write_borrowed(borrow a[], int items, const char * fileName)
{
    FILE* ptr = fopen(fileName,"wb");
    if(! ptr) return 0; // TODO: better error handling
    fwrite( a, sizeof(borrow), items, ptr);
    fclose(ptr);
    return 1;
}
int read_borrowed(borrow a[], const char * fileName)
{
    FILE* ptr = fopen(fileName,"rb");
    if( !ptr ) return 0;
    int n=0;
    while(!feof(ptr))
    {
        fread(&a[n],sizeof(borrow),1,ptr);
        n++;
    }

    fclose(ptr);
    return n ;
}
