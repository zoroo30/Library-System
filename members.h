typedef struct
{
    int buildNum;
    char street[10];
    char city[10];
} addressStruct;

typedef struct
{
    char name[10];
    char domain[10];

} emailStruct;

typedef struct
{
    char name[10];
    int ID;
    addressStruct address;
    long int mobile;
    int age;
    emailStruct email;
} member;
