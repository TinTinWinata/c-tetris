#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int randomInt(int min, int max)
{
  return min + rand() % (max + 1 - min);
}

int double_array_length(char **array)
{
}

int array_length(char *array)
{
  int temp = 0;
  int len = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < len; i++)
  {
    temp += 1;
    printf("masuk [%c]\n", array[temp]);
    if (array[i] == '\0')
    {
      return temp - 1;
    }
  }
}