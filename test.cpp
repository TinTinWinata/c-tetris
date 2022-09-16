#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int main()
{
  char test[255] = "asd";
  int a = array_length(test);
  printf("helo world %d", a);
}
