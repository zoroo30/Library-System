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
void insert_book(void);
void show(book toShow);
void search_title(char search[]);
int search_ISBN(char search[]);
void search_author(char search[]);
void search_publisher(char search[]);
void add_copy(char ISBN[],int* num_copies);
void delete_book(char ISBN[]);
