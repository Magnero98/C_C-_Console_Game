#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

struct Point
{
    int x, y;
};

struct Tile
{
    int value;
    int distance;
    bool visited;

    struct Point thisCoor, prevCoor;

    struct Tile *prev, *next;
}*qhead = NULL, *qtail = NULL, *shead = NULL, *stail = NULL;

struct Tile *area[30][30];
int maps[30][30];
struct Tile *ahead, *temp;
struct Point start, finish;

//=====================================================================================//

void initialize()
{
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            //untuk lantai djikstra
            area[i][j] = (struct Tile*) malloc(sizeof(struct Tile));

            area[i][j] -> thisCoor.x = j;
            area[i][j] -> thisCoor.y = i;

            if(i == 0 || i == 29 || j == 0 || j == 29)
            {
                area[i][j] -> value = 999;
            }
            else
            {
                area[i][j] -> value = 1;
            }

            area[i][j] -> distance = 999;
            area[i][j] -> visited = false;

            area[i][j] -> prev = area[i][j] -> next = NULL;

            //untuk lantai yang akan ditampilkan
            maps[i][j] = 0;
        }
    }

    start.y = 3;
    start.x = 3;

    finish.y = 25;
    finish.x = 3;

    area[start.y][start.x] -> distance = 0;
    area[start.y][start.x] -> visited = true;

    maps[start.y][start.x] = 3;
    maps[finish.y][finish.x] = 5;
}

//=====================================================================================//

void obstacle()
{
    int x, y;
/*
    for(int i = 0; i < 100; i++)
    {
        x = rand() % 28 + 1;
        y = rand() % 28 + 1;

        if((x == start.x && y == start.y) || (x == finish.x && y == finish.y) || area[y][x] -> value != 1)
        {
            i--;
        }
        else
        {
            area[y][x] -> value = 999;
        }
    }
*/

    for(int i = 1; i < 28; i++)
    {
        area[5][i] -> value = 999;
    }

    for(int i = 5; i < 29; i++)
    {
        area[9][i] -> value = 999;
    }

    for(int i = 1; i < 26; i++)
    {
        area[13][i] -> value = 999;
    }

}

void pushQueue(struct Tile *node)
{
    if(qhead == NULL)
    {
        qhead = qtail = node;
    }
    else if(node -> distance < qhead -> distance)
    {
        qhead -> next = node;
        node -> prev = qhead;
        qhead = node;
    }
    else if(node -> distance >= qtail -> distance)
    {
        node -> next = qtail;
        qtail -> prev = node;
        qtail = node;
    }
    else
    {

        struct Tile *curr;
        curr = qhead;

        while(node -> distance >= curr -> distance)
        {
            curr = curr -> prev;
        }

        node -> next = curr -> next;
        curr -> next -> prev = node;
        node -> prev = curr;
        curr -> next = node;
    }
}

void pushStack(struct Tile *node)
{
    if(shead == NULL)
    {
        shead = stail = node;
    }
    else
    {
        shead -> next = node;
        node -> prev = shead;
        shead = node;
    }
}

void pop()
{
    if(qhead != NULL)
    {
        if(qhead == qtail)
        {
            qhead = qtail = NULL;
        }
        else
        {
            qhead = qhead -> prev;
            qhead -> next = NULL;
        }
    }
}

void popAll()
{
    struct Tile *curr;
    while(qhead != NULL)
    {
        curr = qhead;
        qhead = qhead -> prev;
        free(curr);
    }

    while(shead != NULL)
    {
        curr = shead;
        shead = shead -> prev;
        free(curr);
    }
}

void printMaps()
{
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if(i == start.y && j == start.x)
            {
                printf("S");
            }
            else if(i == finish.y && j == finish.x)
            {
                printf("E");
            }
            else if(area[i][j] -> value == 1)
            {
                printf(" ");
            }
            else if(area[i][j] -> value == 999)
            {
                printf("#");
            }
            else if(area[i][j] -> value == 2)
            {
                printf("+");
            }
            else if(area[i][j] -> value == 6)
            {
                printf("o");
            }
        }
        puts("");
    }
}

//=====================================================================================//

void djikstra(struct Tile *current)
{
    if(current -> thisCoor.x != finish.x || current -> thisCoor.y != finish.y)
    {
        ahead = area[current -> thisCoor.y - 1][current -> thisCoor.x];
        if(ahead -> visited == false)
        {
            int dist = (ahead -> value) + (current -> distance);

            if(dist < ahead -> distance)
            {
                ahead -> distance = dist;
                ahead -> prevCoor.x = current -> thisCoor.x;
                ahead -> prevCoor.y = current -> thisCoor.y;

                pushQueue(ahead);
            }
        }

        ahead = area[current -> thisCoor.y + 1][current -> thisCoor.x];
        if(ahead -> visited == false)
        {
            int dist = (ahead -> value) + (current -> distance);

            if(dist < ahead -> distance)
            {
                ahead -> distance = dist;
                ahead -> prevCoor.x = current -> thisCoor.x;
                ahead -> prevCoor.y = current -> thisCoor.y;

                pushQueue(ahead);
            }
        }

        ahead = area[current -> thisCoor.y][current -> thisCoor.x + 1];
        if(ahead -> visited == false)
        {
            int dist = (ahead -> value) + (current -> distance);

            if(dist < ahead -> distance)
            {
                ahead -> distance = dist;
                ahead -> prevCoor.x = current -> thisCoor.x;
                ahead -> prevCoor.y = current -> thisCoor.y;

                pushQueue(ahead);
            }
        }

        ahead = area[current -> thisCoor.y][current -> thisCoor.x - 1];
        if(ahead -> visited == false)
        {
            int dist = (ahead -> value) + (current -> distance);

            if(dist < ahead -> distance)
            {
                ahead -> distance = dist;
                ahead -> prevCoor.x = current -> thisCoor.x;
                ahead -> prevCoor.y = current -> thisCoor.y;

                pushQueue(ahead);
            }
        }
        system("cls");
        printMaps();

        temp = qhead;
        temp -> visited = true;
        area[temp -> thisCoor.y][temp -> thisCoor.x] -> value = 2;

        pop();
        djikstra(temp);
    }
}

void backtrack(struct Tile *current)
{
    if(current -> thisCoor.x != start.x || current -> thisCoor.y != start.y)
    {
        area[current -> thisCoor.y][current -> thisCoor.x] -> value = 6;
        backtrack(area[current -> prevCoor.y][current -> prevCoor.x]);
    }
}

//=====================================================================================//

int main()
{
    srand(time(NULL));

    initialize();
    obstacle();

    printMaps();
    getchar();

    djikstra(area[start.y][start.x]);
    backtrack(area[finish.y][finish.x]);

    system("cls");
    printMaps();
    getchar();
    return 0;
}
