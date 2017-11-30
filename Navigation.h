#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "validation.h"

//Navigation
typedef struct {
    int id;
    int parent_item_id;
    char value[50];
    char key[5];
} menu_item;


    //defining menu items
    menu_item menu_items[] = {
        {0, -1, "Book Management", "1"},
        {1, 0, "Insert", "1"},
        {2, 0, "Search", "2"},
        {3, 0, "Add new copies", "3"},
        {4, 0, "Delete", "4"},
        {5, 0, "Edit", "5"},
        {6, -1, "User Management", "2"},
        {7, 6, "Register", "1"},
        {8, 6, "Remove", "2"},
        {9, -1, "Borrow Management", "3"},
        {10, 9, "Borrow", "1"},
        {11, 9, "Return", "2"},
        {12, -1, "Administrative actions", "4"},
        {13, 12, "Overdue", "1"},
        {14, 12, "Popular", "2"},
        {15, -1, "Save changes", "5"},
        {16, -1, "Exit", "6"},
        {17, 16, "Save and exit", "1"},
        {18, 16, "Exit without saving", "2"},
        {19, 0, "Return to the main menu", "6"},
        {19, 6, "Return to the main menu", "3"},
        {19, 9, "Return to the main menu", "3"},
        {19, 12, "Return to the main menu", "3"},
        {19, 16, "Return to the main menu", "3"}
    };


void clrscr()
{
    system("@cls||clear");
}

void load_menu(int parent_id, char error[100]){

    display_menu(parent_id, error);

    int items_count = sizeof(menu_items)/sizeof(menu_items[0]);
    //waiting for user input and navigate him to his desired section
    char choice[5] = ""; //>>>>>>>>>>>>>>>>>>>>>>WE SHOULD LIMIT THE NUMBER OF CHARS<<<<<<<<<<<<<<<<<<<<<<<<<<<

    while(!check(choice, parent_id, items_count))
    {
        printf("Enter your choice : ");
        scanf(" %4s", choice);
        while(getchar() != '\n');
        if(!check(choice, parent_id, items_count))
            display_menu(parent_id, "Please choose one of the options above");
    }
    try_to_go(choice, parent_id, items_count);
}

void display_menu(int parent_id, char error[100]){
    //clear screen
    clrscr();

    int i;

    //printing section title and returning the length of the printed string
    int sep_size = print_header("Library System",(parent_id != -1) ? menu_items[parent_id].value : "");

    //getting items count
    int items_count = sizeof(menu_items)/sizeof(menu_items[0]);

    //printing items (depends on the parent)
    for(i=0;i<items_count;i++){
        if(menu_items[i].parent_item_id == parent_id)
            printf("\n==> %s (%S)\n", menu_items[i].value, menu_items[i].key);
    }

    //printing a seprator with the same length as the title
    print_seprator(sep_size);


    if(error[0] != '\0')
    {
        printf("%s\n",error);
    }
}

int print_header(char main_title[], char secondary_title[]){
    char secondary[20] = "";
    if(secondary_title[0] != '\0')
    {
        strcpy(secondary," : ");
        strcat(secondary,secondary_title);
    }
    printf("======================== %s%s ========================\n",main_title,secondary);
    return 50+strlen(main_title)+strlen(secondary);
}

void print_seprator(int ssize){
    int i;
    printf("\n");
    for(i=0; i<ssize; i++){
        printf("=");
    }
    printf("\n");
}

int check(char choice[], int parent_id, int items_count){
    int i, id = -1;
    for(i=0;i<items_count;i++){
        if(menu_items[i].parent_item_id == parent_id && strcmp(menu_items[i].key,choice)==0){
            id = menu_items[i].id;
            return 1;
        }
    }
    return 0;
}

void try_to_go(char choice[], int parent_id, int items_count){
    int i, id = -1;
    for(i=0;i<items_count;i++){
        if(menu_items[i].parent_item_id == parent_id && strcmp(menu_items[i].key,choice)==0){
            id = menu_items[i].id;
            break;
        }
    }
    switch(id) {
        case -1:
            if(strcmp(choice,"-1")==0 && parent_id != -1)
                load_menu(-1,"");
            else if(strcmp(choice,"0")==0)
                exit(0);
            else
                load_menu(parent_id,"Please choose one of the options above or enter 0 to exit the program");
            return 0;
        case 0:
            load_menu(0,"");
            return 1;
        case 1:
            //Insert new book

            return 1;
        case 2:
            //Search books

            return 1;
        case 3:
            //Add new copies

            return 1;
        case 4:
            //Delete

            return 1;
        case 5:
            //Edit

            return 1;
        case 6:
            load_menu(6,"");
            return 1;
        case 7:
            //Register new member

            return 1;
        case 8:
            //Remove member

            return 1;
        case 9:
            load_menu(9,"");
            return 1;
        case 10:
            //Borrow

            return 1;
        case 11:
            //Return

            return 1;
        case 12:
            load_menu(12,"");
            return 1;
        case 13:
            //Overdue

            return 1;
        case 14:
            //Popular

            return 1;
        case 15:
            load_menu(-1,"Your changes have been saved");
            return 1;
        case 16:
            load_menu(16,"");
            return 1;
        case 17:
            //Save and exit

            return 1;
        case 18:
            //Exit without saving

            return 1;
        case 19:
                load_menu(-1,"");
            return 1;
        default:
            break;
    }
    return;
}

