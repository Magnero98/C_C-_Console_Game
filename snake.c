#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int area[20][20];
int length = 5;

//struct for snake player
struct snake
{
    int x;
    int y;
};

//build up snake head and tail to represent their coordinate
struct snake head;
struct snake tail;

//creating snake move direction
enum Direction
{
    up, down, left, right
};
enum Direction dir;


//initializing arena to space and place the player in arena
void initialization()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            area[i][j] = -1;
        }
    }

    area[10][10] = 1;
    area[10][9] = 2;
    area[10][8] = 3;
    area[10][8] = 4;
    area[10][8] = 5;
}

void show()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(area[i][j] > -1)
            {
                printf("O");
            }
            else if(area[i][j] == -1)
            {
                printf(" ");
            }
            else if(area[i][j] == -2)
            {
                printf("#");
            }

            if((j + 1) % 20 == 0)
            {
                puts("");
            }
        }
    }
}

void cek_tail(int input)
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(input == length)
            {
                if(area[i][j] == input)
                {
                    area[i][j] = -1;

                    if(area[i - 1][j] == (length - 1))
                    {
                        tail.y--;
                    }
                    else if(area[i + 1][j] == (length - 1))
                    {
                        tail.y++;
                    }
                    else if(area[i][j - 1] == (length - 1))
                    {
                        tail.x--;
                    }
                    else if(area[i][j + 1] == (length - 1))
                    {
                        tail.x++;
                    }
                    printf("tail.x = %d\ntail.y = %d", tail.x, tail.y);

                    area[tail.y][tail.x] = input;

                    return;
                }
            }
            else
            {
                if(area[i][j] == input - 1)
                {
                    area[i][j] = input;
                    return;
                }
            }
        }
    }
}

void addTail(int input)
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(area[i][j] == (input - 1))
            {
                area[i][j] = input;
            }
        }
    }
}

void move()
{
    int i;

    if(dir == up)
    {
        if(area[head.y - 1][head.x] == -1)
        {
            //move the head to top;
            head.y--;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                cek_tail(i);
            }
        }
        else if(area[head.y - 1][head.x] == -2)
        {
            length++;

            head.y--;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                addTail(i);
            }
        }
    }
    else if(dir == down)
    {
        if(area[head.y + 1][head.x] == -1)
        {
            //move the head to bottom
            head.y++;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                cek_tail(i);
            }
        }
        else if(area[head.y + 1][head.x] == -2)
        {
            length++;

            head.y++;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                addTail(i);
            }
        }
    }
    else if(dir == left)
    {
        if(area[head.y][head.x - 1] == -1)
        {
            //move head to left
            head.x--;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                cek_tail(i);
            }
        }
        else if(area[head.y][head.x - 1] == -2)
        {
            length++;

            head.x--;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                addTail(i);
            }
        }
    }
    else if(dir == right)
    {
        if(area[head.y][head.x + 1] == -1)
        {
            //move head to right
            head.x++;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                cek_tail(i);
            }
        }
        else if(area[head.y][head.x + 1] == -2)
        {
            length++;

            head.x++;
            area[head.y][head.x] = 0;

            for(i = length; i >= 1; i--)
            {
                addTail(i);
            }
        }
    }
}

void cek_makan()
{
    int i, j, ada = 0, x, y;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(area[i][j] == -2)
            {
                ada = 1;
            }
        }
    }

    if(ada == 0)
    {
        do
        {
            x = rand() % 20;
            y = rand() % 20;
        }
        while(area[y][x] != -1);

        area[y][x] = -2;
    }
}

void control()
{
    char key;

    if(kbhit())
    {
        key = getch();

        switch(key)
        {
        case 'a':
            dir = left;
            break;
        case 's':
            dir = down;
            break;
        case 'd':
            dir = right;
            break;
        case 'w':
            dir = up;
            break;
        }
    }
}

int main()
{
    int x, y;

    srand(time(NULL));

    head.x = 10;
    head.y = 10;

    tail.x = 8;
    tail.y = 10;
    dir = right;

    initialization();

    do
    {
        x = rand() % 20;
        y = rand() % 20;
    }
    while(area[y][x] != -1);
    area[y][x] = -2;

    do
    {
        Sleep(300);
        system("cls");

        cek_makan();
        show();
        control();
        move();
    }
    while(1);

    return 0;
}
