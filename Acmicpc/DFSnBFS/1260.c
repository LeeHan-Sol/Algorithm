#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VTXS 1000

typedef struct Node
{
	char * data;
	struct Node * next;

	void (*init)(struct Node *, char *, struct Node *);
}Node;

Node * createNode(char *, Node *);
Node * createNodeWithoutNext(char *);
void initNode(Node *, char *, Node *);

typedef struct List
{
	int size;
	Node * head;
	Node * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	void (*display)(struct List *);
	int (*popFront)(struct List *);
//	int (*popRear)(struct List *);
	void (*pushFront)(struct List *, int);
	void (*pushRear)(struct List *, int);
	int (*front)(struct List *);
}List;

List * createList();
void initList(List *);
int isEmptyList(List *);
void displayList(List *);
int popFront(List *);
//int popRear(List *);
void pushFront(List *, int);
void pushRear(List *, int);
int front(List *);

typedef struct AdjListGraph
{
	int size;
	int * vertices;
	Node * adj[MAX_VTXS];

	void (*init)(struct AdjListGraph *, int);
	int (*isEmpty)(struct AdjListGraph *);
	void (*display)(struct AdjListGraph *);
	void (*insertEdge)(struct AdjListGraph *, int, int);

	void (*DFS)(struct AdjListGraph *, int *, int);
	void (*BFS)(struct AdjListGraph *, int *, int);
}AdjListGraph;

AdjListGraph * createAdjListGraph(int);
void initAdjListGraph(AdjListGraph *, int);
int isEmptyAdjListGraph(AdjListGraph *);
void displayAdjListGraph(AdjListGraph *);
void insertEdge(AdjListGraph *, int, int);

void DFS(AdjListGraph *, int *, int);
void BFS(AdjListGraph *, int *, int);

void sort(int *, int);
void swap(int *, int *);

int main()
{
	int n = 0, m = 0, v = 0;
	
	scanf("%d %d %d", &n, &m, &v);
	if(1 > n || n > 1000) return 0;
	if(1 > m || m > 10000) return 0;

	AdjListGraph * alg = createAdjListGraph(n);

	int * visited = (int *)malloc(sizeof(int) * n);
	memset(visited, 0, sizeof(int) * n);

	for(int i = 0; i < m; i++)
	{
		int u = 0, v = 0;
		scanf("%d %d", &u, &v);

		alg->insertEdge(alg, u - 1, v - 1);
	}

//	alg->display(alg);

	DFS(alg, visited, v-1);
	fprintf(stdout, "\n");
	memset(visited, 0, sizeof(int) * n);

	BFS(alg, visited, v-1);
	fprintf(stdout, "\n");

	return 0;
}

/*
int main()
{
	List * list = createList();

	list->pushFront(list, 0);
	for(int i  = 0; i < 5; i++)
	{
		list->pushFront(list, i+1);
	}
	
	list->display(list);

	for(int i = 0; i < 3; i++)
		list->popFront(list);
	
	list->display(list);

	for(int i = 0; i < 1; i++)
		list->popFront(list);
	list->display(list);

	for(int i = 0; i < 4; i++)
		list->pushFront(list, i + 1);
	list->display(list);

	list->popFront(list);
	list->display(list);
	
	return 0;
}
*/

Node * createNode(char * data, Node * node)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;
	newNode->init(newNode, data, node);

	return newNode;
}

void initNode(Node * node, char * data, Node * next)
{
//fprintf(stdout, "data : %d\n", *(int *)data);

	node->data = (char *)malloc(sizeof(char) * 4);
	*((int *)(node->data)) = *(int *)data;
	node->next = next;

//fprintf(stdout, "node->data : %d\n", *(int *)node->data);

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
	list->popFront = popFront;
//	list->popRear = popRear;
	list->pushFront = pushFront;
	list->pushRear = pushRear;
	list->front = front;
}

int isEmptyList(List * list)
{
	return list->size == 0 ? 1 : 0;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		fputs("List is Empty\n", stdout);
		return ;
	}

	fputs("List 항목\n", stdout);
	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%4d", *((int *)temp->data));
	}
	fputc('\n', stdout);
	
	return ;
}

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return 0;
	}

	Node * temp = list->head;
	int result = *((int *)temp->data);
	list->head = list->head->next;
	if(list->head == NULL) list->tail = NULL;
	list->size--;
	free(temp);

	return result;
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

void pushRear(List * list, int data)
{
	if(list->isEmpty(list))
	{
		list->head = createNode((char *)&data, NULL);
		list->tail = list->head;
		list->size++;

		return ;
	}
	
	list->tail->next = createNode((char *)&data, NULL);
	list->tail = list->tail->next;
	list->size++;

	return ;
}

int front(List * list)
{
	if(list->isEmpty(list))
		return 0;
	return *((int *)list->head->data);
}

AdjListGraph * createAdjListGraph(int size)
{
	AdjListGraph * newAdjListGraph = (AdjListGraph *)malloc(sizeof(AdjListGraph));
	
	newAdjListGraph->init = initAdjListGraph;
	newAdjListGraph->init(newAdjListGraph, size);

	return newAdjListGraph;
}

void initAdjListGraph(AdjListGraph * alg, int size)
{
	alg->size = size;
	alg->vertices = (int *)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++)
	{
		alg->vertices[i] = i + 1;
	}

	alg->isEmpty = isEmptyAdjListGraph;
	alg->display = displayAdjListGraph;
	alg->insertEdge = insertEdge;

	return ;
}

int isEmptyAdjListGraph(AdjListGraph * alg)
{
	return alg->size == 0 ? 1 : 0;
}

void displayAdjListGraph(AdjListGraph * alg)
{
	if(alg->isEmpty(alg))
		return ;

	fprintf(stdout, "정점의 개수 : %d\n", alg->size);
	for(int i = 0; i < alg->size; i++)
	{
		fprintf(stdout, "%d[%p]    ", alg->vertices[i], &alg->vertices[i]);
		for(Node * temp = alg->adj[i]; temp != NULL; temp = temp->next)
		{
			fprintf(stdout, "%3d[%p]", *((int *)(temp->data)) + 1, temp);
		}
		fputc('\n', stdout);
	}
	
	return ;
}

void insertEdge(AdjListGraph * alg, int u, int v)
{
	alg->adj[u] = createNode((char *)&v, alg->adj[u]);
	alg->adj[v] = createNode((char *)&u, alg->adj[v]);

	return ;
}


void DFS(AdjListGraph * alg, int * visited, int u)
{
	visited[u] = 1;
	fprintf(stdout, "%d ", u + 1);
	
	int * array = (int *)malloc(sizeof(int) * alg->size);
	int index = 0;

	List * stack = createList();
	stack->pushFront(stack, u);

	for(;;)
	{
		if(stack->isEmpty(stack))
			break;

		for(Node * temp = alg->adj[stack->popFront(stack)]; temp != NULL; temp = temp->next)
		{
			if(visited[*((int *)temp->data)] == 0) 
			{
				array[index++] = *((int *)temp->data);
			}
		}

		if(index > 0)
			sort(array, index);
//		fputs("|array 항목|\n", stdout);
//		for(int i = 0; i < alg->size; i++)
//		{
//			fprintf(stdout, "%4d", array[i]);
//		}
//		fputc('\n', stdout);

		for(int i = index - 1; i > -1; i--)
		{
			stack->pushFront(stack, array[i]);
		}

		if(visited[stack->front(stack)] == 0 && !stack->isEmpty(stack))
		{
			fprintf(stdout, "%d ", stack->front(stack) + 1);
			visited[stack->front(stack)] = 1;
		}

		memset(array, 0, sizeof(int) * alg->size);
		index = 0;
	}

	return ;
}

void BFS(AdjListGraph * alg, int * visited, int u)
{
	visited[u] = 1;
	fprintf(stdout, "%d ", u + 1);

	int * array = (int *)malloc(sizeof(int) * alg->size);
	int index = 0;

	List * queue = createList();
	queue->pushRear(queue, u);

	for(;;)
	{
		if(queue->isEmpty(queue))
			break;

		for(Node * temp = alg->adj[queue->popFront(queue)]; temp != NULL; temp = temp->next)
		{
			if(visited[*((int *)temp->data)] == 0)
			{
				array[index++] = *((int *)temp->data);
			}
		}

		if(index > 0)
			sort(array, index);

//		fprintf(stdout, "index : %d\n", index);
//		fputs("|array 항목|\n", stdout);
//		for(int i = 0; i < alg->size; i++)
//		{
//			fprintf(stdout, "%4d", array[i]);
//		}
//		fputc('\n', stdout);

		for(int i = 0; i < index; i++)
		{
			queue->pushRear(queue, array[i]);
		}
//		queue->display(queue);


		if(visited[queue->front(queue)] == 0 && !queue->isEmpty(queue))
		{
			fprintf(stdout, "%d ", queue->front(queue) + 1);
			visited[queue->front(queue)] = 1;
		}

		memset(array, 0, sizeof(int) * alg->size);
		index = 0;
	}

	return ;
}

void sort(int * array, int size)
{
	for(int i = 0 ; i < size - 1; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(array[i] > array[j])
			{
				swap(array + i, array + j);
			}
		}
	}

	return ;
}

void swap(int * a, int * b)
{
	int temp = 0;

	temp = *a;
	*a = *b;
	*b = temp;

	return ;
}

