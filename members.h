#ifndef MEMBER_H_INCLUDED
#define MEMBER_H_INCLUDED

typedef struct
{
    int buildNum;
    char street[100];
    char city[100];
} addressStruct;
typedef struct
{
    char name[10];
    char domain[10];

} emailStruct;
typedef struct
{
    char name[100];
    int ID;
    addressStruct address;
    char mobile[13];
    int age;
    char email[100];
} member;


extern int current_member_index;


int insert_member();
int borrow_book(void);
void registeration(void);
int search_ID(int );

#endif // MEMBER_H_INCLUDED
