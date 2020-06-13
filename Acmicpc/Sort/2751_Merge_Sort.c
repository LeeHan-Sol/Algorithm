#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char * data;
	struct Node * prev;
	struct Node * next;

	void (*init)(struct Node *, char *, struct Node *, struct Node *);
}Node;

Node * createNode(char *, Node *, Node *);
void initNode(Node *, char *, Node *, Node *);

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
	void (*moveItem)(struct List *, Node *, Node *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void displayList(List *);
void pushFront(List *, int);
int popFront(List *);
int peekFront(List *);
void moveItem(List *, Node *, Node *);

int sort(List *, int, int);
void swap(int *, int *);
int divide(List *, int, int);
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

//	list->display(list);

	sort(list, 0, list->size-1);
	list->display(list);

	return 0;
}

Node * createNode(char * data, Node * prev, Node * next)
{
	Node * new_node = (Node *)malloc(sizeof(Node));
	
	new_node->init = initNode;
	new_node->init(new_node, data, prev, next);

	return new_node;
}

void initNode(Node * node, char * data, Node * prev, Node * next)
{
	node->data = (char *)malloc(sizeof(char) * 4);
	if(node->data == NULL)
	{
		fputs("node->data fail malloc()\n", stderr);
		exit(1);
	}
	*((int *)node->data) = *((int *)data);
	node->prev = prev;
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
	list->moveItem = moveItem;

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

//	fputs("List 항목\n", stdout);
	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%d\n", *((int *)temp->data));
//		fprintf(stdout, "%5d", *((int *)temp->data));	
//		fprintf(stdout, "%5d[%p]", *((int *)temp->data), temp);	
	}
//	fputc('\n', stdout);

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

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	Node * temp = list->head;
	list->head = list->head->next;
	list->head->prev = NULL;
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

void moveItem(List * list, Node * from, Node * to)
{
	if(from->next != NULL)
		from->next->prev = from->prev;
	from->prev->next = from->next;
	from->next = from->prev = NULL;

	from->next = to;
	if(to->prev != NULL)
	{
		to->prev->next = from;
	}
	from->prev = to->prev;
	to->prev = from;
	if(list->head == to)
	{
		list->head = from;
	}

	return ;
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

int sort(List * list, int start, int end)
{	
//	fprintf(stdout, "start, end : %d, %d\n", start, end);
	if(start == end) return 1;
	
	int mid = (start + end) / 2;

	int compare_left = 0;
	int compare_right = 0;
	
	int left = sort(list, start, mid);
	int right = sort(list, mid + 1, end);
//	fprintf(stdout, "left, right: %d, %d\n", left, right);

	Node * node_left = list->head;
	Node * node_right = list->head;

	for(int i = 0; i < start; i++)
	{
		node_left = node_left->next;		
	}
	for(int i = 0; i < end - (right - 1); i++)
	{
		node_right = node_right->next;
	}

	for(;;)
	{
//	fprintf(stdout, "node_left, node_right : %d, %d", *((int *)node_left->data), *((int *)node_right->data));
//	fprintf(stdout, "\t\tstart, end : %d, %d\n", start, end);

		if(left == compare_left || right == compare_right) 
		{
//			fputs("break\n", stdout);
			break;
		}

		if(*((int *)node_left->data) > *((int *)node_right->data))
		{
			if(node_right->next != NULL)
			{
				node_right = node_right->next;
				list->moveItem(list, node_right->prev, node_left);
			}
			else
			{
				list->moveItem(list, node_right, node_left);
			}
			compare_right++;
		}
		else
		{
			node_left = node_left->next;
			compare_left++;
		}
//	list->display(list);
	}

	return left + right;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return ;
}

int divide(List * list, int left, int right)
{
	return 0;
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
