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
    char first_name[25];
    char last_name[25];
    int ID;
    addressStruct address;
    char mobile[13];
    int age;
    char email[100];
    int booksBorrowed;
} member;


extern member member_array[100];
extern int members_displayed[100];
extern int current_member_index;
extern int members_displayed_number;
extern int member_delete_success;

#endif // MEMBER_H_INCLUDED
