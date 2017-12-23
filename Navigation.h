#include "book_action.h"
#include "members.h"
#include "borrowing.h"
#include "validation.h"
#include <windows.h>

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
    {1, 0, "Add new book", "1"},
    {2, 0, "Advanced search (edit - delete)", "2"},
    /*{3, 0, "Edit book copies", "3"},
    {4, 0, "Delete", "4"},
    {5, 0, "Edit", "5"},*/
    {6, -1, "User Management", "2"},
    {7, 6, "Register new user", "1"},
    {8, 6, "Advanced search (edit - delete)", "2"},
    {9, -1, "Borrow Management", "3"},
    {10, 9, "Borrow", "1"},
    {11, 9, "Advanced search (edit - delete)", "2"},
    {12, -1, "Administrative actions", "4"},
    {13, 12, "Overdue", "1"},
    {14, 12, "Popular", "2"},
    {15, -1, "Save changes", "5"},
    {16, -1, "Exit", "6"},
    {17, 16, "Save and exit", "1"},
    {18, 16, "Exit without saving", "2"},
    {19, 0, "Return to the main menu", "3"},
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
    char choice[5] = "";

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
    int sep_size = print_header("Library System",(parent_id != -1) ? menu_items[get_operation_index(parent_id)].value : "");

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

int get_operation_index(int id){

    int i;
    //getting items count
    int items_count = sizeof(menu_items)/sizeof(menu_items[0]);

    //printing items (depends on the parent)
    for(i=0;i<items_count;i++){
        if(menu_items[i].id == id)
            return i;
    }
    return -1;
}


int print_header(char main_title[], char secondary_title[]){
    char secondary[50] = "";
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

void next_step(int operation_id,int parent_id){
    print_seprator(80);
    printf("\n==> repeat the last operation (1)\n\n==> return to the menu (2)\n");
    char choice[5] = "";
    print_seprator(80);
    while(strcmp("1",choice)!=0 && strcmp("2",choice)!=0)
    {
        printf("Enter your choice : ");
        scanf(" %4s", choice);
        while(getchar() != '\n');
        if(strcmp("1",choice)!=0 && strcmp("2",choice)!=0)
        {
            clrscr();
            int sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            printf("\n==> repeat the last operation (1)\n\n==> return to the menu (2)\n");
            print_seprator(sep_size);
            printf("Please choose one of the options above\n");
        }
    }

    if(strcmp("1",choice)==0)
        go(operation_id,parent_id);
    else if(strcmp("2",choice)==0)
        go(parent_id,-1);
}

void search_next_step(int operation_id,int parent_id, int record_index, int in_operation, char section[]){
    print_seprator(80);
    printf("\n==> repeat the last operation (1)\n\n==> continue searching (2)\n\n==> return to the menu (3)\n");
    char choice[5] = "";
    print_seprator(80);
    while(strcmp("1",choice)!=0 && strcmp("2",choice)!=0 && strcmp("3",choice)!=0)
    {
        printf("Enter your choice : ");
        scanf(" %4s", choice);
        while(getchar() != '\n');
        if(strcmp("1",choice)!=0 && strcmp("2",choice)!=0 && strcmp("3",choice)!=0)
        {
            clrscr();
            int sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            printf("\n==> repeat the last operation (1)\n\n==> continue searching (2)\n\n==> return to the menu (3)\n");
            print_seprator(sep_size);
            printf("Please choose one of the options above\n");
        }
    }


    if(strcmp("3",choice)==0)
    {
        go(parent_id,-1);
    }
    else if(strcmp("Books",section) == 0)
    {
        if(strcmp("1",choice)==0)
        {
            int sep_size;
            if(in_operation == 0)
                sep_size = operation_header(parent_id,"Edit book");
            else
                sep_size = operation_header(parent_id,"Edit book copies");
            current_book_index = record_index;
            display_book(record_index);
            print_seprator(sep_size);
            if(in_operation == 0)
                insert_book(record_index);
            else
                edit_copies(record_index);
            search_next_step(operation_id,parent_id,record_index,in_operation,section);
        }
        else if(strcmp("2",choice)==0)
        {
            int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
            display_book(record_index);
            books_displayed_number = 1;
        }
    }
    else if(strcmp("Members",section) == 0)
    {
        if(strcmp("1",choice)==0)
        {
            int sep_size;

            sep_size = operation_header(parent_id,"Edit member");

            current_member_index = record_index;
            display_member(record_index);
            print_seprator(sep_size);

            insert_member(record_index);

            search_next_step(operation_id,parent_id,record_index,in_operation,section);
        }
        else if(strcmp("2",choice)==0)
        {
            int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
            display_member(record_index);
            members_displayed_number = 1;
        }
    }
    else if(strcmp("borrows",section) == 0)
    {
        if(strcmp("1",choice)==0)
        {
            int sep_size;
            if(in_operation == 0)
                sep_size = operation_header(parent_id,"Edit borrow");
            else
                sep_size = operation_header(parent_id,"Edit borrow copies");
            current_borrow_index = record_index;
            display_borrow(record_index);
            print_seprator(sep_size);
            if(in_operation == 0)
                insert_borrow(record_index);
            else
                edit_return_date(record_index);
            search_next_step(operation_id,parent_id,record_index,in_operation,section);
        }
        else if(strcmp("2",choice)==0)
        {
            int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
            display_borrow(record_index);
            borrows_displayed_number = 1;
        }
    }
    return;
}

int are_you_sure(int operation_id, int parent_id,int sep_size){
    printf("\nAre you sure you want delete this record ?");
    printf("\n\n==> yes (1)\n==> no (2)\n");
    print_seprator(sep_size);
    char choice[5] = "";
    while(strcmp("1",choice)!=0 && strcmp("2",choice)!=0)
    {
        printf("Enter your choice : ");
        scanf(" %4s", choice);
        while(getchar() != '\n');
        if(strcmp("1",choice)!=0 && strcmp("2",choice)!=0)
        {
            clrscr();
            int sep_size = operation_header(parent_id, book_array[current_book_index].title);
            printf("\nAre you sure you want delete this record ?");
            printf("\n\n==> yes (1)\n==> no (2)\n");
            print_seprator(sep_size);
            printf("Please choose one of the options above\n");
        }
    }

    if(strcmp("1",choice)==0)
        return 1;
    else if(strcmp("2",choice)==0)
        return 0;
}

int operation_header(int parent_id, char *title){
    clrscr();
    char main_title[100] = "Library System : ";
    strcat(main_title, menu_items[get_operation_index(parent_id)].value);
    int sep_size = print_header(main_title, title);
    return sep_size;
}

void try_to_go(char choice[], int parent_id, int items_count){
    int i, id = -1;
    for(i=0;i<items_count;i++){
        if(menu_items[i].parent_item_id == parent_id && strcmp(menu_items[i].key,choice)==0){
            id = menu_items[i].id;
            break;
        }
    }

    go(id,parent_id);

    return;
}

void go(int operation_id,int parent_id) {
    int sep_size;
    int results_number, all_records_number;
    switch(operation_id) {
        case -1:
            load_menu(parent_id,"Please choose one of the options above or enter 0 to exit the program");
            return 0;
        case 0:
            load_menu(0,"");
            return 1;
        case 1:
            //Insert new book
            operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            insert_book(-1);
            next_step(operation_id,parent_id);
            return 1;
        case 2:
            //Search books
            sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            all_records_number = display_books(book_array);

            if(all_records_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);

            printf("\n(%d results found from %d books)\n%s",all_records_number,all_records_number,(all_records_number == 1 || all_records_number == 0) ? "" : "to search the current results enter ',' before search term\n");

            if(all_records_number == 0)
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
            printf("to display all book leave the search term empty or enter '-'\n");

            if(all_records_number == 1) {printf("\n==> edit current book (./edit)\n==> edit current book's copies (./copies)\n==> delete current book (./delete)");}
            printf("\n==> return to menu (./menu)");

            print_seprator(sep_size);
            while(1){
                results_number = search_books(book_array);
                if(results_number == -1) {load_menu(0,""); return;}
                else if(results_number == -2) {int book_index=current_book_index; insert_book(current_book_index); search_next_step(2,0,book_index,0,"Books"); results_number = 1;}
                else if(results_number == -3) {int book_index=current_book_index; edit_copies(current_book_index); search_next_step(2,0,book_index,1,"Books"); results_number = 1;}
                else if(results_number == -4) {
                    int book_index=current_book_index;
                    if(book_array[book_index].copies == book_array[book_index].current)
                    {
                        int book_index=current_book_index;
                        int youSure = are_you_sure(operation_id,parent_id,sep_size);
                        if(youSure)
                        {
                            delete_book(current_book_index);
                            go(operation_id,parent_id);
                        }
                        else
                        {
                            //book_delete_success = 0;
                            int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
                            display_book(current_book_index);
                            results_number = 1;

                            display_info("  Delete operation has been canceled  ","");
                        }
                    }else {
                        int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
                        display_book(current_book_index);
                        results_number = 1;

                        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                        printf("\n  There are %d copies from this book which are borrowed by library members  ",book_array[book_index].copies - book_array[book_index].current);
                        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    }

                }
                if(results_number == 0){
                    current_book_index = -1;
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                }
                printf("\n(%d results found from %d books)\n%s",results_number,all_records_number,(results_number == 1 || results_number == 0) ? "" : "to search the current results enter ',' before search term\n");

                if(results_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);

                printf("to display all book leave the search term empty or enter '-'\n");

                if(results_number == 1) {printf("\n==> edit current book (./edit)\n==> edit current book's copies (./copies)\n==> delete current book (./delete)");}
                printf("\n==> return to menu (./menu)");
                print_seprator(sep_size);
            }
            load_menu(0,"");
            return 1;
        /*case 3:
            //Add new copies
            sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);

            while(1){
                results_number = search_ISBN(book_array, menu_items[get_operation_index(operation_id)].value);

                if(results_number == 1){int book_index=current_book_index; edit_copies(current_book_index); search_next_step(2,0,book_index,0); results_number = 1;}
                else if(results_number == -2) {load_menu(0,""); return;}
                else if(results_number == -3) {}

                if(results_number == 0){
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                    printf("\n(Wrong ISBN)\n");
                }
                if(results_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);

                if(results_number == 1) {printf("\n==> Advanced search (./search)");}
                printf("\n==> return to menu (./menu)");
                print_seprator(sep_size);
            }
            load_menu(0,"");
            return 1;
        case 4:
            //Delete

            return 1;
        case 5:
            //Edit

            return 1;
        */
        case 6:
            load_menu(6,"");
            return 1;
        case 7:
            //Register new member
            operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            insert_member(-1);
            next_step(operation_id,parent_id);
            return 1;
        case 8:
            //Search members
            sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            all_records_number = display_members(member_array);

            if(all_records_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);

            printf("\n(%d results found from %d members)\n%s",all_records_number,all_records_number,(all_records_number == 1 || all_records_number == 0) ? "" : "to search the current results enter ',' before search term\n");

            if(all_records_number == 0)
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
            printf("to display all member leave the search term empty or enter '-'\n");

            if(all_records_number == 1) {printf("\n==> edit current member (./edit)\n==> delete current member (./delete)");}
            printf("\n==> return to menu (./menu)");

            print_seprator(sep_size);
            while(1){
                results_number = search_members(member_array);
                if(results_number == -1) {load_menu(6,""); return;}
                else if(results_number == -2) {int member_index=current_member_index; insert_member(current_member_index); search_next_step(8,6,member_index,0,"Members"); results_number = 1;}
                else if(results_number == -3) {
                    int member_index=current_member_index;
                    if(member_books_number(member_array[member_index].ID,-1) == 0)
                    {
                        int youSure = are_you_sure(operation_id,parent_id,sep_size);
                        if(youSure)
                        {
                            delete_member(current_member_index);
                            go(operation_id,parent_id);
                        }
                        else
                        {
                            //member_delete_success = 0;
                            int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
                            display_member(current_member_index);
                            results_number = 1;

                            display_info("  Delete operation has been canceled  ","");
                        }
                    }else {
                        int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
                        display_member(current_member_index);
                        results_number = 1;

                        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                        printf("\n  This member borrowed %d books and has not returned them yet!  ",member_books_number(member_array[member_index].ID,-1));
                        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    }

                }
                if(results_number == 0){
                    current_member_index = -1;
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                }
                printf("\n(%d results found from %d members)\n%s",results_number,all_records_number,(results_number == 1 || results_number == 0) ? "" : "to search the current results enter ',' before search term\n");

                if(results_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);

                printf("to display all member leave the search term empty or enter '-'\n");

                if(results_number == 1) {printf("\n==> edit current member (./edit)\n==> delete current member (./delete)");}
                printf("\n==> return to menu (./menu)");
                print_seprator(sep_size);
            }
            load_menu(6,"");
            return 1;
        case 9:
            load_menu(9,"");
            return 1;
        case 10:
            //Borrow
            operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            insert_borrow(-1);
            next_step(operation_id,parent_id);
            return 1;
        case 11:
            //Advanced_search
            sep_size = operation_header(parent_id, menu_items[get_operation_index(operation_id)].value);
            all_records_number = display_borrows(borrow_array);

            if(all_records_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);

            printf("\n(%d results found from %d borrows)\n%s",all_records_number,all_records_number,(all_records_number == 1 || all_records_number == 0) ? "" : "to search the current results enter ',' before search term\n");

            if(all_records_number == 0)
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);
            printf("to display all borrow leave the search term empty or enter '-'\n");

            if(all_records_number == 1) {printf("\n==> edit current borrow (./edit)\n==> edit date returned (./return)\n==> delete current borrow (./delete)");}
            printf("\n==> return to menu (./menu)");

            print_seprator(sep_size);
            while(1){
                results_number = search_borrows(borrow_array);
                if(results_number == -1) {load_menu(9,""); return;}
                else if(results_number == -2) {int borrow_index=current_borrow_index; insert_borrow(current_borrow_index); search_next_step(11,9,borrow_index,0,"borrows"); results_number = 1;}
                else if(results_number == -3) {int borrow_index=current_borrow_index; edit_return_date(current_borrow_index); search_next_step(11,9,borrow_index,1,"borrows"); results_number = 1;}
                else if(results_number == -4) {
                    int borrow_index=current_borrow_index;
                    int youSure = are_you_sure(operation_id,parent_id,sep_size);
                    if(youSure)
                    {
                        delete_borrow(current_borrow_index);
                        go(operation_id,parent_id);
                    }
                    else
                    {
                        //borrow_delete_success = 0;
                        int sep_size = operation_header(parent_id,"Advanced search (edit - delete)");
                        display_borrow(current_borrow_index);
                        results_number = 1;

                        display_info("  Delete operation has been canceled  ","");
                    }
                }
                if(results_number == 0){
                    current_borrow_index = -1;
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 79);
                }
                printf("\n(%d results found from %d borrows)\n%s",results_number,all_records_number,(results_number == 1 || results_number == 0) ? "" : "to search the current results enter ',' before search term\n");

                if(results_number == 0)
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7);

                printf("to display all borrow leave the search term empty or enter '-'\n");

                if(results_number == 1) {printf("\n==> edit current borrow (./edit)\n==> edit date returned (./return)\n==> delete current borrow (./delete)");}
                printf("\n==> return to menu (./menu)");
                print_seprator(sep_size);
            }
            load_menu(0,"");
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
