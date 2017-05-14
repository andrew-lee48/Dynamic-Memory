/*
 * DynMem.c
 */
#include <stdlib.h>
#include "DynMem.h"
#define BLOCKSIZE 5000
#define SIZE_THRESHOLD 100

//myblock represents the heap
static char myblock[BLOCKSIZE];
static int initialized = 0;

/*
 * inspectheap(const char* fileName, const int lineNum)
 * Function called by atexit() to iterate through the heap and
 * print out any MemStruct entries whose isFree values are 0,
 * indicating unfreed memory.
 */
void inspectheap()
{
	MemEntry *ptr = (MemEntry*)myblock;
	while (ptr != 0)
	{
		// iterate through the heap and find memory blocks still in use
		// ignore the bigRoot MemEntry which acts only as a placeholder
		if (ptr->isFree == 0 && ptr != (MemEntry*)(myblock + BLOCKSIZE - sizeof(MemEntry))) {
			printf("Error: MemEntry at address %p is not free.\n", ptr);
		}
		ptr = ptr->next;
	}
}

/*
 * myalloc(unsigned int size)
 * Returns a pointer to a space in the heap if an available
 * block of memory exists. If no memory block can complete
 * the request, a NULL pointer is returned.
 */
void * mymalloc(unsigned int size, const char* fileName, const int lineNum)
{
	atexit(inspectheap);
	/* smallRoot is a pointer to the MemEntry on the left of the array, holding
	 * the memory space for chunks less than 100(?) bytes. bigRoot is a pointer
	 * to the MemEntry on the right of the array, holding memory space for chunks
	 * greater than 100 bytes
	 */
	static MemEntry *smallRoot = (MemEntry *)(myblock);
	static MemEntry *bigRoot = (MemEntry *)(myblock + BLOCKSIZE - sizeof(MemEntry));
	// p is a pointer to some block of allocated memory
	// newChunk points to a "new chunk" of free memory
	MemEntry *p, *newChunk;
	if (!initialized) {
		//Code that initializes the smallRoot
		smallRoot->prev = 0;
		smallRoot->next = bigRoot;
		// free space is anything not taken by the two MemEntry structs
		smallRoot->size = BLOCKSIZE-2*sizeof(MemEntry);
		smallRoot->isFree = 1;
		/* Code that initializes the bigRoot. bigRoot is just a pointer
		 * for the large memory blocks to grow from and will not be a
		 * reference to any memory storage space.
		 */
		bigRoot->prev = smallRoot;
		bigRoot->next = 0;
		bigRoot->size = 0;
		bigRoot->isFree = 0;
		initialized = 1;
	}
	if (size <= 0 || size > BLOCKSIZE) {	// requested memory exceeds maximum size of heap
		printf("Error: Heap cannot allocate space of this size. \n");
		printf("Error in file %s at line %d.\n", fileName, lineNum);
		return NULL;
	}
	// requested memory is to be placed with bias to the left
	if (size < SIZE_THRESHOLD) {
		p = smallRoot;
		do
		{
			// iterate through the memory blocks to find an appropriate block
			if (p->size < size || !p->isFree) {
				p = p->next;
			}
			// memory block is too small to split and leave a significant free chunk
			else if ( p->size <= (size + sizeof(MemEntry)) ) {
				p->isFree = 0;
				return (char *)p + sizeof(MemEntry);
			}
			// memory block is large enough to split and leave a significant free chunk
			else {
				/*
				 * Construct the new free memory block immediately following the
				 * newly designated allocated memory. Designate pointers for both
				 * the new allocated and free memory chunks and adjust sizes so that
				 * their sum equals the previous larger chunk.
				 */
				newChunk = (MemEntry *)((char *)p + sizeof(MemEntry) + size);
				newChunk->prev = p;
				newChunk->next =p->next;
				p->next->prev = newChunk;
				p->next = newChunk;
				newChunk->size = p->size - sizeof(MemEntry) - size;
				newChunk->isFree = 1;
				p->size = size;
				p->isFree = 0;
				return (char *)p + sizeof(MemEntry);
			}
		} while(p != 0);
	}	// end of if (size < SIZE_THRESHOLD)
	// requested memory is to be placed with bias to the right
	else {
		p = bigRoot;
		do
		{
			// iterate through the memory blocks to find an appropriate block
			if (p->size < size || !p->isFree) {
				p = p->prev;
			}
			// memory block is too small to split and leave a significant free chunk
			else if ( p->size<=(size + sizeof(MemEntry)) ) {
				p->isFree = 0;
				return (char *)p + sizeof(MemEntry);
			}
			// memory block is large enough to split and leave a significant free chunk
			else {
				/*
				 * Construct the new free memory block immediately before the
				 * newly designated allocated memory. Designate pointers for both
				 * the new allocated and free memory chunks and adjust sizes so that
				 * their sum equals the previous larger chunk.
				 */
				newChunk = (MemEntry *)((char *)p+p->size-size);
				newChunk->prev = p;
				newChunk->next = p->next;
				p->next->prev = newChunk;
				p->next = newChunk;
				newChunk->size = size;
				newChunk->isFree = 0;
				p->size -= (sizeof(MemEntry)+size);
				p->isFree = 1;
				return (char *)newChunk + sizeof(MemEntry);
			}
		} while(p != 0);
	}	// end of else
	// saturation: heap cannot fulfill request due to lack of free space
	printf("Error: Heap cannot allocate space of this size.\n");
	printf("Error in file %s at line %d.\n", fileName, lineNum);
	return NULL;
}

/*
 * myfree(void* p) attempts to free the memory allocated at this pointer.
 * "Freeing" entails setting the isFree member's value to 1.
 * This function should NOT do anything is the pointer is invalid,
 * i.e. memory already free, memory not a pointer returned by malloc.
 */
void myfree(void *p, const char* fileName, const int lineNum)
{
	// pointers to examine adjacent memory blocks for potential merging
	MemEntry *pred, *succ;
	MemEntry *ptr = (MemEntry *)myblock;

	// check if the argument pointer is null
	if (p == NULL) {
		printf("Error:Null pointer.\n");
		printf("Error in file %s at line %d.\n", fileName, lineNum);
		return;
	}
	// change the value of p so that it points to the MemEntry instead of the data
	p = p - sizeof(MemEntry);
	// iterate through the MemEntry linked list to find the matching pointer
	while (ptr != p && ptr != 0)
	{
		ptr = ptr->next;
	}

	// argument pointer not found in heap
	if (ptr != p) {
		printf("Error: This pointer was not returned from malloc or was never allocated.\n");
		printf("Error in file %s at line %d.\n", fileName, lineNum);
		return;
	}

	// set pointer to MemEntry pointer before memory
	// ptr = (MemEntry *)p-1;
	//printf("ptr after adjustment: %p\n", ptr);
	/*
	 * Perform checks on adjacent blocks to see if memory can be merged together to
	 * create a single, larger contiguous block of free memory.
	 */
	// check if the block before it is free
	if ((pred = ptr->prev) != 0 && pred->isFree) {
		// append previous block with current block
		pred->size += sizeof(MemEntry)+ptr->size;
		pred->next = ptr->next;
		if (ptr->next != 0)
			ptr->next->prev=pred;
	}
	// previous block is currently in use
	else {
		ptr->isFree=1;
		pred = ptr;
	}
	// check if the block after it is free
	if ((succ= ptr->next) != 0 && succ->isFree) {
		pred->size += sizeof(MemEntry)+succ->size;
		pred->next = succ->next;
		if(succ->next != 0)
			succ->next->prev = pred;
	}
	printf("Pointer %p was successfully freed.\n", p + sizeof(MemEntry));
	p = NULL;
}
