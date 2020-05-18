#include "List.h"

List * createList()
{
	List * list = (List *)malloc(sizeof(List));
	
	list->init = initList;
	list->init(list);

	return list;
}

void initList(List * list)
{
	list->head = NULL;
	list->tail = NULL;

	list->isEmpty = isEmptyList;
	list->size = size;
	list->clear = clearList;
	list->free = freeList;

	list->pushFront = pushFront;
	list->pushRear = pushRear;

	list->popFront = popFront;
	list->popRear = popRear;

	list->peekFront = peekFront;
	list->peekRear = peekRear;

	list->pushData = pushData;
	list->searchData = searchData;

	list->display = displayList;
}

int isEmptyList(List * list)
{
	return list->head == NULL ? 1 : 0;
}

int size(List * list)
{
	if(list->isEmpty(list))
	{
//		puts("list가 비었습니다.");
		return 0;
	}

	int count = 0;
	for(Item * temp = list->head; temp != NULL; temp = temp->next)
	{
		count++;
	}
	
	return count;
}

void clearList(List * list)
{
	if(list->isEmpty(list))
	{
		return ;
	}

	list->head = list->tail = NULL;

	return ;
}

void freeList(List * list)
{
	if(list->isEmpty(list))
	{
		return ;
	}

	while(list->head != NULL)
	{
		Item * item = list->head;

		list->head = list->head->next;

		item->free(item);
		item = NULL;
	}
	
	list->head = list->tail = NULL;

	free(list);

	return ;
}

int pushFront(List * list, Item * item)
{
	if(list->isEmpty(list))
	{
		list->head = list->tail = item;
		list->head->prev = NULL;
		list->tail->next = NULL;

		return 0;
	}	

	item->next = list->head;
	list->head->prev = item;
	list->head = item;

	return 0;
}

int pushRear(List * list, Item * item)
{
	if(list->isEmpty(list))
	{
		list->head = list->tail = item;

		return 0;
	}

	item->prev = list->tail;
	list->tail->next = item;
	list->tail = item;

	return 0;
}

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
//		puts("popFront() list가 비어있습니다.");

		return 1;
	}

	Item * item = list->head;

	if(list->head == list->tail)
	{
		item->free(item);
		item = NULL;

		list->head = list->tail = NULL;

		return 0;
	}

	list->head = item->next;
	list->head->prev = NULL;

	item->free(item);
	item = NULL;

	return 0;
}

int popRear(List * list)
{
	if(list->isEmpty(list))
	{
//		puts("popRear() list가 비어있습니다.");
		
		return 0;
	}

	if(list->head == list->tail)
	{
		list->free(list);

		return 1;
	}

	Item * item = list->tail;

	list->tail = item->prev;
	item->next = NULL;

	item->free(item);
	item = NULL;

	return 1;
}

Item * peekFront(List * list)
{
	if(list->isEmpty(list))
	{
//		puts("peekFront() list가 비어있습니다.");

		return (Item *)NULL;
	}

	return list->head;
}

Item * peekRear(List * list)
{
	if(list->isEmpty(list))
	{
//		puts("peekRear() list가 비어있습니다.");

		return (Item *)NULL;
	}

	return list->tail;
}

int pushData(List * list, int u, int v)
{
	Item * uItem = searchData(list, u);
	if(uItem == NULL)
	{
		uItem = createItem(createNode(u));
		list->pushRear(list, uItem);
	}

	Item * vItem = searchData(list, v);
	if(vItem == NULL)
	{
		vItem = createItem(createNode(v));
		list->pushRear(list, vItem);
	}

	uItem->node->addConnection(uItem->node, vItem->node);
	vItem->node->addConnection(vItem->node, uItem->node);
	
	return 0;
}

Item * searchData(List * list, int data)
{
	if(list->isEmpty(list))
	{
//		puts("List.c searchData() list가 비어있습니다.");
		return (Item *)NULL;
	}

	for(Item * temp = list->head; temp != NULL; temp = temp->next)
	{
		if(temp->node->data == data)
			return temp;
	}

	return (Item *)NULL;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		puts("list가 비어있습니다.");

		return ;
	}

	for(Item * temp = list->head; temp != NULL; temp = temp->next)
	{
		temp->display(temp);
	}
	
	return ;
}
