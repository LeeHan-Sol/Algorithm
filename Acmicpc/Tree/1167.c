#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char * data;
	int weight;
	struct Node * prev;
	struct Node * next;

	void (*init)(struct Node * node, int data, int weight, struct Node * prev, struct Node * next);
	void (*display)(struct Node * node);
	void (*free)(struct Node * node);
}Node;

Node * createNode(int data, int weight, Node * prev, Node * next);
void initNode(Node * node, int data, int weight, Node * prev, Node * next);
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
	void (*pushFront)(struct List * list, int data, int weight);
	void (*pushRear)(struct List * list, int data, int weight);
	int (*popFront)(struct List * list);
	int (*popRear)(struct List * list);
}List;

List * createList();
void initList(List * list);
int isEmptyList(List * list);
void displayList(List * list);
void rDisplayList(List * list);
void pushFront(List * list, int data, int weight);
void pushRear(List * list, int data, int weight);
int popFront(List * list);
int popRear(List * list);

typedef struct AdjGraph
{
	int size;
	int * vertices;
	int * max_weight;
	Node ** adj;

	void (*init)(struct AdjGraph * adjGraph, int size);
	int (*isEmpty)(struct AdjGraph * adjGraph);
	void (*display)(struct AdjGraph * adjGraph);
	void (*insert)(struct AdjGraph * adjGraph, int u, int weight, int v);
}AdjGraph;

AdjGraph * createAdjGraph(int size);
void initAdjGraph(AdjGraph * adjGraph, int size);
int isEmptyAdjGraph(AdjGraph * adjGraph);
void displayAdjGraph(AdjGraph * adjGraph);
void insert(AdjGraph * adjGraph, int u, int v, int weight);

int main()
{
	int n = 0;
	scanf("%d", &n);
	getchar();
	if(2 > n || n > 100000) return 0;

	AdjGraph * adjGraph = createAdjGraph(n);

	for(int i = 0; i < n; i++)
	{
		int u = 0;
		scanf("%d", &u);
		getchar();

		for(;;)
		{
			int v = 0, weight = 0;
			scanf("%d", &v);
			getchar();
			if(v == -1)
				break;
			scanf("%d", &weight);
			getchar();

			adjGraph->insert(adjGraph, u - 1, v - 1, weight);
		}
	}

	adjGraph->display(adjGraph);

//	List * list = createList();
//
//	for(int i = 0; i < 10; i++)
//	{
//		list->pushFront(list, i, 1);
//	}
//	for(int i = 1; i < 10; i++)
//	{
//		list->pushRear(list, i, 1);
//	}
//	list->display(list);
//	list->rDisplay(list);
//	
//	for(int i = 0; i < 10; i++)
//	{
//		list->popFront(list);
//	}
//	list->display(list);
//	list->rDisplay(list);
//	
//	for(int i = 0; i < 10; i++)
//	{
//		list->popRear(list);
//	}
//	list->display(list);
//	list->rDisplay(list);
//	
//	for(int i = 0; i < 5; i++)
//	{
//		list->pushRear(list, i, 1);
//	}
//	for(int i = 0; i < 3; i++)
//	{
//		list->popFront(list);
//	}
//	for(int i = 0; i < 2; i++)
//	{
//		list->popFront(list);
//	}
//	list->display(list);
//	list->rDisplay(list);

	return 0;
}

Node * createNode(int data, int weight, Node * prev, Node * next)
{
	Node * newNode = (Node *)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		fprintf(stdout, "newNode malloc() error\n");
		exit(1);
	}

	newNode->init = initNode;
	newNode->init(newNode, data, weight, prev, next);

	return newNode;
}

void initNode(Node * node, int data, int weight, Node * prev, Node * next)
{
	node->data = (char *)malloc(sizeof(char) * 4);
	*((int *)node->data) = data;
	node->weight = weight;
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

void pushFront(List * list, int data, int weight)
{
	if(list->isEmpty(list))
	{
		list->head = createNode(data, weight, NULL, NULL);
		list->tail = list->head;
		list->size++;

		return ;
	}

	list->head->prev = createNode(data, weight, NULL, list->head);	
	list->head = list->head->prev;
	list->size++;

	return ;
}

void pushRear(List * list, int data, int weight)
{
	if(list->isEmpty(list))
	{
		list->head = createNode(data, weight, NULL, NULL);
		list->tail = list->head;
		list->size++;

		return ;
	}

	list->tail->next = createNode(data, weight, list->tail, NULL);
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


AdjGraph * createAdjGraph(int size)
{
	AdjGraph * newAdjGraph = (AdjGraph *)malloc(sizeof(AdjGraph));
	newAdjGraph->init = initAdjGraph;
	newAdjGraph->init(newAdjGraph, size);

	return newAdjGraph;
}

void initAdjGraph(AdjGraph * adjGraph, int size)
{
	adjGraph->size = size;
	adjGraph->vertices = (int *)malloc(sizeof(int) * size);
	for(int i = 0 ; i < size; i++)
	{
		adjGraph->vertices[i] = i;
	}
	adjGraph->max_weight = (int *)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++)
	{
		adjGraph->max_weight[i] = 0;
	}
	
	adjGraph->adj = (Node **)malloc(sizeof(Node *) * size);

	adjGraph->isEmpty = isEmptyAdjGraph;
	adjGraph->display = displayAdjGraph;
	adjGraph->insert = insert;
}

int isEmptyAdjGraph(AdjGraph * adjGraph)
{
	return adjGraph->size == 0 ? 1 : 0;
}

void displayAdjGraph(AdjGraph * adjGraph)
{
	if(adjGraph->isEmpty(adjGraph))
	{
		return ;
	}

	for(int i = 0; i < adjGraph->size; i++)
	{
		fprintf(stdout, "%3d", adjGraph->vertices[i] + 1);

		for(Node * temp = adjGraph->adj[i]; temp != NULL; temp = temp->next)
		{
			fprintf(stdout, "%5d(%2d)", *((int *)temp->data) + 1, temp->weight);
		}
		fprintf(stdout, "\n");
	}

	return ;
}

void insert(AdjGraph * adjGraph, int u, int v, int weight)
{
	adjGraph->adj[u] = createNode(v, weight, NULL, adjGraph->adj[u]);
//	adjGraph->adj[v] = createNode(u, weight, NULL, adjGraph->adj[v]);

	return ;
}
