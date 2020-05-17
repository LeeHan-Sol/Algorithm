#include "Item.h"

Item * createItem(Node * node)
{
	Item * newItem = (Item *)malloc(sizeof(Item));

	newItem->init = initItem;
	newItem->init(newItem, node);

	return newItem;
}

void initItem(Item * item, Node * node)
{
	item->node = node;
	item->prev = NULL;
	item->next = NULL;

	item->free = freeItem;

	item->display = displayItem;
}

void freeItem(Item * item)
{
	item->node = NULL;
	item->prev = NULL;
	item->next = NULL;

	free(item);
}

void displayItem(Item * item)
{
	printf("%4d[%p] [%p] [%p]\n", item->node->data, item, item->prev, item->next);
}
