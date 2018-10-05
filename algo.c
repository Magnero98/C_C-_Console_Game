#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int i,j;
int keluar = 0;
int Index;
char temp[20];

struct food{
    char name[20];
    int price;
    int stock;
};
struct food makanan[10];



void sort_name(){
	//char temp[40];
	int temp1, temp2;

	for(i=0; i<Index; i++){
		for(j=Index-1; j>i; j--){
			if(strcmp(makanan[j].name,makanan[j-1].name)<0){
				strcpy(temp, makanan[j].name);
				temp1 = makanan[j].price;
				temp2 = makanan[j].stock;

				strcpy(makanan[j].name, makanan[j-1].name);
				makanan[j].price = makanan[j-1].price;
				makanan[j].stock = makanan[j-1].stock;

				strcpy(makanan[j-1].name, temp);
				makanan[j-1].price = temp1;
				makanan[j-1].stock = temp2;
			}
		}
	}
}

void sort_price(){
	//char temp[40];
	int temp1, temp2;

	for(i=0; i<Index; i++){
		for(j=Index-1; j>i; j--){
			if(makanan[j].price<makanan[j-1].price){
				strcpy(temp, makanan[j].name);
				temp1 = makanan[j].price;
				temp2 = makanan[j].stock;

				strcpy(makanan[j].name, makanan[j-1].name);
				makanan[j].price = makanan[j-1].price;
				makanan[j].stock = makanan[j-1].stock;

				strcpy(makanan[j-1].name, temp);
				makanan[j-1].price = temp1;
				makanan[j-1].stock = temp2;
			}
		}
	}
}

void sort_stock(){
	//char temp[40];
	int temp1, temp2;

	for(i=0; i<Index; i++){
		for(j=Index-1; j>i; j--){
			if(makanan[j].stock<makanan[j-1].stock){
				strcpy(temp, makanan[j].name);
				temp1 = makanan[j].price;
				temp2 = makanan[j].stock;

				strcpy(makanan[j].name, makanan[j-1].name);
				makanan[j].price = makanan[j-1].price;
				makanan[j].stock = makanan[j-1].stock;

				strcpy(makanan[j-1].name, temp);
				makanan[j-1].price = temp1;
				makanan[j-1].stock = temp2;
			}
		}
	}
	puts("");
	puts("Sorting SUCCESSFULL\n\nPress any key to continue...");
	getch();
}

void tambah_menu(){
	//char temp[30];
	char nama[30];
	int lama = 0, add;

	printf("Please Enter The food's name : ");
	scanf("%[^\n]s",&nama);
	fflush(stdin);

	for(i=0;i<Index;i++){
	    puts(nama);
	    puts(makanan[i].name);
        if(strcmp(nama, makanan[i].name)==0){
            lama=1;
            break;
        }
	}
	printf("lama %d",lama);

	printf("Index = %d\n\n",Index);
	if(lama==1){
		printf("How many stock do you want to add : ");
		scanf("%d",&add);
		fflush(stdin);

		makanan[i].stock+=add;

		printf("Index = %d\n\n",Index);
		puts("");
		puts("");
		printf("Congrats, The Stock has been added!");
		puts("");

	}else{
		strcpy(makanan[Index].name,nama);
		puts("");
		printf("Please enter the price : ");
		scanf("%d",&makanan[Index].price);
		fflush(stdin);
		puts("");
		printf("Please enter the stock : ");
		scanf("%d",&makanan[Index].stock);
		fflush(stdin);

		Index++;
		printf("Index = %d\n\n",Index);
		puts("");
		puts("");
		printf("Congrats, The new Menu has been added!");
		puts("");
	}
    printf("press any key to continue...");
    getch();
}

void sorting(){
	int pilihan;


	do{
        system("cls");
        printf("Choose the type of sorting :\n\n1. Name Sorting\n2. Price Sorting\n3. Stock Sorting\n4. Main Menu\n\n");
        printf("Your Choice is : ");
        scanf("%d", &pilihan);
        fflush(stdin);

        switch(pilihan){
        case 1:
            sort_name();
            break;
        case 2:
            sort_price();
            break;
        case 3:
            sort_stock();
            break;
        case 4:
            return;
        }
	}while(pilihan<1 || pilihan>4);
}

void cetak(){
    puts("                      LIST MENU                 ");
    puts("");
    puts("=======================================================+");
    printf("%-3s %-3c %-20s %-3c %-8s %-3c %-8s %c\n","No.",'|',"FOODS",'|',"PRICE",'|',"STOCK",'|');
    puts("=======================================================+");
    for(i=0;i<Index;i++){
        if(i!=Index-1){
            printf("%-3d %-3c %-20s %-3c %-8d %-3c %-8d %-1c\n",i+1,'|',makanan[i].name,'|',makanan[i].price,'|',makanan[i].stock,'|');
        }else{
            printf("%-3d %-3c %-20s %-3c %-8d %-3c %-8d %-1c\n",i+1,'|',makanan[i].name,'|',makanan[i].price,'|',makanan[i].stock,'|');
            puts("-------------------------------------------------------+");
        }
    }
    puts("");
    getch();
}

void print_pesanan(char namanya[100][20], int harganya[100], int kuantitasnya[100], int jumlah){
    int total=0;

    system("cls");
    puts("          $           Here is your Bill            $");
    puts("");
    puts("");
    puts("");
    puts("                     TAKOSUKI RESTAURANT");
    puts("                    HOT LINE 088808880888");
    puts("");
    puts("                         EASTERN FOODS");
    puts("                  Jl. Anggrek Cakra 5 No.50");
    puts("");
    puts("");
    printf("=======================================================+\n");
    printf("%-20s   %-3c%-10s   %-3c%-10s   %c\n","Nama Produk",'|',"Jumlah",'|',"Harga",'|');
    printf("=======================================================+\n");
    for(i=0;i<jumlah;i++){
        printf("%-20s   %-3c%-10d   %-3cRp.%-10d%c\n",namanya[i],'|', kuantitasnya[i],'|',harganya[i]*kuantitasnya[i],'|');
        total+=harganya[i]*kuantitasnya[i];
    }
    printf("-------------------------------------------------------+\n");
    printf("%-20s                   %-3cRp.%-10d%c\n","Total Harga",'|',total,'|');
    printf("=======================================================+\n");
    puts("");
    puts("");
    puts("                     ...THANK YOU...\n\n");
    getch();
}

void pesan(){
    char nama_makan[100][20];
    int quantity[100];
    int harga[100];
    int ada;
    int jumlahPesan=0;



    puts("");
    puts("");
    do{
        ada=0;
		int tampung=0;

        system("cls");

        printf("What do You want to order :\n");

        printf("%-2d. Food Name : ",jumlahPesan+1);
        scanf("%[^\n]", &temp);
        fflush(stdin);
        strcpy(nama_makan[jumlahPesan],temp);
        do{
            printf("    Quantity  : ");
            scanf("%d",&quantity[jumlahPesan]);
            fflush(stdin);
            puts("");
        }while(quantity[jumlahPesan] < 1);

        for(j=0;j<Index;j++){
            if(strstr(nama_makan[jumlahPesan],makanan[j].name)!=NULL && makanan[j].stock>0){
                harga[jumlahPesan]=makanan[j].price;

				if(makanan[j].stock < quantity[jumlahPesan]){
                    ada=-1;
                    break;
				}else if(makanan[j].stock >= quantity[jumlahPesan]){
				    makanan[j].stock-=quantity[jumlahPesan];
                    ada=1;
                    break;
				}
            }
        }

        if(ada==1){
            jumlahPesan++;
        }else if(ada==-1){
            printf("SORRY, OUR %s STOCK IS INSUFFICIENT\n\nWE ONLY HAVE %d PORTION OF %s\n\n",makanan[j].name,makanan[j].stock,makanan[j].name);
        }else{
            puts("SORRY, WE DON'T HAVE THAT KIND OF FOOD\n");
        }

        printf("Do you still want to order [y/n]? ");
        if(getchar()=='n'){
            break;
        }
        fflush(stdin);

    }while(1);

    system("cls");

    if(jumlahPesan!=0){
        print_pesanan(nama_makan,harga,quantity,jumlahPesan);
    }else{
        puts("");
        puts("You Haven't done any order yet! Go order some foods!");
    }
    getchar();
}

void hapus_menu(){
    int pilihan;

    cetak();

    printf("Choose the number of menu which you want to delete : ");
    scanf("%d",&pilihan);
    fflush(stdin);

    for(i=pilihan-1;i<Index;i++){
        if(i!=Index-1){
            strcpy(makanan[i].name,makanan[i+1].name);
            makanan[i].price=makanan[i+1].price;
            makanan[i].stock=makanan[i+1].stock;
        }
    }

    Index--;
    system("cls");

    puts("Here is The New Menu");
    puts("");
    puts("");
    cetak();
    puts("");
    puts("");
    printf("Press any key to continue...");
    getch();
}

void save(){
    FILE *output;

    puts("Preparing to overwrite...");

    output = fopen("menu.txt","w");

    for(i=0;i<Index;i++){
        fprintf(output,"%s@",makanan[i].name);
        fprintf(output,"%d@",makanan[i].price);
        if(i!=Index-1){
            fprintf(output,"%d\n\r",makanan[i].stock);
        }else{
            fprintf(output,"%d",makanan[i].stock);
        }
    }

    puts("Save is in the progress");
    puts("Please Wait...");
    puts("Please Wait...");
    fclose(output);

    puts("");
    printf("SAVE SUCESSFULL\n\n\n");
    printf("press any key to continue...");
    getch();
}
int searching(){
    char keyword[30];

    printf("Type food's name here [to check if the food is available] : ");
    scanf("%[^\n]s",&keyword);
    fflush(stdin);

    for(i=0;i<Index;i++){
        if(strcmp(makanan[i].name, keyword) == 0){
            return 1;
        }
    }

    return 0;
}

int mulai(){
    do{
        int pilihan=0;

        system("cls");

        printf("                  Hi, Welcome to Restaurant TAKOSUKI's Program\n");
        puts("");
        puts("");
        puts("                   _______ _____ _  _  ____  _____ _    _ _  _  _");
        puts("                  |__   __|  _  | |/ /| __ |/ ____| |  | | |/ /| |");
        puts("                     | |  | |_| |   | ||__||\\____ \\ |__| |   | | |");
        puts("                     |_|  |_| |_|_|\\_\\|____|\\_____/______/_|\\_\\|_|\n");
        puts("");
        puts("");
        printf("1. Show Restaurant's Menu\n2. Order from Menu\n3. Add a New Menu / Food Stock\n4. Remove an Old Menu\n5. Save Changes\n6. Sorting\n7. Searching\n8. Exit Program\n\n\n");

        puts("");

        printf("Please let me know what do you want me to do :\n");
        printf("Your Choice[1..6]: ");
        scanf("%d",&pilihan);
        fflush(stdin);

        switch(pilihan){
        case 1:
            system("cls");
            cetak();
            break;
        case 2:
            system("cls");
            pesan();
            break;
        case 3:
            system("cls");
            tambah_menu();
            break;
        case 4:
            system("cls");
            hapus_menu();
            break;
        case 5:
            system("cls");
            save();
            break;
        case 6:
            sorting();
            break;
        case 7:
            do{
                system("cls");
                puts("");
                puts("");
                if(searching()==1){
                    puts("The food which you are looking for is available now!");
                }else{
                    puts("Sorry, we could not find that kind of food");
                }
                getchar();
                puts("Do you want to search for another food [y/n]? ");
            }while(getch()=='y');
            break;
        case 8:
            return 0;
        }
    }while(1);
}

int read(int *out){
    FILE *input;

    input = fopen("menu.txt","r");

	if(input==NULL){
		printf("There is no such a file");
		*out = 1;
		return 0;
	}else{
		while(!feof(input)){
			fscanf(input,"%[^@]@%d@%d\n",&makanan[Index].name,&makanan[Index].price,&makanan[Index].stock);
			Index++;
		}
	}
    fclose(input);
}

int main(){
    read(&keluar);
	if(keluar==1){
		getchar();
		return 0;
	}

    mulai();

    return 0;
}
