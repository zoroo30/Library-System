#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "book_action.h"
book book_array[50];
int i=5;
void insert_book(void)
{
    book inserted;
    gets(inserted.title);
    gets(inserted.author);
    gets(inserted.publisher);
    gets(inserted.ISBN);
    scanf("%d%d",&(inserted.copies),&(inserted.current));
    scanf("%d%d%d",&(inserted.date.day),&(inserted.date.month),&(inserted.date.year));
    book_array[i]=inserted;
    i++;
    return ;
}

void show(book toShow)
{
    printf("Title: %s\n",toShow.title);
    printf("Author: %s\n",toShow.author);
    printf("Publisher: %s\n",toShow.publisher);
    printf("ISBN: %s\n",toShow.ISBN);
    printf("Date: %d\\%d\\%d\n",toShow.date.day,toShow.date.month,toShow.date.year);
    printf("available Copies: %d\nCurrent Copies: %d\n",toShow.copies,toShow.current);
}

void search_title(char search[])
{
    int j=0;
    while(strstr(book_array[j].title,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].title,search)== NULL) printf("\nOur library doesn't have this book\n");
    else show(book_array[j]);

}

int search_ISBN(char search[])
{
    int j=0;
    while(strstr(book_array[j].ISBN,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].ISBN,search)== NULL) return -1;
    else return j;

}

void search_author(char search[])
{
    int j=0;
    while(strstr(book_array[j].author,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].author,search)== NULL) printf("\nOur library doesn't have this book\n");
    else show(book_array[j]);

}
void search_publisher(char search[])
{
    int j=0;
    while(strstr(book_array[j].publisher,search)== NULL && j<i)
    {
        j++;
    }
    if(strstr(book_array[j].publisher,search)== NULL) printf("\nOur library doesn't have this book\n");
    else show(book_array[j]);

}
void add_copy(char ISBN[],int* num_copies)
{
    if(search_ISBN(ISBN)!=-1)
    {
        *num_copies+=1;
    }
    else printf("\nThis book doesn't exist");
}
void delete_book(char ISBN[])
{
    int index=search_ISBN(ISBN);
    int j=index;
    if(index!=-1)
        while(j<i)
        {
          book_array[j]=book_array[j+1];
          j++;
        }
    else printf("\nThis book doesn't exist");
    return;
}
