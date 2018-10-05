#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

struct collection
{
    char name[50];
    char code[10];
    char author[20];
    char status[10];
    char borrow_by[30];
    char lifetime[10];
} book[100], temp, kosong;

int Index = 0, i, j;


//READ THE TEXT FILE
void baca()
{
    FILE *input;

    input = fopen( "book.txt", "r");

    if( input != NULL )
    {
        while( !feof( input ) )
        {
            fscanf(input, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", &book[Index].name, &book[Index].code, &book[Index].author, &book[Index].status, &book[Index].borrow_by, &book[Index].lifetime);
            Index++;
        }
    }

    fclose(input);
}

void search_new()
{
    char temp[30];
    char kosong[10];

    for(i = 0; i < Index; i++)
    {
        if(strstr(book[i].lifetime, "NEW") != NULL)
        {
            strcpy(book[i].lifetime, "[New]");
        }
        else if(strstr(book[i].lifetime, "New") != NULL)
        {
            strcpy(book[i].lifetime, "[new]");
        }
        else if(strstr(book[i].lifetime, "new") != NULL)
        {
            strcpy(book[i].lifetime, "-");
        }
    }
}

//HERE ARE SOME METHODS TO PRINT LIST OF BOOK'S COLLECTION

//PRINT LIST METHOD FOR SEARCHING
void print_list(char key[30])
{
    char temp[30];

    puts("[========================================================================================================================]");
    printf("[| %-4s %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", "No.", '|', "Book's Name", '|', "Shelf's Code", '|', "Book's Author", '|', "Status", "|]");
    puts("[========================================================================================================================]");

    for(i = 0; i < Index; i++)
    {
        if(strstr(book[i].name, key) != NULL)
        {
            if(strchr(book[i].lifetime, '-') == NULL)
            {
                strcpy(temp, book[i].lifetime);
                strcat(temp, " ");
                strcat(temp, book[i].name);
                printf("[| %-4d %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", i+1, '|', temp, '|', book[i].code, '|', book[i].author, '|', book[i].status, "|]");
            }
            else
            {
                printf("[| %-4d %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", i+1, '|', book[i].name, '|', book[i].code, '|', book[i].author, '|', book[i].status, "|]");
            }
        }
    }

    puts("[========================================================================================================================]");
}

//PRINT BOOK METHOD
void book_list()
{
    char local_temp[50];

    if( Index != 0 )
    {
        puts("[========================================================================================================================]");
        printf("[| %-4s %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", "No.", '|', "Book's Name", '|', "Shelf's Code", '|', "Book's Author", '|', "Status", "|]");
        puts("[========================================================================================================================]");

        for(i = 0; i < Index; i++)
        {
            if(strstr(book[i].lifetime, "-") == NULL)
            {
                strcpy(local_temp, book[i].lifetime);
                strcat(local_temp, " ");
                strcat(local_temp, book[i].name);
                printf("[| %-4d %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", i+1, '|', local_temp, '|', book[i].code, '|', book[i].author, '|', book[i].status, "|]");
            }
            else
            {
                printf("[| %-4d %-1c %-50s %-1c %-15s %-1c %-20s %-1c %-15s %-2s\n", i+1, '|', book[i].name, '|', book[i].code, '|', book[i].author, '|', book[i].status, "|]");
            }
        }

        puts("[========================================================================================================================]");
    }
}

//HERE ARE SOME METHODS OF menu1

//FIRST METHOD OF MENU1
void sort_name()
{
    printf("Start The sorting process now [y/n]? ");
    if(getch() == 'y')
    {
        for(i = 0; i < (Index - 1); i++)
        {
            for(j = (Index - 1); j > i; j--)
            {
                if(strcmp(book[j].name, book[j-1].name) < 0)
                {
                    memcpy(&temp, &book[j-1], sizeof(temp));
                    memcpy(&book[j-1], &book[j], sizeof(book[j-1]));
                    memcpy(&book[j], &temp, sizeof(book[j]));
                }
            }
        }
        puts("\n\nSorting COMPLETE");
        getch();
    }
    else
    {
        return;
    }
}

//SECOND METHOD OF MENU1
void sort_author()
{
    printf("Start The sorting process now [y/n]? ");
    if(getch() == 'y')
    {
        for(i = 0; i < (Index - 1); i++)
        {
            for(j = (Index - 1); j > i; j--)
            {
                if(strcmp(book[j].author, book[j-1].author) < 0)
                {
                    memcpy(&temp, &book[j-1], sizeof(temp));
                    memcpy(&book[j-1], &book[j], sizeof(temp));
                    memcpy(&book[j], &temp, sizeof(temp));
                }
            }
        }
        puts("\n\nSorting COMPLETE");
        getch();
    }
    else
    {
        return;
    }
}

// THIRD METHOD OF MENU1
void new_book()
{
    printf("Start The sorting process now [y/n]? ");
    if(getch() == 'y')
    {
        for(i = 0; i < Index; i++)
        {
            if( strstr(book[i].lifetime, "NEW") != NULL )
            {
                memcpy(&temp, &book[0], sizeof(temp));
                memcpy(&book[0], &book[i], sizeof(temp));
                memcpy(&book[i], &temp, sizeof(temp));
            }
            else if( strstr(book[i].lifetime, "New") != NULL )
            {
                memcpy(&temp, &book[1], sizeof(temp));
                memcpy(&book[1], &book[i], sizeof(temp));
                memcpy(&book[i], &temp, sizeof(temp));
            }
            else if( strstr(book[i].lifetime, "new") != NULL )
            {
                memcpy(&temp, &book[2], sizeof(temp));
                memcpy(&book[2], &book[i], sizeof(temp));
                memcpy(&book[i], &temp, sizeof(temp));
            }
        }

        puts("\n\nSorting COMPLETE");
        getch();
    }
    else
    {
        return;
    }
}

void availability()
{
    for(i = 3, j = 3; i < (Index - 1); i++)
    {
        if( book[i].status == "Available" )
        {
            memcpy(&temp, &book[j], sizeof(temp));
            memcpy(&book[j], &book[i], sizeof(temp));
            memcpy(&book[i], &temp, sizeof(temp));
            j++;
        }
    }
}

//FOURTH METHOD OF MENU1
void find_book()
{
    char huruf;
    char keyword[20];
    int key_i = 0;

    printf("Start Searching now [y/n]? ");

    if(getch() == 'y')
    {
        do{
            system("cls");

            print_list(keyword);

            puts("Please enter the keyword first!");
            printf(keyword);
            huruf = getch();
            if(isprint(huruf))
            {
                keyword[key_i] = huruf;
                key_i++;
                continue;
            }
            else
            {
                break;
            }
        }while(1);
    }
}

//HERE ARE SOME MEHTODS OF menu2

// FIRST METHOD OF MENU2
void borrow()
{
    int pilihan;
    char person[30];

    do
    {
        book_list();
        puts("\n");

        printf("Which book that you want to borrow [1..%d] : ", Index);
        scanf("%d", &pilihan);
        fflush(stdin);
    }while( pilihan < 1 || pilihan > Index);

    if(strcmp(book[pilihan-1].status, "Available") == 0)
    {
        printf("\n\nThe %s Book is now Available now!\n\n",book[pilihan].name);
        printf("Please Enter your name first[1..20] : ");
        scanf("%[^\n]s", &person);
        fflush(stdin);
        strcpy(book[pilihan-1].borrow_by, person);
        strcpy(book[pilihan-1].status, "-");

        puts("\n\n");
        printf("Congrats %s! You have successful to borrow this book\nPlease take care of this book\n\nTHANK YOU!");
    }
    else
    {
        printf("This book is unavailable now\n\nFrom the last information, %s has borrowed this book", book[pilihan-1].borrow_by);
    }
    getchar();
}

// SECOND METHOD OF MENU2
void returning()
{
    char name[40];
    int found = 0;

    do
    {
        system("cls");
        book_list();
        puts("\n\n");
        printf("Please enter the book's name : ");
        scanf("%[^\n]s", &name);
        fflush(stdin);
        puts("");

        for(i = 0; i < Index; i++)
        {
            if(strcmp(book[i].name, name) == 0)
            {
                strcpy(book[i].borrow_by, "-");
                strcpy(book[i].status, "Available");
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            puts("The %s Book is NOT FOUND\n\nPlease make sure that you typed the correct name");
            getchar();
            continue;
        }
        else
        {
            printf("Thank You %s, Come Back Soon", book[i].borrow_by);
            getchar();
            break;
        }
    }while(1);
}

// HERE ARE SOME MENU IN menu3() METHOD

//FIRST METHOD OF MENU3
void add_book()
{
    char temp[30];
    char temp1[5];
    int temp_val;

    srand( time( NULL ) );

    book_list();
    puts("\n");

    search_new();

    printf("Please Enter the New Book's Name : ");
    scanf("%[^\n]s", &book[Index].name);
    fflush(stdin);
    strcpy(book[Index].lifetime, "[NEW]");
    puts("");

    printf("Please Enter the Author's Name : ");
    scanf("%[^\n]s", &book[Index].author);
    fflush(stdin);
    puts("");

    temp_val = (rand() % 1000 );

    //make a copy of book name to temp variable
    strcpy(temp, book[Index].name);
    strlwr(temp);

    //for shelf alphabetic code

    strncpy(book[Index].code, book[Index].name, 1); //for first letter of shelf code
    strncat(book[Index].code, book[Index].author, 1);   //for second letter of shelf code

    //for shelf numeric code
    itoa(temp_val, temp1, 10);
    itoa(Index, temp, 10);

    strcat(book[Index].code, temp1);                    //for next digit of shelf code
    strcat(book[Index].code, temp);                     //for the last digit of shelf code

    strupr(book[Index].code);                           //make all the letter in it be UPPERCASE

    strcpy(book[Index].status, "Available");

    strcpy(book[Index].borrow_by, "-");

    Index++;
}

// SECOND METHOD OF MENU3
void remove_book()
{
    int pilihan;

    book_list();

    puts("");
    puts("");

    printf("Please Enter the Book's Index that you want to remove [1..%d]: ", Index);
    scanf("%d", &pilihan);
    fflush(stdin);

    for(i = (pilihan - 1 ); i < Index; i++)
    {
        if(i != (Index-1))
        {
            temp = book[i];
            book[i] = book [i+1];
            book[i+1] = temp;
        }
        else
        {
            book[i] = kosong;
            Index--;
        }
    }
}

void menu1()
{
    int pilihan;

    do
    {
        system("cls");

        book_list();
        puts("\n");

        printf("1. Sort by Book's Name\n2. Sort by Author's Name\n3. Show the New Book\n4. Search Book\n5. Main Menu\n\n\n");
        printf("Input here[1..5] : ");
        scanf("%d", &pilihan);
        fflush(stdin);

        switch(pilihan)
        {
        case 1:
            system("cls");
            sort_name();
            break;
        case 2:
            system("cls");
            sort_author();
            break;
        case 3:
            system("cls");
            new_book();
            break;
        case 4:
            system("cls");
            find_book();
            break;
        case 5:
            return;
        }
    }while(1);
}

void menu2()
{
    int pilihan;

    do
    {
        system("cls");

        printf("1. Borrow Book\n2. Return Book\n3. Main Menu\n\n");
        printf("Input here[1..3] : ");
        scanf("%d", &pilihan);
        fflush(stdin);

        switch(pilihan)
        {
        case 1:
            system("cls");
            borrow();
            break;
        case 2:
            system("cls");
            returning();
            break;
        case 3:
            return;
        }
    }while(1);
}

void menu3()
{
    int pilihan;

    do
    {
        system("cls");

        printf("1. Add New Book\n2. Remove Book from List\n3. Main Menu\n\n\n");
        printf("Input here[1..3] : ");
        scanf("%d", &pilihan);
        fflush(stdin);
        puts("\n\n");
    }while(pilihan < 0 || pilihan > 3);

    switch(pilihan)
    {
    case 1:
        system("cls");
        add_book();
        break;
    case 2:
        system("cls");
        remove_book();
        break;
    case 3:
        return;
    }
}

void tulis()
{
    FILE *output;

    output = fopen("book.txt", "w");

    for(i = 0; i < Index; i++)
    {
        fprintf(output, "%s#%s#%s#%s#%s#%s\n", book[i].name, book[i].code, book[i].author, book[i].status, book[i].borrow_by, book[i].lifetime);
    }

    fclose(output);
}

void interface()
{
    int inputan;
    do
    {
        do
        {
            system("cls");
            printf("1. Book Collection\n2. Borrow/Return\n3. Edit Book List\n4. Save Changes\n5. Exit Program\n\n\n");
            printf("Input here [1..4] : ");
            scanf("%d", &inputan);
            fflush(stdin);
        }while( inputan < 1 || inputan > 5);

        //MASUK PADA PILIHAN MENU SELANJUTNYA

        switch(inputan)
        {
        case 1:
            system("cls");
            menu1();
            break;
        case 2:
            system("cls");
            menu2();
            break;
        case 3:
            system("cls");
            menu3();
            break;
        case 4:
            tulis();
            break;
        case 5:
            return;
        }
    }while(1);
}


int main()
{
    baca();
    interface();
    return 0;
}
