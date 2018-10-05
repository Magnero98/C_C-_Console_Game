#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

void tampilanAwal(char tanah_copy[10][10], int arr_copy[10][10]){
    int i=0, j=0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            tanah_copy[i][j]='0';
        }
    }
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            arr_copy[i][j]=0;
        }
    }
}

void placingBomb(int arr_copy[10][10]){
    int i,a,b;
    srand(time(NULL));
    for(i=0;i<10;i++){
        a=rand()%10;
        b=rand()%10;
        arr_copy[a][b]=-1;
    }
}

void calculate(int arr_copy[10][10]){
    int i,j,jumlah_bomb=0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){

            jumlah_bomb=0;

            if(arr_copy[i][j]==0){
                if(i-1>-1 && j-1>-1){
                    if(arr_copy[i-1][j-1]==-1){
                        jumlah_bomb++;
                    }
                }
                if(i-1>-1){
                    if(arr_copy[i-1][j]==-1){
                        jumlah_bomb++;
                    }
                }
                if(i-1>-1 && j+1<10){
                    if(arr_copy[i-1][j+1]==-1){
                        jumlah_bomb++;
                    }
                }
                if(j-1>-1){
                    if(arr_copy[i][j-1]==-1){
                        jumlah_bomb++;
                    }
                }
                if(j+1<10){
                    if(arr_copy[i][j+1]==-1){
                        jumlah_bomb++;
                    }
                }
                if(i+1<10 && j-1>-1){
                    if(arr_copy[i+1][j-1]==-1){
                        jumlah_bomb++;
                    }
                }
                if(i+1<10){
                    if(arr_copy[i+1][j]==-1){
                        jumlah_bomb++;
                    }
                }
                if(i+1<10 && j+1<10){
                    if(arr_copy[i+1][j+1]==-1){
                        jumlah_bomb++;
                    }
                }
            }else{
                continue;
            }
            arr_copy[i][j]=jumlah_bomb;
        }
    }
}

void print_array(char tanah_copy[10][10],int arr_copy[10][10]){
    int i,j;
    printf("       1  2  3  4  5  6  7  8  9  10\n");
    puts("     ________________________________");
    puts("    |                                |");
    for(i=0;i<10;i++){
        printf("%2d %2c",(i+1),'|');
        for(j=0;j<10;j++){
            printf("%3c",tanah_copy[i][j]);
        }
        printf("%3c %2d",'|',(i+1));
        puts("");
        if(i==9){
            puts("    |________________________________|");
        }else{
            puts("    |                                |");
        }

    }
    puts("");
    printf("       1  2  3  4  5  6  7  8  9  10\n");
    puts("");
    puts("");
}

void check_for_win(char tanah_copy[10][10],int *win){
    int i,j,jumlah;
    jumlah=0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(tanah_copy[i][j]==0){
                jumlah++;
            }
        }
    }
    if(jumlah==10){
        *win=1;
    }
}

void klik_tanah(int baris, int kolom, int arr_copy[10][10], char tanah_copy[10][10],int *kalah){
    if(tanah_copy[baris][kolom]!='0'){
        printf("This field had been opened, Go Choose another!");
        getchar();
    }else{
        if(arr_copy[baris][kolom]!=0 && arr_copy[baris][kolom]!=-1){
            tanah_copy[baris][kolom]=(arr_copy[baris][kolom])+'0';
        }else if(arr_copy[baris][kolom]==-1){
            tanah_copy[baris][kolom]='#';
            print_array(tanah_copy,arr_copy);
            *kalah=1;
        }else if(arr_copy[baris][kolom]==0){
            int i,j,k;

            arr_copy[baris][kolom]=-3;

            for(k=0;k<50;k++){
                for(i=0;i<10;i++){
                    for(j=0;j<10;j++){
                        if(arr_copy[i][j]==-3){
                            if(arr_copy[i-1][j]==0){
                                if(i-1>-1){
                                    arr_copy[i-1][j]=-3;
                                }
                            }

                            if(arr_copy[i][j-1]==0){
                                if(j-1>-1){
                                    arr_copy[i][j-1]=-3;
                                }
                            }
                            if(arr_copy[i][j+1]==0){
                                if(j+1<10){
                                    arr_copy[i][j+1]=-3;
                                }
                            }

                            if(arr_copy[i+1][j]==0){
                                if(i+1<10){
                                    arr_copy[i+1][j]=-3;
                                }
                            }
                        }
                    }
                }
            }
            for(i=0;i<10;i++){
                for(j=0;j<10;j++){
                    if(arr_copy[i][j]==-3){
                        tanah_copy[i][j]=' ';
                        if(i-1>-1){
                            if(arr_copy[i-1][j]!=-3){
                                tanah_copy[i-1][j]=arr_copy[i-1][j]+'0';
                            }
                        }
                        if(j-1>-1){
                            if(arr_copy[i][j-1]!=-3){
                                tanah_copy[i][j-1]=arr_copy[i][j-1]+'0';
                            }
                        }
                        if(j+1<10){
                            if(arr_copy[i][j+1]!=-3){
                                tanah_copy[i][j+1]=arr_copy[i][j+1]+'0';
                            }
                        }
                        if(i+1<10){
                            if(arr_copy[i+1][j]!=-3){
                                tanah_copy[i+1][j]=arr_copy[i+1][j]+'0';
                            }
                        }
                    }
                }
            }
        }
    }
}





int main(){
    int arr[10][10];
    char tanah[10][10];
    int row,col;
    int win=0,kalah=0;

    tampilanAwal(tanah,arr);
    placingBomb(arr);
    calculate(arr);
    do{
        system("cls");
        print_array(tanah,arr);
        scanf("%d %d",&row,&col);
        fflush(stdin);
        row--;
        col--;
        klik_tanah(row,col,arr,tanah,&kalah);
        check_for_win(tanah,&win);
        if(win==1){
            break;
        }
        if(kalah==1){
            break;
        }
    }while(1);
    if(win==1){
        puts("CONGRATULATION, YOU HAVE REACH THE END OF THE GAME!");
        puts("");
        puts("Thank you!");
        getchar();
    }
    if(kalah==1){
        printf("GOTCHA! You Chose A BIG BOMB!\n");
        puts("You FAILED!\n\n\n");
        puts("GAME OVER");
        getchar();
    }
    return 0;
}
