#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int area[20][20];
int value = 0;

struct POINT
{
  int x;
  int y;
};

enum DIRECTION
{
    up, down, left, right
};

enum DIRECTION hor = right;
enum DIRECTION ver = up;

struct POINT player;
struct POINT ball;

void initialize()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(i == 0 || i == 19)
            {
                area[i][j] = 1;
            }
            else
            {
                if(j == 0 || j == 19)
                {
                    area[i][j] = 1;
                }
            }
        }
    }

    player.y = 18;
    player.x = 10;
    area[player.y][player.x] = 8;
    area[player.y][player.x - 1] = 8;
    area[player.y][player.x + 1] = 8;

    ball.y = 10;
    ball.x = 10;
    area[ball.y][ball.x] = 5;
}

void print()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(area[i][j] == 1)
            {
                printf("%c ", '#');
            }
            else if(area[i][j] == 0)
            {
                printf("%c ", ' ');
            }
            else if(area[i][j] == 5)
            {
                printf("%c ", 'o');
            }
            else if(area[i][j] == 8)
            {
                printf("%c ", '=');
            }
            else if(area[i][j] == 4)
            {
                printf("%c ", 178);
            }

            if(j == 19)
            {
                puts("");
            }
        }
    }
}

void input()
{
    if(_kbhit())
    {
        char ch = getch();

        switch(ch)
        {
        case 'a':
            if(area[player.y][player.x - 2] == 0)
            {
                area[player.y][player.x + 1] = 0;
                player.x--;
                area[player.y][player.x] = 8;
                area[player.y][player.x - 1] = 8;
                area[player.y][player.x + 1] = 8;
            }
            break;
        case 'd':
            if(area[player.y][player.x + 2] == 0)
            {
                area[player.y][player.x - 1] = 0;
                player.x++;
                area[player.y][player.x] = 8;
                area[player.y][player.x - 1] = 8;
                area[player.y][player.x + 1] = 8;
            }
            break;
        }
    }
}

void ballMove()
{
    switch(hor)
    {
    case left:
        if(area[ball.y][ball.x - 1] != 0)
        {
            if(area[ball.y][ball.x - 1] == 4)
            {
                area[ball.y][ball.x - 1] = 0;
                value++;
            }
            area[ball.y][ball.x] = 0;
            ball.x++;
            hor = right;
        }
        else
        {
            area[ball.y][ball.x] = 0;
            ball.x--;
        }
        break;
    case right:
        if(area[ball.y][ball.x + 1] != 0)
        {
            if(area[ball.y][ball.x + 1] == 4)
            {
                area[ball.y][ball.x + 1] = 0;
                value++;
            }
            area[ball.y][ball.x] = 0;
            ball.x--;
            hor = left;
        }
        else
        {
            area[ball.y][ball.x] = 0;
            ball.x++;
        }
        break;
    }

    switch(ver)
    {
    case up:
        if(area[ball.y - 1][ball.x] != 0)
        {
            if(area[ball.y - 1][ball.x] == 4)
            {
                area[ball.y - 1][ball.x] = 0;
                value++;
            }
            area[ball.y][ball.x] = 0;
            ball.y++;
            ver = down;
        }
        else
        {
            area[ball.y][ball.x] = 0;
            ball.y--;
        }
        break;
    case down:
        if(area[ball.y + 1][ball.x] != 0)
        {
            if(area[ball.y + 1][ball.x] == 4)
            {
                area[ball.y + 1][ball.x] = 0;
                value++;
            }
            area[ball.y][ball.x] = 0;
            ball.y--;
            ver = up;
        }
        else
        {
            area[ball.y][ball.x] = 0;
            ball.y++;
        }
        break;
    }

    area[ball.y][ball.x] = 5;
}

void brickGen()
{
    int a, b;
    int i = 0;

    do
    {
        a = (rand() % 19) + 1;
        b = (rand() % 5) + 1;

        if(area[b][a] == 0)
        {
            area[b][a] = 4;
            i++;
        }
    }
    while(i < 40);
}

int main()
{
    initialize();
    srand(time(NULL));
    brickGen();

    do
    {
        print();
        printf("| POINT = %d |", value);
        ballMove();
        input();
        Sleep(300);
        system("cls");
    }
    while(1);

    return 0;
}
