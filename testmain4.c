#include <stdlib.h>
#define MALLOC_SIZE 476
#include "DynMem.c"
#define mymalloc(x) mymalloc(x, __FILE__, __LINE__)
#define myfree(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char** argv)
{
	char *p1, *p2, *p3, *p4, *p5;
	printf("Attempting to allocate %d bytes of data into p1.\n", MALLOC_SIZE);
	p1 = (char*)mymalloc(MALLOC_SIZE);
	printf("Address of returned pointer: %p\n", p1);
	printf("Attempting to allocate %d bytes of data into p2.\n", MALLOC_SIZE);
	p2 = (char*)mymalloc(MALLOC_SIZE);
	printf("Address of returned pointer: %p\n", p2);
	printf("Attempting to allocate %d bytes of data into p3.\n", MALLOC_SIZE);
	p3 = (char*)mymalloc(MALLOC_SIZE);
	printf("Address of returned pointer: %p\n", p3);
	printf("Attempting to allocate %d bytes of data into p4.\n", MALLOC_SIZE);
	p4 = (char*)mymalloc(MALLOC_SIZE);
	printf("Address of returned pointer: %p\n", p4);
	printf("Attempting to allocate %d bytes of data into p5.\n", MALLOC_SIZE);
	p5 = (char*)mymalloc(MALLOC_SIZE);
	printf("Address of returned pointer: %p\n", p5);

	printf("Attempting to free pointer p1.\n");
	myfree(p1);
	printf("Attempting to free pointer p5.\n");
	myfree(p5);
	printf("Attempting to free pointer p2.\n");
	myfree(p2);
	printf("Attempting to free pointer p4.\n");
	myfree(p4);
	printf("Attempting to free pointer p3.\n");
	myfree(p3);
	printf("Test complete.\n");
	return 0;
}
