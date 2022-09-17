#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define COLOR_RED "\u001b[31"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define BACKGROUND_RED "\u001b[41m"

int randomInt(int min, int max)
{
  return min + rand() % (max + 1 - min);
}
