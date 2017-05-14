#include <stdlib.h>
#include "DynMem.c"
#define mymalloc(x) mymalloc(x, __FILE__, __LINE__)
#define myfree(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char** argv)
{
  char c, *p;
  printf("Attempting to free pointer that was never allocated.\n");
  myfree(&c);
  printf("Attempting to allocate 100 bytes of data.\n");
  p = (char *)mymalloc(200);
  printf("Address of returned pointer: %p\n", p);
  printf("Attempting to free pointer to dynamic memory that was not returned from malloc.\n");
  myfree(p+10);
  printf("Attempting redundant freeing of the same pointer.\n");
  myfree(p);
  myfree(p);
  printf("Allocating memory of 100 bytes.\n");
  p = (char *)mymalloc(100);
  printf("Address of returned pointer: %p\n", p);
  printf("Freeing pointer to allocated memory.\n");
  myfree(p);
  printf("Allocating memory of 100 bytes.\n");
  p = (char *)mymalloc(100);
  printf("Address of returned pointer: %p\n", p);
  printf("Freeing pointer to allocated memory \n");
  myfree(p);
  printf("All done\n");
  return 0;
}

