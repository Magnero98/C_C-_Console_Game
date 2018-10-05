#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int i, j;
int Index = 0;
unsigned int income = 0;

typedef struct
{
    char name[100];
    char type[100];
    char size[100];
    int price,stock;
}burger;

burger roti[100],temp;

void read()
{
    FILE *input;

    input = fopen("burger.txt", "r");

    if(input != NULL)
    {
        fscanf(input, "%d\n", &income);
        while(!feof(input))
        {
            fscanf(input, "%[^#]#%[^#]#%[^#]#%d#%d\n", &roti[Index].name, &roti[Index].type, &roti[Index].size, &roti[Index].price, &roti[Index].stock);
            Index++;
        }
    }

    fclose(input);
}

void resume()
{
    puts("\n");
    printf("Press Enter to continue...");
    getchar();
}

int cek(char key[100])
{
    int ada;

    for(i = 0; i < Index; i++)
    {
        if(strcmp(roti[i].name, key) == 0)
        {
            ada = 1;
            return ada;
        }
    }

    return 0;
}

void make()
{
    int oke;
    char yn;
    char keyword[100];

    system("cls");

    if(Index < 10)
    {
        do
        {
            do
            {
                oke = 0;

                printf("Please type the Burger's Name [max 20 characters] : ");
                scanf("%[^\n]s", &keyword);
                fflush(stdin);

                oke = cek(keyword);

                if(oke == 1)
                {
                    printf("This Burger's Name has already been taken!\nPlease Choose Another name\n");
                }

                puts("");
            }
            while(strlen(keyword) < 1 || strlen(keyword) > 20 || oke == 1);

            strcpy(roti[Index].name, keyword);

            do
            {
                printf("Please type the Burger's Size [small/Medium/LARGE] : ");
                scanf("%s", &roti[Index].size);
                fflush(stdin);

                puts("");
            }
            while(strcmp(roti[Index].size, "small") != 0 && strcmp(roti[Index].size, "Medium") != 0 && strcmp(roti[Index].size, "LARGE") != 0);

            do
            {
                printf("Please type the Burger's Type [original/thin crust/hot n spicy] : ");
                scanf("%[^\n]s", &roti[Index].type);
                fflush(stdin);

                puts("");
            }
            while(strcmp(roti[Index].type, "original") != 0 && strcmp(roti[Index].type, "thin crust") != 0 && strcmp(roti[Index].type, "hot n spicy") != 0);

            do
            {
                printf("Please type the Burger's current Stock [1-20] : ");
                scanf("%d", &roti[Index].stock);
                fflush(stdin);

                puts("");
            }
            while(roti[Index].stock < 1 || roti[Index].stock > 20);

            do
            {
                printf("Please type the Burger's Price [10000-50000] : ");
                scanf("%d", &roti[Index].price);
                fflush(stdin);

                puts("");
            }
            while(roti[Index].price < 10000 || roti[Index].price > 50000);

            system("cls");

            printf("Burger's Name      : %s\n\n", roti[Index].name);
            printf("Burger's Type      : %s\n\n", roti[Index].type);
            printf("Burger's Size      : %s\n\n", roti[Index].size);
            printf("Burger's Stock     : %d\n\n", roti[Index].stock);
            printf("Burger's Price     : %d\n\n\n", roti[Index].price);

            do
            {
                printf("Does The Data Shown Above correct [y = yes, n = no] ? ");
                scanf("%c", &yn);
                fflush(stdin);
            }
            while(yn != 'y' && yn != 'n');
        }
        while(yn == 'n');

        Index++;

        puts("Data Succesfully Added!");
    }
    else
    {
        puts("You have no Space for the Burger Right Now!\n\nGo Sell Some First!");
    }

    resume();
}

void display()
{
    system("cls");

    if(Index > 0)
    {
        puts("[===========================================================================================================================]");
        printf("[| %-4s %-1c %-20s %-1c %-20s %-1c %-20s %-1c %-20s %-1c %-20s |]\n", "No.", '|', "Burger's Name", '|', "Burger's Size", '|', "Burger's Type", '|', "Burger's Price", '|', "Burger's Stock");
        puts("[===========================================================================================================================]");
        for( i = 0; i < Index; i++)
        {
            printf("[| %-4d %-1c %-20s %-1c %-20s %-1c %-20s %-1c %-20d %-1c %-20d |]\n", i+1, '|', roti[i].name, '|', roti[i].size, '|', roti[i].type, '|', roti[i].price, '|', roti[i].stock);
        }
        puts("[===========================================================================================================================]");
    }
    else
    {
        puts("               NO DATA AVAILABLE\n");
    }
}

void sell()
{
    int pilihan;
    int ukur;

    if(Index > 0)
    {
        do
        {
            display();

            printf("\nInput HERE [1-%d] : ", Index);
            scanf("%d", &pilihan);
            fflush(stdin);
        }
        while(pilihan < 1 || pilihan > Index);

        pilihan--;

        if(strcmp(roti[pilihan].size, "small") == 0)
        {
            ukur = 1;
        }
        else if(strcmp(roti[pilihan].size, "Medium") == 0)
        {
            ukur = 2;
        }
        else
        {
            ukur = 3;
        }

        income += roti[pilihan].price * roti[pilihan].stock * strlen(roti[pilihan].type) * ukur;

        printf("The %s Burger, has been sold!\n", roti[Index].name);

        for(i = pilihan; i < Index; i++)
        {
            roti[i] = roti[i+1];
        }

        Index--;
    }
    else
    {
        system("cls");

        printf("You Have no Burger to sell");
    }

    resume();
}

void sort_p()
{
    for(i = 0; i < Index; i++)
    {
        for(j = Index-1; j > i; j--)
        {
            if(roti[j].price < roti[j-1].price)
            {
                temp = roti[j];
                roti[j] = roti[j-1];
                roti[j-1] = temp;
            }
        }
    }
}

void sort_n()
{
    for(i = 0; i < Index; i++)
    {
        for(j = Index-1; j > i; j--)
        {
            if(strcmp(roti[j].name, roti[j-1].name) < 0)
            {
                temp = roti[j];
                roti[j] = roti[j-1];
                roti[j-1] = temp;
            }
        }
    }
}

void sort()
{
    int pilihan;

    puts("");

    do
    {
        printf("1. Sort Ascending by Name\n2. Sort Descending by Price\n\n");
        scanf("%d", &pilihan);
        fflush(stdin);
    }
    while( pilihan < 1 || pilihan > 2);

    switch(pilihan)
    {
    case 1:
        sort_n();
        break;
    case 2:
        sort_p();
        break;
    }

    printf("\n\nSort SUCCESSFULL!");
    resume();
}

void in()
{
    system("cls");

    puts("                          INCOME\n\n");

    if(income > 0)
    {
        printf("CONGRATS, YOUR CURRENT MONEY IS %d\n\n", income);
        printf("Go make Burger and make MONEY!\n\n");

    }
    else
    {
        printf("You don't have any money right now\nDon't worry, you can make it by selling Burger\n\n");
    }

    resume();
}

void save()
{
    FILE *output;

    output = fopen("burger.txt", "w");

    fprintf(output, "%d\n", income);

    for(i = 0; i < Index; i++)
    {
        if(i != Index-1)
        {
            fprintf(output, "%s#%s#%s#%d#%d\n", roti[i].name, roti[i].type, roti[i].size, roti[i].price, roti[i].stock);
        }
        else
        {
            fprintf(output, "%s#%s#%s#%d#%d", roti[i].name, roti[i].type, roti[i].size, roti[i].price, roti[i].stock);
        }
    }

    fclose(output);

    printf("Save Successful!\n");

    resume();
}

void inface()
{
    int pilihan;

    do
    {
        do
        {
            system("cls");

            display();

            puts("1. Make a Burger\n2. Sell the Burger\n3. Sort the Burger's List\n4. Show Income\n5. Save & Exit\n\n");
            printf("Input HERE [1-5] : ");
            scanf("%d", &pilihan);
            fflush(stdin);
        }
        while(pilihan < 1 || pilihan > 5);

        switch(pilihan)
        {
        case 1:
            make();
            break;
        case 2:
            sell();
            break;
        case 3:
            sort();
            break;
        case 4:
            in();
            break;
        case 5:
            save();
            return;
        }
    }
    while(1);
}

int main()
{
    read();

    inface();

    system("cls");
    printf("\n\n\n\n                                    GOOD BYE!");
    getchar();
    return 0;
}
