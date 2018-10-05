#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WALL 10
#define EMPTY 0
#define BRICK 3
#define BLOCK 2

//=========================================================================//

struct Point
{
    int x, y;
}p[4], mid;

enum blockForm
{
    LINE, BOX, LL, RL, S, Z
}Shape;

int currForm = 1;
int height;

//=========================================================================//

int area[30][20];

void initialize()
{
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(i == 29 || j == 0 || j == 19)
            {
                area[i][j] = WALL;
            }
            else
            {
                area[i][j] = EMPTY;
            }
        }
    }
}

void printArea()
{
    system("cls");

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(area[i][j] == WALL || i == 0)
            {
                printf("#");
            }
            else if(area[i][j] == EMPTY)
            {
                printf(" ");
            }
            else if(area[i][j] == BLOCK)
            {
                printf("O");
            }
            else if(area[i][j] == BRICK)
            {
                printf("X");
            }
        }

        puts("");
    }

    printf("MID X: %d\nMID Y: %d\n\n", mid.x, mid.y);
}

//=========================================================================//

void setLine()
{
    p[0].y = 0;
    p[0].x = 9;

    p[1].y = -1;
    p[1].x = 9;

    p[2].y = -2;
    p[2].x = 9;

    p[3].y = -3;
    p[3].x = 9;

    mid.x = p[1].x;
    mid.y = p[1].y;
}

void setBox()
{
    p[0].y = 0;
    p[0].x = 9;

    p[1].y = 0;
    p[1].x = 10;

    p[2].y = -1;
    p[2].x = 9;

    p[3].y = -1;
    p[3].x = 10;

    mid.x = p[3].x;
    mid.y = p[3].y;
}

void setRL()
{
    p[0].y = 0;
    p[0].x = 9;

    p[1].y = 0;
    p[1].x = 10;

    p[2].y = -1;
    p[2].x = 9;

    p[3].y = -2;
    p[3].x = 9;

    mid.x = p[3].x;
    mid.y = p[3].y;
}

void setLL()
{
    p[0].y = 0;
    p[0].x = 9;

    p[1].y = 0;
    p[1].x = 8;

    p[2].y = -1;
    p[2].x = 9;

    p[3].y = -2;
    p[3].x = 9;

    mid.x = p[3].x;
    mid.y = p[3].y;
}

void setS()
{
    p[0].y = 0;
    p[0].x = 8;

    p[1].y = 0;
    p[1].x = 9;

    p[2].y = -1;
    p[2].x = 9;

    p[3].y = -1;
    p[3].x = 10;

    mid.x = p[3].x;
    mid.y = p[3].y;
}

void setZ()
{
    p[0].y = 1;
    p[0].x = 9;

    p[1].y = 1;
    p[1].x = 10;

    p[2].y = 0;
    p[2].x = 9;

    p[3].y = 0;
    p[3].x = 8;

    mid.x = p[3].x;
    mid.y = p[3].y;
}

//=========================================================================//

void clearPrev()
{
    for(int i = 0; i < 4; i++)
    {
        if(p[i].y > 0)
        {
            area[p[i].y][p[i].x] = EMPTY;
        }
    }
}

void fillBlock()
{
    for(int i = 0; i < 4; i++)
    {
        if(p[i].y > 0)
        {
            area[p[i].y][p[i].x] = BLOCK;
        }
    }
}

void fillBrick()
{
    for(int i = 0; i < 4; i++)
    {
        if(p[i].y > 0)
        {
            area[p[i].y][p[i].x] = BRICK;
        }
    }
}

void getShape()
{
    int random = rand() % 6;

    Shape = (blockForm)random;
}

void setCoord()
{
    switch(Shape)
    {
    case LINE:
        setLine();
        break;
    case BOX:
        setBox();
        break;
    case LL:
        setLL();
        break;
    case RL:
        setRL();
        break;
    case S:
        setS();
        break;
    case Z:
        setZ();
        break;
    }
}

//=========================================================================//

int validLeft()
{
    int valid = 1;

    for(int i = 0; i < 4; i++)
    {
        if(area[p[i].y][p[i].x - 1] == BRICK || area[p[i].y][p[i].x - 1] == WALL)
        {
            valid = 0;
            break;
        }
    }

    return valid;
}

int validRight()
{
    int valid = 1;

    for(int i = 0; i < 4; i++)
    {
        if(area[p[i].y][p[i].x + 1] == BRICK || area[p[i].y][p[i].x + 1] == WALL)
        {
            valid = 0;
            break;
        }
    }

    return valid;
}

//=========================================================================//

void changeForm()
{
    int valid = 1;

    switch(Shape)
    {
    case LINE:
        if(currForm == 1 || currForm == 3)
        {
            for(int i = mid.y - 2; i <= mid.y + 1; i++)
            {
                if(area[i][mid.x] == WALL || area[i][mid.x] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.y - 2; i < 4; i++, j++)
                {
                    p[i].x = mid.x;
                    p[i].y = j;
                }

                fillBlock();
            }
        }
        else
        {
            for(int i = mid.x - 1; i <= mid.x + 2; i++)
            {
                if(area[mid.y][i] == WALL || area[mid.y][i] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.x - 1; i < 4; i++, j++)
                {
                    p[i].x = j;
                    p[i].y = mid.y;
                }

                fillBlock();
            }
        }

        break;
    case RL:
        switch(currForm)
        {
        case 1:
            for(int i = mid.y - 1; i <= mid.y + 1; i++)
            {
                if(area[i][mid.x] == WALL || area[i][mid.x] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y + 1][mid.x + 1] == WALL || area[mid.y + 1][mid.x + 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.y - 1; i < 3; i++, j++)
                {
                    p[i].x = mid.x;
                    p[i].y = j;
                }

                p[3].y = mid.y + 1;
                p[3].x = mid.x + 1;

                fillBlock();
            }

            break;
        case 2:
            for(int i = mid.x - 1; i <= mid.x + 1; i++)
            {
                if(area[mid.y][i] == WALL || area[mid.y][i] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y + 1][mid.x - 1] == WALL || area[mid.y + 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.x - 1; i < 3; i++, j++)
                {
                    p[i].x = j;
                    p[i].y = mid.y;
                }

                p[3].y = mid.y + 1;
                p[3].x = mid.x - 1;

                fillBlock();
            }

            break;
        case 3:
            for(int i = mid.y - 1; i <= mid.y + 1; i++)
            {
                if(area[i][mid.x] == WALL || area[i][mid.x] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y - 1][mid.x - 1] == WALL || area[mid.y - 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.y - 1; i < 3; i++, j++)
                {
                    p[i].x = mid.x;
                    p[i].y = j;
                }

                p[3].y = mid.y - 1;
                p[3].x = mid.x - 1;

                fillBlock();
            }

            break;
        case 4:
            for(int i = mid.x - 1; i <= mid.x + 1; i++)
            {
                if(area[mid.y][i] == WALL || area[mid.y][i] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y - 1][mid.x + 1] == WALL || area[mid.y - 1][mid.x + 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.x - 1; i < 3; i++, j++)
                {
                    p[i].x = j;
                    p[i].y = mid.y;
                }

                p[3].y = mid.y - 1;
                p[3].x = mid.x + 1;

                fillBlock();
            }

            break;
        }

        break;
    case LL:
        switch(currForm)
        {
        case 1:
            for(int i = mid.y - 1; i <= mid.y + 1; i++)
            {
                if(area[i][mid.x] == WALL || area[i][mid.x] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y + 1][mid.x - 1] == WALL || area[mid.y + 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.y - 1; i < 3; i++, j++)
                {
                    p[i].x = mid.x;
                    p[i].y = j;
                }

                p[3].y = mid.y + 1;
                p[3].x = mid.x - 1;

                fillBlock();
            }

            break;
        case 2:
            for(int i = mid.x - 1; i <= mid.x + 1; i++)
            {
                if(area[mid.y][i] == WALL || area[mid.y][i] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y - 1][mid.x - 1] == WALL || area[mid.y - 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.x - 1; i < 3; i++, j++)
                {
                    p[i].x = j;
                    p[i].y = mid.y;
                }

                p[3].y = mid.y - 1;
                p[3].x = mid.x - 1;

                fillBlock();
            }

            break;
        case 3:
            for(int i = mid.y - 1; i <= mid.y + 1; i++)
            {
                if(area[i][mid.x] == WALL || area[i][mid.x] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y - 1][mid.x + 1] == WALL || area[mid.y - 1][mid.x + 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.y - 1; i < 3; i++, j++)
                {
                    p[i].x = mid.x;
                    p[i].y = j;
                }

                p[3].y = mid.y - 1;
                p[3].x = mid.x + 1;

                fillBlock();
            }

            break;
        case 4:
            for(int i = mid.x - 1; i <= mid.x + 1; i++)
            {
                if(area[mid.y][i] == WALL || area[mid.y][i] == BRICK)
                {
                    valid = 0;
                    break;
                }
            }

            if(area[mid.y + 1][mid.x + 1] == WALL || area[mid.y + 1][mid.x + 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                for(int i = 0, j = mid.x - 1; i < 3; i++, j++)
                {
                    p[i].x = j;
                    p[i].y = mid.y;
                }

                p[3].y = mid.y + 1;
                p[3].x = mid.x + 1;

                fillBlock();
            }

            break;
        }

        break;
    case S:
        if(currForm == 1 || currForm == 3)
        {
            if(area[mid.y][mid.x] == WALL || area[mid.y][mid.x + 1] == WALL || area[mid.y][mid.x] == BRICK || area[mid.y][mid.x + 1] == BRICK)
            {
                valid = 0;
            }
            if(area[mid.y + 1][mid.x] == WALL || area[mid.y + 1][mid.x - 1] == WALL || area[mid.y + 1][mid.x] == BRICK || area[mid.y + 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                p[0].y = p[1].y = mid.y;
                p[0].x = mid.x;
                p[1].x = mid.x + 1;

                p[2].y = p[3].y = mid.y + 1;
                p[2].x = mid.x;
                p[3].x = mid.x - 1;

                fillBlock();
            }
        }
        else
        {
            if(area[mid.y][mid.x - 1] == WALL || area[mid.y - 1][mid.x - 1] == WALL || area[mid.y][mid.x - 1] == BRICK || area[mid.y - 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }
            if(area[mid.y][mid.x] == WALL || area[mid.y + 1][mid.x] == WALL || area[mid.y][mid.x] == BRICK || area[mid.y + 1][mid.x] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                p[0].x = p[1].x = mid.x - 1;
                p[0].y = mid.y;
                p[1].y = mid.y - 1;

                p[2].x = p[3].x = mid.x;
                p[2].y = mid.y;
                p[3].y = mid.y + 1;

                fillBlock();
            }
        }
        break;
    case Z:
        if(currForm == 1 || currForm == 3)
        {
            if(area[mid.y][mid.x] == WALL || area[mid.y][mid.x - 1] == WALL || area[mid.y][mid.x] == BRICK || area[mid.y][mid.x - 1] == BRICK)
            {
                valid = 0;
            }
            if(area[mid.y + 1][mid.x] == WALL || area[mid.y + 1][mid.x + 1] == WALL || area[mid.y + 1][mid.x] == BRICK || area[mid.y + 1][mid.x + 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                p[0].y = p[1].y = mid.y;
                p[0].x = mid.x;
                p[1].x = mid.x - 1;

                p[2].y = p[3].y = mid.y + 1;
                p[2].x = mid.x;
                p[3].x = mid.x + 1;

                fillBlock();
            }
        }
        else
        {
            if(area[mid.y][mid.x] == WALL || area[mid.y - 1][mid.x] == WALL || area[mid.y][mid.x] == BRICK || area[mid.y - 1][mid.x] == BRICK)
            {
                valid = 0;
            }
            if(area[mid.y][mid.x - 1] == WALL || area[mid.y + 1][mid.x - 1] == WALL || area[mid.y][mid.x - 1] == BRICK || area[mid.y + 1][mid.x - 1] == BRICK)
            {
                valid = 0;
            }

            if(valid)
            {
                clearPrev();

                p[0].x = p[1].x = mid.x - 1;
                p[0].y = mid.y;
                p[1].y = mid.y + 1;

                p[2].x = p[3].x = mid.x;
                p[2].y = mid.y;
                p[3].y = mid.y - 1;

                fillBlock();
            }
        }

        break;
    }
}

//=========================================================================//

void towerHeight()
{
    for(int i = 1; i < 29; i++)
    {
        for(int j = 1; j < 19; j++)
        {
            if(area[i][j] == BRICK)
            {
                height = 28 - (i + 1);
                return;
            }
        }
    }
}

int checkBrick()
{
    int counter = 0;
    int full = 1;
    int clears = 0;

    towerHeight();

    for(int i = 28; i > height; i--)
    {
        full = 1;

        for(int j = 1; j < 19; j++)
        {
            if(clears)
            {
                area[i][j] = EMPTY;
                if(j == 18)
                {
                    clears = 0;
                    system("cls");

                    printArea();
                }
            }
            else if(area[i][j] != BRICK)
            {
                full = 0;
                break;
            }
        }

        if(full)
        {
            counter++;
            i++;
            clears = 1;
        }
    }

    return counter;
}

void moveDown()
{
    int counter = checkBrick();
    printArea();
    int none = 1;
    int fills = 0;

    towerHeight();

    for(int i = 28, k = 1; i < height; i--)
    {
        none = 1;

        for(int j = 1; j < 19; j++)
        {
            if(fills)
            {
                area[i][j] = area[i - k][j];
                if(j == 18)
                {
                    fills = 0;
                    k++;
                    system("cls");
                    printArea();
                }
            }
            else if(area[i][j] != EMPTY)
            {
                none = 0;
                break;
            }
        }

        if(none)
        {
            i++;
            fills = 1;
        }
    }
}

void fall()
{
    int hitGround = 0;

    clearPrev();

    for(int i = 0; i < 4; i++)
    {
        if(area[p[i].y + 1][p[i].x] == BRICK || area[p[i].y + 1][p[i].x] == WALL)
        {
            hitGround = 1;
            break;
        }
    }

    if(hitGround)
    {
        fillBrick();

        moveDown();

        Shape = (blockForm)1;
        //getShape();
        setCoord();
        fillBlock();
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            p[i].y++;
        }
        mid.y++;

        fillBlock();
    }
}

//=========================================================================//

void move()
{
    if(kbhit())
    {
        char input = getch();

        switch(input)
        {
        case 'a':
            if(validLeft())
            {
                clearPrev();

                for(int i = 0; i < 4; i++)
                {
                    p[i].x--;
                }

                mid.x--;

                fillBlock();
            }

            break;
        case 's':
            fall();

            break;
        case 'd':
            if(validRight())
            {
                clearPrev();

                for(int i = 0; i < 4; i++)
                {
                    p[i].x++;
                }

                mid.x++;

                fillBlock();
            }

            break;
        case 'w':
            currForm++;

            if(currForm > 4)
            {
                currForm = 1;
            }

            changeForm();

            break;
        }
    }
}

//=========================================================================//

int main()
{
    srand(time(NULL));

    initialize();
    printArea();

    Shape = (blockForm)1;
    setCoord();
    fillBlock();

    do
    {
        printArea();
        move();
        move();
        move();
        Sleep(100);
        fall();
    }
    while(1);

    getchar();
    return 0;
}
