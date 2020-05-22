#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int data;
	int priority;
	struct Node * next;

	void (*init)(struct Node *, int, int);
	void (*free)(struct Node *);
	void (*display)(struct Node *);
}Node;

Node * createNode(int, int);
void initNode(Node *, int, int);
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
	
	void (*push)(struct List *, int, int);
	int (*pop)(struct List *);
	int (*find)(struct List *);
	int (*front)(struct List *);
	int (*back)(struct List *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void clearList(List *);
void freeList(List *);
void displayList(List *);

void push(List *, int, int);
int pop(List *);
int find(List *);
int front(List *);
int back(List *);

int main()
{
	List * list = createList();
	int testCase = 0, n = 0, m = 0, priority = 0;
	scanf("%d", &testCase);
	getchar();

	int arrayPriority[9] = {0,};
	int index = 8, count = 0;

	for(int i = 0; i < testCase; i++)
	{
		scanf("%d %d", &n, &m);
		getchar();
		if(n > 100) return 0;
		if(0 > m || m > n) return 0;

		for(int j = 0; j < n; j++)
		{
			scanf("%d", &priority);
			getchar();
//			fprintf(stdout, "\t\tj, priority : %d, %d\n", j, priority);
			list->push(list, j, priority);
			arrayPriority[priority - 1]++;
		}

//		fprintf(stdout, "list->size : %d\n", list->size);
//		fputs("list :\t", stdout);
//		list->display(list);
//
//		fputs("arrayPriority :\t", stdout);
//		for(int i = 0; i < 9; i++)
//			fprintf(stdout, "%d[%d] ", arrayPriority[i], i + 1);
//		fputc('\n', stdout);

		while(list->size > 0)
		{
			int maxPriority = 0;

			if(arrayPriority[index] == 0)
			{
				index--;
				continue;
			}
			else
			{
				maxPriority = index + 1;
			}

//			fprintf(stdout, "maxPriority, index, count : %d, %d, %d\n", maxPriority, index, count);

			if(list->head->priority == maxPriority)
			{
				if(list->head->data == m)
				{
					count++;
					break;
				}

				list->pop(list);
				arrayPriority[index]--;
				count++;

//				fprintf(stdout, "count++\n");
			}
			else
			{
				list->push(list, list->pop(list), list->head->priority);
			}

//			fputs("list :\t", stdout);
//			list->display(list);
		}
		
		fprintf(stdout, "%d\n", count);

		list->clear(list);
		memset(arrayPriority, 0, sizeof(arrayPriority[0]) * 9);
		index = 8;
		count = 0;
//		for(int i = 0; i < 9; i++)
//			arrayPriority[i] = 0;

//		fprintf(stdout, "list->size : %d\n", list->size);
//		fputs("list :\t", stdout);
//		list->display(list);
//
//		fputs("arrayPriority :\t", stdout);
//		for(int i = 0; i < 9; i++)
//			fprintf(stdout, "%d[%d] ", arrayPriority[i], i + 1);
//		fputc('\n', stdout);

	}


	list->free(list);
	list = NULL;

	return 0;
}

Node * createNode(int data, int priority)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;

	newNode->init(newNode, data, priority);

	return newNode;
}

void initNode(Node * node, int data, int priority)
{
	node->data = data;
	node->priority = priority;
	node->next = NULL;

	node->free = freeNode;
	node->display = displayNode;

	return ;
}

void freeNode(Node * node)
{
	node->data = 0;
	node->next = NULL;

	free(node);

	return ;
}

void displayNode(Node * node)
{
	fprintf(stdout, "%d[%d]", node->data, node->priority);
	
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
	
	list->push = push;
	list->pop = pop;
	list->find = find;
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

void push(List * list, int data, int priority)
{
	Node * node = createNode(data, priority);

	if(list->isEmpty(list))
	{
		list->head = list->tail = node;
		list->size++;

		return ;
	}

	list->tail->next = node;
	list->tail = node;
	list->size++;

	return ;
}

int pop(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	list->size--;
	Node * node = list->head;

	list->head = list->head->next;
	if(list->head == NULL) list->tail = NULL;

	int result = node->data;

	node->free(node);
	node = NULL;
		

	return result;
}

int find(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}
	
	int maxPriority = 0;

	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		if(temp->priority > maxPriority) 
			maxPriority = temp->priority;
	}

	return maxPriority;
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
