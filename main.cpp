#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "config.h"
#include "shape.h"

const int COLUMN = 8;
const int ROW = 18;

const int TOTAL_SHAPE = 6;
const int UNIQUE_SHAPE = 4;

// Function List
void game();
int randomInt(int min, int max);
void copyShape(char *first, char *second);

char MAP[ROW][COLUMN] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

class Shape
{
public:
  int col;
  int row;
  char matrix[4][4][4];
  int state = 0;

  Shape()
  {
    col = 3;
    row = 0;
    randomShape();
  }

  void randomShape()
  {
    int idx = randomInt(0, 6);
    printf("Gotted index : %d\n", idx);

    int uniqueLength = 4;
    printf("Unique length : %d\n", uniqueLength);

    for (int i = 0; i < uniqueLength; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        for (int k = 0; k < UNIQUE_SHAPE; k++)
        {
          // Debugging
          printf("idx : %d | i : %d | j : %d | k %d\n", idx, i, j, k);
          printf("[%c]\n", SHAPES[idx][i][j][k]);
          matrix[i][j][k] = SHAPES[idx][i][j][k];
        }
      }
    }
  }

  void clearPlayer()
  {
    for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < COLUMN; j++)
      {
        if (MAP[i][j] == '*')
        {
          printf("Clearing Player!");
          MAP[i][j] = ' ';
        }
      }
    }
  }

  void changeState()
  {
    state += 1;
    state %= UNIQUE_SHAPE;
  }

  void put()
  {
  }

  bool isLast(int x, int y)
  {
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        int currX = x + i;
        int bottom = y + j - 1;

        if (bottom < 0)
        {
          // printf("return true!");
          return true;
        }
        if (MAP[currX][bottom] == 'O')
        {
          // printf("return true!");
          return true;
        }
      }
    }
    // getchar();
    return false;
  }

  bool isIntersect(int x, int y)
  {
    printf("x : %d | y : %d", x, y);
    // printf("Check intersecting!");
    // getchar();
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        int currX = x + i;
        int currY = y + j;
        if (currX < 0 || currY < 0 || currX >= ROW || currY >= COLUMN)
        {
          return true;
        }
        if (MAP[i + x][j + y] == 'O')
        {
          // printf("return true!");
          return true;
        }
      }
    }
    // getchar();
    return false;
  }

  void render()
  {
    // int shapeLength = array_length(matrix[state][0]);
    // printf("Shap length now : %d\n", shapeLength);
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        char mapChar = MAP[i + row][j + col];
        char matrixChar = matrix[state][i][j];

        // validate is matrix
        if (mapChar == ' ' && matrix[state][i][j] != ' ')
        {
          MAP[i + row][j + col] = '*';
        }
      }
    }
  }

  void logic()
  {
    clearPlayer();
    render();
  }

  void move(char *str)
  {
    if (strcmp(str, "top") == 0 && !isIntersect(row - 1, col))
    {
      row -= 1;
    }
    if (strcmp(str, "left") == 0 && !isIntersect(row, col - 1))
    {
      col -= 1;
    }
    if (strcmp(str, "right") == 0 && !isIntersect(row, col + 1))
    {
      col += 1;
    }
    if (strcmp(str, "bottom") == 0 && !isIntersect(row + 1, col))
    {
      row += 1;
    }
  }
};

Shape *currentShape = NULL;

void init()
{
  srand(time(NULL));
}

int main()
{
  init();
  game();
}

void makePiece()
{
}

void printMap()
{
  system("cls");
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COLUMN; j++)
    {
      printf("%c", MAP[i][j]);
    }
    printf("\n");
  }
}

void generatePiece()
{
  currentShape = new Shape();
}

void game()
{
  printf("Generating Piece...\n");
  generatePiece();
  printMap();
  printf("masuk sini..");
  while (true)
  {

    char buffer;
    buffer = getch();
    printf("Getting Buffer[%c]\n", buffer);
    switch (buffer)
    {
    case 'd':
      if (currentShape)
        currentShape->move("right");
      break;
    case 'a':
      if (currentShape)
        currentShape->move("left");
      break;
    case 's':
      if (currentShape)
        currentShape->move("bottom");
      break;
    case ' ':
      if (currentShape)
        currentShape->changeState();
      break;
    }
    currentShape->logic();

    system("cls");
    printMap();
  }
}
