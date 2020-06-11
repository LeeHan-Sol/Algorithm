#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char * data;
	struct Node * next;

	void (*init)(struct Node *, char *, struct Node *);
}Node;

Node * createNode(char *, Node *);
void initNode(Node *, char *, Node *);

typedef struct List
{
	int size;
	Node * head;
	Node * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	void (*display)(struct List *);
	void (*pushFront)(struct List *, int);
	int (*popFront)(struct List *);
	int (*peekFront)(struct List *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void displayList(List *);
void pushFront(List *, int);
int popFront(List *);
int peekFront(List *);

void sort(List *, int, int);
void swap(int *, int *);
Node * divide(List *, int, int);
Node * conquer(Node *, Node *, int);

int main()
{
	int n = 0;
	scanf("%d", &n);
	if(1 > n || n > 1000000) return 0;

	List * list = createList();

	for(int i = 0; i < n; i++)
	{
		int input = 0;
		scanf("%d", &input);

		list->pushFront(list, input);
	}

	list->display(list);

	sort(list, 0, list->size-1);

	return 0;
}

Node * createNode(char * data, Node * next)
{
	Node * new_node = (Node *)malloc(sizeof(Node));
	
	new_node->init = initNode;
	new_node->init(new_node, data, next);

	return new_node;
}

void initNode(Node * node, char * data, Node * next)
{
	node->data = (char *)malloc(sizeof(char) * 4);
	if(node->data == NULL)
	{
		fputs("node->data fail malloc()\n", stderr);
		exit(1);
	}
	*((int *)node->data) = *((int *)data);
	node->next = next;

	return ;
}

List * createList()
{
	List * new_list = (List *)malloc(sizeof(List));
	if(new_list == NULL)
	{
		fputs("new_list fail malloc()\n", stderr);
		exit(1);
	}

	new_list->init = initList;
	new_list->init(new_list);

	return new_list;
}

void initList(List * list)
{
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	list->init = initList;
	list->isEmpty = isEmptyList;
	list->display = displayList;
	list->pushFront = pushFront;
	list->popFront = popFront;
	list->peekFront = peekFront;

	return ;
}

int isEmptyList(List * list)
{
	return list->size == 0 ? 1 : 0;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		return ;
	}

	fputs("List 항목\n", stdout);
	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%5d", *((int *)temp->data));	
	}
	fputc('\n', stdout);

	return ;
}

void pushFront(List * list, int data)
{
	if(list->isEmpty(list))
	{
		list->head = createNode((char *)&data, NULL);
		list->tail = list->head;
		list->size++;
		
		return ;
	}

	list->head = createNode((char *)&data, list->head);
	list->size++;

	return ;
}

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	Node * temp = list->head;
	list->head = list->head->next;
	if(list->head == NULL)
	{
		list->tail = NULL;
	}
	int result = *((int *)temp->data);
	free(temp);
	list->size--;
	
	return result;
}

int peekFront(List * list)
{
	return *((int *)list->head->data);
}

void displayArray(int * array, int size)
{
	if(array == NULL)
		return ;

//	fputs("array 항목\n", stdout);
	for(int i = 0; i < size; i++)
	{
//		fprintf(stdout, "%3d", *(array + i));
		fprintf(stdout, "%d\n", *(array + i));
	}
	fputc('\n', stdout);
	
	return ;
}

void sort(List * list, int left, int right)
{	
	divide(list, left, right);

	return ;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return ;
}

Node * divide(List * list, int left, int right)
{
	if(left >= right) 
	{
		Node * result = list->head;
		for(int i = 0; result != NULL && i < left; i++)
		{
			result = result->next;
		}
		fprintf(stdout, "마지막 남은 노드 : %d[%p]\n", *((int *)result->data), result);
		return result;
	}

	int mid = (left + right) / 2;

	Node * node_left = divide(list, left, mid);
	Node * node_right = divide(list, mid + 1, right);

	int count = right - left + 1;
	conquer(node_left, node_right, count);
}

Node * conquer(Node * left, Node * right, int count)
{
	Node * result = left;

	for(int i = 0; i < count; i++)
	{
		if(*((int *)left->data) > *((int *)right->data))
		{
			swap((int *)left->data, (int *)right->data);
		}
		else if(left->next == right)
		{
			right = right->next;
		}
		else
		{
			left = left->next;
		}
	}

	return result;
}
