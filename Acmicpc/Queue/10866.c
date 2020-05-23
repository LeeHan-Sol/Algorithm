#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int data;
	struct Node * next;
	struct Node * prev;

	void (*init)(struct Node *, int);
	void (*free)(struct Node *);
	void (*display)(struct Node *);
}Node;

Node * createNode(int);
void initNode(Node *, int);
void freeNode(Node *);
void displayNode(Node *);

typedef struct List
{
	int size;

	Node * head;
	Node * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	void(*clear)(struct List *);
	void (*free)(struct List *);
	void (*display)(struct List *);
	
	void (*pushFront)(struct List *, int);
	void (*pushBack)(struct List *, int);
	int (*popFront)(struct List *);
	int (*popBack)(struct List *);
	int (*front)(struct List *);
	int (*back)(struct List *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void clearList(List *);
void freeList(List *);
void displayList(List *);

void pushFront(List *, int);
void pushBack(List *, int);
int popFront(List *);
int popBack(List *);
int front(List *);
int back(List *);

int main()
{
	List * list = createList();
	int n = 0;
	scanf("%d", &n);
	getchar();
	if(1 > n || n > 10000)
		return 0;
//	fprintf(stdout, "\t\tn : %d\n", n);

	char * buffer = (char *)malloc(sizeof(char) * 32);

	for(int i = 0; i < n; i++)
	{
		fgets(buffer, 32, stdin);
		
		if(strncmp(buffer, "push_front ", 11) == 0)
		{
			int integer = atoi(buffer + 11);
			if(1 > integer || integer > 100000) return 0;
//			fprintf(stdout, "\t\tinteger : %d\n", integer);

			list->pushFront(list, integer);
		}
		else if(strncmp(buffer, "push_back ", 10) == 0)
		{
			int integer = atoi(buffer + 10);
			if(1 > integer || integer > 100000) return 0;
//			fprintf(stdout, "\t\tinteger : %d\n", integer);

			list->pushBack(list, integer);
		}
		else if(strncmp(buffer, "pop_front", 9) == 0)
		{
			fprintf(stdout, "%d\n", list->popFront(list));
		}
		else if(strncmp(buffer, "pop_back", 8) == 0)
		{
			fprintf(stdout, "%d\n", list->popBack(list));
		}
		else if(strncmp(buffer, "size", 4) == 0)
		{
			fprintf(stdout, "%d\n", list->size);
		}
		else if(strncmp(buffer, "empty", 5) == 0)
		{
			fprintf(stdout, "%d\n", list->isEmpty(list));
		}
		else if(strncmp(buffer, "front", 5) == 0)
		{
			fprintf(stdout, "%d\n", list->front(list));
		}
		else if(strncmp(buffer, "back", 4) == 0)
		{
			fprintf(stdout, "%d\n", list->back(list));
		}
		
		memset(buffer, 0x00, sizeof(char) * 32);
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
	node->prev = NULL;

	node->free = freeNode;
	node->display = displayNode;

	return ;
}

void freeNode(Node * node)
{
	node->data = 0;
	node->next = NULL;
	node->prev = NULL;

	free(node);

	return ;
}

void displayNode(Node * node)
{
	fprintf(stdout, "%d", node->data);
	
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
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	list->isEmpty = isEmptyList;
	list->clear = clearList;
	list->free = freeList;
	list->display = displayList;
	
	list->pushFront = pushFront;
	list->pushBack = pushBack;
	list->popFront = popFront;
	list->popBack = popBack;
	list->front = front;
	list->back = back;

	return ;
}

int isEmptyList(List * list)
{
	return list->head == NULL ? 1 : 0;
}

void clearList(List * list)
{
	if(list->isEmpty(list))
	{
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
	list->size = 0;

	return ;
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
	list->size = 0;

	free(list);

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
		temp->display(temp);
		fputc(' ', stdout);
	}
	fputc('\n', stdout);

	return ;
}

void pushFront(List * list, int data)
{
	Node * node = createNode(data);
	list->size++;

	if(list->isEmpty(list))
	{
		list->head = list->tail = node;

		return ;
	}

	list->head->prev = node;
	node->next = list->head;
	list->head = node;

	return ;
}

void pushBack(List * list, int data)
{
	Node * node = createNode(data);
	list->size++;

	if(list->isEmpty(list))
	{
		list->head = list->tail = node;

		return ;
	}

	list->tail->next = node;
	node->prev = list->tail;
	list->tail = node;

	return ;
}

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	list->size--;
	Node * node = list->head;

	list->head = list->head->next;
	if(list->head == NULL) 
	{
		list->tail = NULL;
	}
	else
	{
		list->head->prev = NULL;
	}

	int result = node->data;

	node->free(node);
	node = NULL;
		

	return result;
}

int popBack(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	list->size--;
	Node * node = list->tail;

	list->tail = list->tail->prev;
	if(list->tail == NULL) 
	{
		list->head = NULL;
	}
	else
	{
		list->tail->next = NULL;
	}

	int result = node->data;

	node->free(node);
	node = NULL;

	return result;
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
