typedef struct
{
    int day;
    int month;
    int year;
} dateStruct;

typedef struct
{
    char title[10];//we need to handle longer titles
    char author[10];//same
    char publisher[10];//same
    char ISBN[20];
    dateStruct* date;
    int copies;
    int current;
} book;

