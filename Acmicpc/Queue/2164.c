#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int data;
	struct Node * next;

	void (*init)(struct Node *, int);
	void (*free)(struct Node *);
}Node;

void initNode(Node *, int);
void freeNode(Node *);

typedef struct List
{
	int count;

	Node * head;
	Node * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	void (*free)(struct List *);
	void (*display)(struct List *);
	
	void (*push)(struct List *, int);
	int (*pop)(struct List *);
	int (*size)(struct List *);
	int (*front)(struct List *);
	int (*back)(struct List *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void freeList(List *);
void displayList(List *);

void push(List *, int);
int pop(List *);
int size(List *);
int front(List *);
int back(List *);

int main()
{
	List * list = createList();
	int n = 0;

	scanf("%d", &n);
	if(1 > n || n > 500000)
		return 0;
	
	for(int i = 0; i < n; i++)
	{
		list->push(list, i + 1);
	}

	for(;;)
	{
		if(list->count != 1)
			list->pop(list);

		if(list->count != 1)
			list->push(list, list->pop(list));
		else
		{
			fprintf(stdout, "%d\n", list->pop(list));
			break;
		}
	}

	list->free(list);
	list = NULL;

	return 0;
}

Node * createNode(int data)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;

	newNode->init(newNode, data);

	return newNode;
}

void initNode(Node * node, int data)
{
	node->data = data;
	node->next = NULL;

	node->free = freeNode;

	return ;
}

void freeNode(Node * node)
{
	node->data = 0;
	node->next = NULL;

	free(node);

	return ;
}

List * createList()
{
	List * newList = (List *)malloc(sizeof(List));

	newList->init = initList;

	newList->init(newList);

	return newList;
}

void initList(List * list)
{
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	list->isEmpty = isEmptyList;
	list->free = freeList;
	list->display = displayList;
	
	list->push = push;
	list->pop = pop;
	list->size = size;
	list->front = front;
	list->back = back;

	return ;
}

int isEmptyList(List * list)
{
	return list->head == NULL ? 1 : 0;
}

void freeList(List * list)
{
	if(list->isEmpty(list))
	{
		free(list);

		return ;
	}

	while(list->head)
	{
		Node * temp = list->head;

		list->head = list->head->next;

		temp->free(temp);
		temp = NULL;
	}

	list->head = list->tail = NULL;

	return ;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		fprintf(stdout, "list가 비어있습니다.\n");
		return ;
	}

	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%d\n", temp->data);
	}

	return ;
}

void push(List * list, int data)
{
	Node * node = createNode(data);

	if(list->isEmpty(list))
	{
		list->head = list->tail = node;
		list->count++;

		return ;
	}

	list->tail->next = node;
	list->tail = node;
	list->count++;

	return ;
}

int pop(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	list->count--;
	Node * node = list->head;

	list->head = list->head->next;
	if(list->head == NULL) list->tail = NULL;

	int result = node->data;

	node->free(node);
	node = NULL;
		

	return result;
}

int size(List * list)
{
	if(list->isEmpty(list))
	{
		return 0;
	}

	return list->count;
}

int front(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	return list->head->data;
}

int back(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	return list->tail->data;
}
