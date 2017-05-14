/*
 * DynMem.h
 */
#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdio.h>

/*
 * Struct for tagging allocated and free memory blocks.
 * It holds information about an associated memory block's
 * size, usage status, and pointers to adjacent memory blocks.
 */
struct MemEntry
{
  struct MemEntry *prev, *next;	// pointers to adjacent memory blocks
  int isFree:1;	//isFree only have 1 or 0 as values
  unsigned int size:13; //range of values for size is 0 to 8192
};
typedef struct MemEntry MemEntry;

/*
 * mymalloc(unsigned int size)
 */
void* mymalloc(unsigned int size, const char* fileName, const int lineNum);

/*
 * myfree(void* p)
 */
void myfree(void * tf, const char* fileName, const int lineNum);

#endif
