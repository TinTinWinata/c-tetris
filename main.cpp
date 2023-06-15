#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "config.h"
#include "shape.h"
#include <windows.h>

// Variable List
const int COLUMN = 18;
const int ROW = 18;

const int TOTAL_SHAPE = 6;
const int UNIQUE_SHAPE = 4;
bool GAME_LOSE = false;
const int OFFSET_MAP = 1;
const int INITIAL_SPAWN_X = COLUMN / 2;
const int INITIAL_SPAWN_Y = 1;
const int INCREMENTED_SCORE = 500;
int SCORE = 0;
int FRAME = 0;
int TOTAL_FRAME_TO_MOVE = 30;

// Function Prototype
void forceCls();
void game();
int randomInt(int min, int max);
void copyShape(char *first, char *second);
void splice(int idx);
void checkWin();
void printMap();
void winSound();
void moveSound();
void gameLose();
void checkMoving();
void endScreen();

char MAP[ROW + 2][COLUMN + 2] =
    {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
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
    col = INITIAL_SPAWN_X;
    row = INITIAL_SPAWN_Y;
    randomShape();
    render();
  }

  void randomShape()
  {
    int idx = randomInt(0, 5);
    int uniqueLength = 4;
    for (int i = 0; i < uniqueLength; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        for (int k = 0; k < UNIQUE_SHAPE; k++)
        {
          // ! Debugging Commend
          // printf("idx : %d | i : %d | j : %d | k %d\n", idx, i, j, k);
          // printf("[%c]\n", SHAPES[idx][i][j][k]);

          matrix[i][j][k] = SHAPES[idx][i][j][k];
        }
      }
    }
    if (isIntersect(row, col, false))
    {
      GAME_LOSE = true;
      printMap();
      // gameLose();
    }
  }

  void clearPlayer()
  {
    for (int i = 1; i <= ROW; i++)
    {
      for (int j = 1; j <= COLUMN; j++)
      {
        if (MAP[i][j] == '*')
        {
          MAP[i][j] = ' ';
        }
      }
    }
  }

  void changeState()
  {
    if (!isIntersect(row, col, true))
    {
      state += 1;
      state %= UNIQUE_SHAPE;
    }
  }

  int nextState()
  {
    int temp = state + 1;
    return temp %= UNIQUE_SHAPE;
  }

  void put()
  {
    int x = row;
    int y = col;
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        int currX = x + i;
        int currY = y + j;
        char currMap = MAP[currX][currY];
        char currMatrix = matrix[state][i][j];

        if (currMatrix != ' ')
        {
          MAP[currX][currY] = 'O';
        }
      }
    }
  }

  bool isLast()
  {
    int x = row + 1;
    int y = col;
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        int currX = x + i;
        int currY = y + j;
        char currMap = MAP[currX][currY];
        char currMatrix = matrix[state][i][j];
        if (currMatrix != ' ')
        {
          if (currX >= ROW + OFFSET_MAP || currMap == 'O')
          {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool isIntersect(int x, int y, bool space)
  {
    int currState = state;
    if (space)
    {
      currState = nextState();
    }
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        int currX = x + i;
        int currY = y + j;
        char currMap = MAP[currX][currY];

        char currMatrix = matrix[currState][i][j];

        if (currMatrix != ' ')
        {
          if (currX < 0 + OFFSET_MAP || currY < 0 + OFFSET_MAP || currX >= ROW + OFFSET_MAP || currY >= COLUMN + OFFSET_MAP)
          {
            return true;
          }
          if (currMap == 'O')
          {
            return true;
          }
        }
      }
    }
    return false;
  }

  void render()
  {
    for (int i = 0; i < UNIQUE_SHAPE; i++)
    {
      for (int j = 0; j < UNIQUE_SHAPE; j++)
      {
        char mapChar = MAP[i + row][j + col];
        char matrixChar = matrix[state][i][j];
        if (mapChar == ' ' && matrix[state][i][j] != ' ')
        {
          MAP[i + row][j + col] = '*';
        }
      }
    }
  }

  bool logic()
  {
    clearPlayer();
    render();

    if (isLast())
    {
      put();
      return true;
    }
    return false;
  }

  void move(char *str)
  {
    if (strcmp(str, "top") == 0 && !isIntersect(row - 1, col, false))
    {
      row -= 1;
    }
    if (strcmp(str, "left") == 0 && !isIntersect(row, col - 1, false))
    {
      col -= 1;
    }
    if (strcmp(str, "right") == 0 && !isIntersect(row, col + 1, false))
    {
      col += 1;
    }
    if (strcmp(str, "bottom") == 0 && !isIntersect(row + 1, col, false))
    {
      row += 1;
    }
  }
};

Shape *currentShape = NULL;

void init()
{
  forceCls();
  srand(time(NULL));
}

int main()
{
  init();
  game();
}

void splice(int idx)
{
  for (int i = idx + OFFSET_MAP; i >= 1; i--)
  {
    if (i == 1)
    {
      for (int j = 1; j <= COLUMN; j++)
      {
        MAP[i][j] = ' ';
      }
    }
    else
    {
      int copyIdx = i - 1;
      for (int j = 1; j <= COLUMN; j++)
      {
        MAP[i][j] = MAP[copyIdx][j];
      }
    }
  }
}

void checkWin()
{
  for (int i = 0; i < ROW; i++)
  {
    int circle = 0;
    for (int j = 0; j < COLUMN; j++)
    {
      if (MAP[i + OFFSET_MAP][j + OFFSET_MAP] == 'O')
      {
        circle += 1;
      }
    }
    if (circle == COLUMN)
    {
      SCORE += INCREMENTED_SCORE;
      splice(i);
      winSound();
    }
  }
}

void gameLose()
{
  printf("Game over! Your best score is %d! [Enter]", SCORE);
  getchar();
}

void printScore()
{
  printf(COLOR_YELLOW);
  printf("Your score is [%d]", SCORE);
  printf(COLOR_RESET);
}

void printEmptySpace()
{
  for (int i = 0; i < COLUMN; i++)
  {
    ("\t");
  }
  printf("\n");
}
void forceCls()
{
  system("cls");
}

void cls()
{
  // Custom Clear Screen -> Not removing all buffer, just a needed pos onlys
  COORD cursorPosition;
  cursorPosition.X = 0;
  cursorPosition.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void moveSound()
{
  Beep(100, 10);
}

void winSound()
{
  Beep(800, 100);
}

void printMap()
{
  cls();
  printEmptySpace();

  // Print
  int initPrint = ROW / 2 - 2;
  char empty[] = {"      "};

  for (int i = 0; i < ROW + 2; i++)
  {
    printf("\t");
    for (int j = 0; j < COLUMN + 2; j++)
    {
      if (MAP[i][j] == '*')
      {
        // printf(COLOR_RED);
        printf("%c", MAP[i][j]);
        // printf(COLOR_RESET);
      }
      else if (MAP[i][j] == '#')
      {
        // printf(COLOR_YELLOW);
        printf("%c", MAP[i][j]);
        // printf(COLOR_RESET);
      }
      else if (MAP[i][j] == 'O')
      {
        // printf(COLOR_YELLOW);
        printf("%c", MAP[i][j]);
        // printf(COLOR_RESET);
      }
      else
      {
        printf("%c", MAP[i][j]);
      }
    }

    if (i == initPrint)
    {

      printf("%s", empty);
      printScore();
    }
    if (i == initPrint + 2)
    {
      printf("%s", empty);
      printf("A - Left");
    }
    if (i == initPrint + 3)
    {
      printf("%s", empty);
      printf("D - Right");
    }
    if (i == initPrint + 4)
    {
      printf("%s", empty);
      printf("S - Down");
    }
    if (i == initPrint + 5)
    {
      printf("%s", empty);
      printf("Space - Change Direction");
    }
    if (i == initPrint + 7)
    {
      printf("%s", empty);
      printf("\u001b[41m");
      printf("Tetris, Try to make best score!");
      printf(COLOR_RESET);
    }
    if (GAME_LOSE == true && i == initPrint + 9)
    {
      printf("%s", empty);
      gameLose();
    }

    printf("\n");
  }
}

void generatePiece()
{
  currentShape = new Shape();
}

void endScreen()
{
  FILE *fptr;
  char c;
  fptr = fopen("logo.txt", "r");
  if (fptr == NULL)
  {
    printf("Cannot open file \n");
    exit(0);
  }
  c = fgetc(fptr);
  while (c != EOF)
  {
    if (c == '\n')
    {
      Sleep(20);
    }
    printf("%c", c);
    c = fgetc(fptr);
  }
  fclose(fptr);
  char text[] = {"\n\n\tAlongside courage and perseverance, we shape and define our future.\n\tJT 22-1"};
  int length = strlen(text);
  for (int i = 0; i < length; i++)
  {
    Sleep(30);
    printf("%c", text[i]);
  }
  getch();
}

void checkMoving()
{
  FRAME += 1;
  if (FRAME > TOTAL_FRAME_TO_MOVE)
  {
    if (currentShape)
      currentShape->move("bottom");

    printMap();
    FRAME = 0;
  }
}

void game()
{
  generatePiece();
  printMap();
  while (!GAME_LOSE)
  {
    // Enable this for making any move sound
    // Disadvantage : make sleep betweeen the move (slower move)

    // moveSound();
    checkMoving();
    if (kbhit())
    {
      char buffer;
      buffer = getch();
      if (buffer >= 65 && buffer <= 90)
      {
        buffer = buffer + 32;
      }
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
    }
    if (currentShape->logic())
    {
      checkWin();
      generatePiece();
    }
    if (!GAME_LOSE)
    {
      cls();
      printMap();
    }
  }
  forceCls();
  endScreen();
}