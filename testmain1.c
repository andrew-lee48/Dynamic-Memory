#include <stdlib.h>
#define MALLOC_SIZE 100
#include "DynMem.c"
#define mymalloc(x) mymalloc(x, __FILE__, __LINE__) 
#define myfree(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char** argv)
{
  char *p1, *p2, *p3, *p4, *p5;
  printf("Attempting to allocate %d bytes of data.\n", MALLOC_SIZE);
  p1 = mymalloc(MALLOC_SIZE);
  printf("Address of returned pointer: %p\n", p1);
  printf("Attempting to allocate %d bytes of data.\n", MALLOC_SIZE);
  p2 = mymalloc(MALLOC_SIZE);
  printf("Address of returned pointer: %p\n", p2);
  printf("Attempting to allocate %d bytes of data.\n", MALLOC_SIZE);
  p3 = mymalloc(MALLOC_SIZE);
  printf("Address of returned pointer: %p\n", p3);
  printf("Attempting to allocate %d bytes of data.\n", MALLOC_SIZE);
  p4 = mymalloc(MALLOC_SIZE);
  printf("Address of returned pointer: %p\n", p4);
  printf("Attempting to allocate %d bytes of data.\n", 50);
  p5 = mymalloc(50);
  printf("Address of returned pointer: %p\n", p5);
  myfree(p1);
  myfree(p2);
  myfree(p3);
  myfree(p4);
  myfree(p5);
  return 0;
}
