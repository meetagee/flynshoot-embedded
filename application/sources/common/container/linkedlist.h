#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "activeObj.h"

typedef struct {
	activeObj_t data;
	node_t* next;
} node_t;

typedef struct {
	node_t* head, tail;
} linkedList_t;

extern void linkedList_init (linkedList_t* linkedList);
extern void insert_back (linkedList_t* linkedList, activeObj_t data);
extern node_t* getTail (linkedList_t* linkedList);
extern void delete_back (linkedList_t* linkedList);

#endif // LINKEDLIST_H
