#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "Item.h"

typedef struct List
{
	Item * head;
	Item * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	int (*size)(struct List *);
	void (*free)(struct List *);

	int (*pushFront)(struct List *, Item *);
	int (*pushRear)(struct List *, Item *);

	int (*popFront)(struct List *);
	int (*popRear)(struct List *);

	Item * (*peekFront)(struct List *);
	Item * (*peekRear)(struct List *);

	void (*display)(struct List *);
	
}List;

List * createList();

void initList(List *);
int isEmptyList(List *);
int size(List *);
void freeList(List *);

int pushFront(List *, Item *);
int pushRear(List *, Item *);

int popFront(List *);
int popRear(List *);

Item * peekFront(List *);
Item * peekRear(List *);

void displayList(List *);

#endif
