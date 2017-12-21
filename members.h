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
