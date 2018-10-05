#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

struct Data
{
    int fCost, gCost, hCost, cost, x, y;
    bool visited;
    struct Data *prev, *left, *right;
}*head, *tail;

struct Data *area[30][30];
int targetX, targetY, startX, startY;

void placeMine()
{
    int x, y;

    for(int i = 0; i < 100; i++)
    {
        x = rand() % 30;
        y = rand() % 30;
        if(area[y][x] -> cost != 99 && (x != startX && y != startY) && (x != targetX && y != targetY))
        {
            area[y][x] -> cost = 99;
        }
        else
        {
            i--;
        }
    }
}

void initialize()
{
    targetX = 1;
    targetY = 2;

    startX = 18;
    startY = 27;

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            area[i][j] = (struct Data *)malloc(sizeof(struct Data));

            if(i == 0 || i == 29 || j == 0 || j == 29 || (i == 5 && j < 15) || (i == 8 && j > 5) || (i == 11 && j < 15) || (i == 15 && j > 5) || (i == 21 && j < 26))
                area[i][j] -> cost = 99;
            else
                area[i][j] -> cost = 1;


            area[i][j] -> hCost = (abs(targetX - j) + abs(targetY - i));
            area[i][j] -> gCost = area[i][j] -> fCost = 0;
            area[i][j] -> x = j;
            area[i][j] -> y = i;
            area[i][j] -> visited = false;
            area[i][j] -> prev = NULL;
        }
    }

    placeMine();
}

void push(int x, int y)
{
    area[y][x] -> left = area[y][x] -> right = NULL;

    if(head == NULL)
    {
        head = tail = area[y][x];
    }
    else if(area[y][x] -> fCost < head -> fCost)
    {
        head -> left = area[y][x];
        area[y][x] -> right = head;
        head = area[y][x];
    }
    else if(area[y][x] -> fCost >= tail -> fCost)
    {
        tail -> right = area[y][x];
        area[y][x] -> left = tail;
        tail = area[y][x];
    }
    else
    {
        struct Data *temp;
        temp = head;
        while(temp -> fCost <= area[y][x] -> fCost)
        {
            temp = temp -> right;
        }

        area[y][x] -> left = temp -> left;
        temp -> left -> right = area[y][x];
        area[y][x] -> right = temp;
        temp -> left = area[y][x];
    }
}

void pop()
{
    if(head != NULL)
    {
        if(head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            head = head -> right;
            head -> left = NULL;
        }
    }
}

void pop(int x, int y)
{
    if(head != NULL)
    {
        if(head == tail && head -> x == x && head -> y == y)
        {
            head = tail = NULL;
        }
        else if(head -> x == x && head -> y == y)
        {
            head = head -> right;
            head -> left = NULL;
        }
        else if(tail -> x == x && tail -> y == y)
        {
            tail = tail -> left;
            tail -> right = NULL;
        }
        else
        {
            struct Data *temp = head;

            while(temp != NULL)
            {
                if(temp -> x == x && temp -> y == y)
                {
                    temp -> left -> right = temp -> right;
                    temp -> right -> left = temp -> left;
                    temp -> left = temp -> right = NULL;
                    break;
                }
                temp = temp -> right;
            }
        }
    }
}

void print()
{
    system("cls");
    for(int i = 0; i < 30; i++)
    {
        //printf("|");
        for(int j = 0; j < 30; j++)
        {
            if(i != 0 && i != 29 && j != 0 && j != 29)
            {
                if(i == startY && j == startX)
                {
                    printf("S");
                }
                else if(i == targetY && j == targetX)
                {
                    printf("E");
                }
                else if(area[i][j] -> cost == -1)
                {
                    printf(".");
                }
                else if(area[i][j] -> visited == true)
                {
                    printf("-");
                }
                else if(area[i][j] -> visited == false)
                {
                    if(area[i][j] -> cost != 99)
                        printf(" ");
                    else
                        printf("#");
                }
            }
        }
        printf("\n");
    }
}

void printList()
{
    int i = 1;
    struct Data *temp;
    temp = head;
    while(temp != NULL)
    {
        printf("%d. Node -> fCost = %d, x = %d, y = %d\n", i, temp -> fCost, temp -> x, temp -> y);
        temp = temp -> right;
        i++;
    }
}

void showPath()
{
    struct Data *temp = area[targetY][targetX];
    while(temp != area[startY][startX])
    {
        temp -> cost = -1;
        temp = temp -> prev;
    }
}

void findPath(int x, int y)
{
    struct Data *curr, *next;
    int gCost;

    curr = area[y][x];
    curr -> visited = true;
    pop();

    if(curr != area[targetY][targetX])
    {
        next = area[y][x - 1];
        if(next -> visited == false)
        {
            gCost = curr -> gCost + next -> cost;

            if(next -> prev == NULL || gCost < next -> gCost)
            {
                if(gCost < next -> gCost)
                {
                    pop(next -> x, next -> y);
                }

                next -> gCost = gCost;
                next -> fCost = next -> gCost + next -> hCost;
                next -> prev = area[y][x];
                push(next -> x, next -> y);
                puts("1");
            }
        }

        next = area[y][x + 1];
        if(next -> visited == false)
        {
            gCost = curr -> gCost + next -> cost;

            if(next -> prev == NULL || gCost < next -> gCost)
            {
                if(gCost < next -> gCost)
                {
                    pop(next -> x, next -> y);
                }

                next -> gCost = gCost;
                next -> fCost = next -> gCost + next -> hCost;
                next -> prev = area[y][x];
                push(next -> x, next -> y);
                puts("2");
            }
        }

        next = area[y - 1][x];
        if(next -> visited == false)
        {
            gCost = curr -> gCost + next -> cost;

            if(next -> prev == NULL || gCost < next -> gCost)
            {
                if(gCost < next -> gCost)
                {
                    pop(next -> x, next -> y);
                }

                next -> gCost = gCost;
                next -> fCost = next -> gCost + next -> hCost;
                next -> prev = area[y][x];
                push(next -> x, next -> y);
                puts("3");
            }
        }

        next = area[y + 1][x];
        if(next -> visited == false)
        {
            gCost = curr -> gCost + next -> cost;

            if(next -> prev == NULL || gCost < next -> gCost)
            {
                if(gCost < next -> gCost)
                {
                    pop(next -> x, next -> y);
                }

                next -> gCost = gCost;
                next -> fCost = next -> gCost + next -> hCost;
                next -> prev = area[y][x];
                push(next -> x, next -> y);
                puts("3");
            }
        }

        print();
        //Sleep(100);

        findPath(head -> x, head -> y);

    }
}

int main()
{
    srand(time(NULL));
    initialize();

    print();

    findPath(startX, startY);
    showPath();
    print();

    return 0;
}

