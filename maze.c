#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>

struct Position
{
    int x;
    int y;
}player;

char arr[10][10];
int i, j;

void isi()
{
    arr[0][5] = 178;
    arr[1][9] = 178;
    arr[2][2] = 178;
    arr[3][1] = 178;
    arr[3][6] = 178;
    arr[3][7] = 178;
    arr[4][7] = 178;
    arr[4][3] = 178;
    arr[5][0] = 178;
    arr[6][2] = 178;
    arr[6][6] = 178;
    arr[7][5] = 178;
    arr[8][8] = 178;
    arr[9][3] = 178;
    arr[9][4] = 178;

    arr[9][0] = 2;
    arr[0][8] = 15;

    player.x = 0;
    player.y = 9;
}

void print()
{
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(j != 9)
            {
                printf("%c", arr[i][j]);
            }
            else
            {
                printf("%c\n", arr[i][j]);
            }
        }
    }
}

int cek_kiri()
{
    if(arr[player.y][player.x - 1] == ((char)178))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int kiri()
{
    while(cek_kiri() == 0)
    {
        Sleep(300);
        arr[player.y][player.x] = 0;
        player.x--;
        arr[player.y][player.x] = 2;
        system("cls");
        print();

        if(arr[0][8] == 2)
        {
            return 1;
        }
    }

    return 0;
}

int cek_kanan()
{
    if(arr[player.y][player.x + 1] == ((char)178))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int kanan()
{
    while(cek_kanan() == 0)
    {
        Sleep(300);
        arr[player.y][player.x] = 0;
        player.x++;
        arr[player.y][player.x] = 2;
        system("cls");
        print();

        if(arr[0][8] == 2)
        {
            return 1;
        }
    }

    return 0;
}

int cek_atas()
{
    if(arr[player.y - 1][player.x] == ((char)178))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int atas()
{
    while(cek_atas() == 0)
    {
        Sleep(300);
        arr[player.y][player.x] = 0;
        player.y--;
        arr[player.y][player.x] = 2;
        system("cls");
        print();

        if(arr[0][8] == 2)
        {
            return 1;
        }
    }

    return 0;
}

int cek_bawah()
{
    if(arr[player.y + 1][player.x] == ((char)178))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bawah()
{
    while(cek_bawah() == 0)
    {
        Sleep(300);
        arr[player.y][player.x] = 0;
        player.y++;
        arr[player.y][player.x] = 2;
        system("cls");
        print();

        if(arr[0][8] == 2)
        {
            return 1;
        }
    }
    return 0;
}

void move()
{
    char input;
    int result;

    print();
    do
    {
        puts("\n");
        printf("Input the direction : ");
        scanf("%c", &input);
        fflush(stdin);

        switch(input)
        {
        case 'a':
            result = kiri();
            if(result == 1)
            {
                return;
            }
            break;
        case 's':
            result = bawah();
            if(result == 1)
            {
                return;
            }
            break;
        case 'd':
            result = kanan();
            if(result == 1)
            {
                return;
            }
            break;
        case 'w':
            result = atas();
            if(result == 1)
            {
                return;
            }
            break;
        }
    }
    while(1);
}

void enter()
{
    puts("\n");
    printf("Press Enter to continue...");
    getchar();
}

int main()
{
    isi();
    move();
    system("cls");
    printf("\n\n\n\n                    YAY, YOU DID IT!");
    getchar();
    return 0;
}
