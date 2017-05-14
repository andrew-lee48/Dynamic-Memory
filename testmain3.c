#include <stdlib.h>
#include "DynMem.c"
#define mymalloc(x) mymalloc(x, __FILE__, __LINE__)
#define myfree(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char** argv)
{
  char *p1;
  printf("Attempting to allocate 5050 bytes of data.\n");
  p1 = (char *)mymalloc(5050);
  printf("Allocating memory of 4750 bytes.\n");
  p1 = (char *)mymalloc(4750);
  printf("Address of returned pointer: %p\n", p1);
  printf("Attempting to allocate 250 bytes of data.\n");
  mymalloc(250);
  printf("Freeing the allocated memory chunk.\n");
  myfree(p1);
  printf("All done\n");
  return 0;
}
