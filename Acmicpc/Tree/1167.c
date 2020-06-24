#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char * data;
	struct Node * prev;
	struct Node * next;

	void (*init)(struct Node * node, char * data, struct Node * prev, struct Node * next);
	void (*display)(struct Node * node);
	void (*free)(struct Node * node);
}Node;

Node * createNode(char * data, Node * prev, Node * next);
void initNode(Node * node, char * data, Node * prev, Node * next);
void displayNode(Node * node);
void freeNode(Node * node);

typedef struct List
{
	int size;
	Node * head;
	Node * tail;

	void (*init)(struct List * list);
	int (*isEmpty)(struct List * list);
	void (*display)(struct List * list);
	void (*rDisplay)(struct List * list);
	void (*pushFront)(struct List * list, int data);
	void (*pushRear)(struct List * list, int data);
	int (*popFront)(struct List * list);
	int (*popRear)(struct List * list);
}List;

List * createList();
void initList(List * list);
int isEmptyList(List * list);
void displayList(List * list);
void rDisplayList(List * list);
void pushFront(List * list, int data);
void pushRear(List * list, int data);
int popFront(List * list);
int popRear(List * list);

int main()
{
	List * list = createList();

	for(int i = 0; i < 10; i++)
	{
		list->pushFront(list, i);
	}
	for(int i = 1; i < 10; i++)
	{
		list->pushRear(list, i);
	}
	list->display(list);
	list->rDisplay(list);
	
	for(int i = 0; i < 10; i++)
	{
		list->popFront(list);
	}
	list->display(list);
	list->rDisplay(list);
	
	for(int i = 0; i < 10; i++)
	{
		list->popRear(list);
	}
	list->display(list);
	list->rDisplay(list);
	
	for(int i = 0; i < 5; i++)
	{
		list->pushRear(list, i);
	}
	for(int i = 0; i < 3; i++)
	{
		list->popFront(list);
	}
	for(int i = 0; i < 2; i++)
	{
		list->popFront(list);
	}
	list->display(list);
	list->rDisplay(list);

	return 0;
}

Node * createNode(char * data, Node * prev, Node * next)
{
	Node * newNode = (Node *)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		fprintf(stdout, "newNode malloc() error\n");
		exit(1);
	}

	newNode->init = initNode;
	newNode->init(newNode, data, prev, next);

	return newNode;
}

void initNode(Node * node, char * data, Node * prev, Node * next)
{
	node->data = (char *)malloc(sizeof(char) * 4);
	*((int *)node->data) = *((int *)data);
	node->prev = prev;
	node->next = next;

	node->display = displayNode;
	node->free = freeNode;

	return ;
}

void displayNode(Node * node)
{
	fprintf(stdout, "%d", *((int *)node->data));

	return ;
}

void freeNode(Node * node)
{
	free(node->data);
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
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	list->isEmpty = isEmptyList;
	list->display = displayList;
	list->rDisplay = rDisplayList;
	list->pushFront = pushFront;
	list->pushRear = pushRear;
	list->popFront = popFront;
	list->popRear = popRear;
}

int isEmptyList(List * list)
{
	return list->size == 0 ? 1 : 0;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		fprintf(stdout, "List가 비어있습니다.\n");
		return ;
	}

	fputs("List 항목\n", stdout);
	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%d ", *((int *)temp->data));
	}
	fputc('\n', stdout);

	return ;
}

void rDisplayList(List * list)
{
	if(list->isEmpty(list))
	{
		fprintf(stdout, "List가 비어있습니다.\n");
		return ;
	}

	fputs("List 항목\n", stdout);
	for(Node * temp = list->tail; temp != NULL; temp = temp->prev)
	{
		fprintf(stdout, "%d ", *((int *)temp->data));
	}
	fputc('\n', stdout);

	return ;
}

void pushFront(List * list, int data)
{
	if(list->isEmpty(list))
	{
		list->head = createNode((char *)&data, NULL, NULL);
		list->tail = list->head;
		list->size++;

		return ;
	}

	list->head->prev = createNode((char *)&data, NULL, list->head);	
	list->head = list->head->prev;
	list->size++;

	return ;
}

void pushRear(List * list, int data)
{
	if(list->isEmpty(list))
	{
		list->head = createNode((char *)&data, NULL, NULL);
		list->tail = list->head;
		list->size++;

		return ;
	}

	list->tail->next = createNode((char *)&data, list->tail, NULL);
	list->tail = list->tail->next;
	list->size++;

	return ;
}

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	int result = *((int *)list->head);
	Node * temp = list->head;
	list->head = list->head->next;
	list->size--;
	if(list->isEmpty(list))
	{
		list->head = list->tail = NULL;
	}
	else
	{
		list->head->prev = NULL;
	}

	temp->free(temp);

	return result;
}

int popRear(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	int result = *((int *)list->tail);
	Node * temp = list->tail;
	list->tail = list->tail->prev;
	list->size--;
	if(list->isEmpty(list))
	{
		list->head = list->tail = NULL;
	}
	else
	{
		list->tail->next = NULL;
	}


	temp->free(temp);

	return result;
}

