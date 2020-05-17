#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

typedef struct Item
{
	Node * node;
	struct Item * prev;
	struct Item * next;

	void (*init)(struct Item *, Node *);
	void (*free)(struct Item *);

	void (*display)(struct Item *);
}Item;

Item * createItem(Node *);

void initItem(Item *, Node *);
void freeItem(Item *);

void displayItem(Item *);

#endif
