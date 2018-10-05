#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct padi{
    char nama[20];
    int stock, price;
}nasi[100];

int Index = 0;
int i, j;
int income;

void baca_file(struct padi rice[100]){
    FILE *input;

    input = fopen("beras.txt", "r");

    if(input != NULL){
        while(!feof(input)){
            fscanf(input, "%[^#]#%d#%d\n", &nasi[Index].nama, &nasi[Index].stock, &nasi[Index].price);
            if(strlen( nasi[Index].nama )  > 1 ){
                Index++;
            }else{
                break;
            }
        }
    }

    fclose(input);
}

void add(){
    do{
        printf("Input Rice Name : ");
        scanf("%[^\n]s", &nasi[Index].nama);
        fflush(stdin);
    }while(strlen(nasi[Index].nama) < 5 || strlen(nasi[Index].nama) > 20);

    do{
        printf("Input Rice Stock : ");
        scanf("%d", &nasi[Index].stock);
        fflush(stdin);
    }while(nasi[Index].stock < 1 || nasi[Index].stock > 10);

    do{
        printf("Input Rice Price : ");
        scanf("%d", &nasi[Index].price);
        fflush(stdin);
    }while( nasi[Index].price < 1 );

    printf("Successfully added new rice : %s", nasi[Index].nama);
    Index++;

    getch();
}

int sell(int masukkan){
    for(i = 0; i < Index; i++){
        masukkan += nasi[i].price*nasi[i].stock;
        nasi[i].stock = 0;
    }
    printf("You have sold all rice and gained Rp.%d,-", masukkan);

    FILE *output;

    output = fopen("beras.txt", "w");

    fprintf(output,"%s", " ");

    fclose(output);

    for(i = 0; i < Index; i++){
        strcpy(nasi[i].nama, NULL);
    }

    Index = 0;

    return masukkan;
}

void sort(){
    int temp;
    char tempo[30];

    for(i = 0; i < Index-1; i++){
        for(j = Index-1; j > i; j--){
            if(nasi[j].price < nasi[j-1].price){
                temp = nasi[j].price;
                nasi[j].price = nasi[j-1].price;
                nasi[j-1].price = temp;

                strcpy(tempo, nasi[j].nama);
                strcpy(nasi[j].nama, nasi[j-1].nama);
                strcpy(nasi[j-1].nama, tempo);

                temp = nasi[j].stock;
                nasi[j].stock = nasi[j-1].stock;
                nasi[j-1].stock = temp;
            }
        }
    }
}

void save(){
    FILE *output;

    output = fopen("beras.txt", "w");

    if(output != NULL){
        for(i = 0; i < Index; i++){
            if(i != Index-1){
                fprintf(output, "%s#%d#%d\n", nasi[i].nama, nasi[i].stock, nasi[i].price);
            }else{
                fprintf(output, "%s#%d#%d", nasi[i].nama, nasi[i].stock, nasi[i].price);
            }
        }
    }

    fclose(output);
}

int interface(){
    int pilihan;

    do{
        system("cls");

        if( strlen(nasi[0].nama) > 1 ){
            printf("%-3s %-20s %-6s %-10s\n", "No.", "Rice Name", "Stock", "Price");
            puts("==========================================");
            for(i = 0; i < Index; i++){
                printf("%2d. %-20s %-6d %-10d\n", i+1, nasi[i].nama, nasi[i].stock, nasi[i].price);
            }
            puts("==========================================");
            printf("Total Income = Rp.%d,-\n\n\n", income);

            puts("Grosiran Rice Shop");
            puts("===================");
        }else{
            puts("No data Available");
        }
        puts("");
        puts("");

        printf("1. Add New Rice\n2. Sell Rice\n3. Sort Rice by Price Ascending\n4. Save\n5. Exit\n\n");
        puts("");
        printf("Enter Your Choice : ");
        scanf("%d", &pilihan);
        fflush(stdin);
    }while(pilihan < 1 || pilihan > 5);

    puts("");
    puts("");

    switch(pilihan){
    case 1:
        add();
        break;
    case 2:
        income = sell(income);
        break;
    case 3:
        sort();
        break;
    case 4:
        save();
        break;
    case 5:
        return 0;
    }
}

int main(){
    baca_file(&nasi[100]);

    do{
        if( !interface() ){
            break;
        }
    }while(1);

    getchar();
    return 0;
}
