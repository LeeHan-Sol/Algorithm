#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char * data;
	struct Node * next;

	void (*init)(struct Node *, char *, struct Node *);
	void (*display)(struct Node *);
}Node;

Node * createNode(char * data, Node * next);
void initNode(Node * node, char * data, Node * next);
void displayNode(Node * node);

typedef struct List
{
	int size;
	Node * head;
	Node * tail;

	void (*init)(struct List *);
	int (*isEmpty)(struct List *);
	void (*pushRear)(struct List *, int);
	int (*popFront)(struct List *);
	int (*peekFront)(struct List *);
	void (*display)(struct List *);
}List;

List * createList();
void initList(List * list);
int isEmptyList(List * list);
void pushRear(List * list, int data);
int popFront(List * list);
int peekFront(List * list);
void displayList(List * list);

typedef struct AdjGraph
{
	int size;
	int * vertices;
	int * parent;
	Node ** adj;

	void (*init)(struct AdjGraph *, int size);
	void (*insertEdge)(struct AdjGraph *, int u, int v);
	void (*setRoot)(struct AdjGraph *, int);
	void (*display)(struct AdjGraph *);
	void (*displayParent)(struct AdjGraph *);
}AdjGraph;

AdjGraph * createAdjGraph(int size);
void initAdjGraph(AdjGraph * adjGraph, int size);
void insertEdge(AdjGraph * adjGraph, int u, int v);
void setRoot(AdjGraph * adjGraph, int root);
void displayAdjGraph(AdjGraph * adjGraph);
void displayParent(AdjGraph * adjGraph);

int main()
{
	int n = 0;
	scanf("%d", &n);
	getchar();
	if(2 > n || n > 100000) return 0;		
	int u = 0, v = 0;

	AdjGraph * adjGraph = createAdjGraph(n);

	for(int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &u, &v);

		adjGraph->insertEdge(adjGraph, u-1, v-1);
	}

//	adjGraph->display(adjGraph);

	adjGraph->setRoot(adjGraph, 0);
	adjGraph->displayParent(adjGraph);

	return 0;
}

Node * createNode(char * data, Node * next)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;
	newNode->init(newNode, data, next);

	return newNode;
}

void initNode(Node * node, char * data, Node * next)
{
	node->data = (char *)malloc(sizeof(char));

	*((int *)node->data) = *((int *)data);
	node->next = next;

	node->display = displayNode;

//	fprintf(stdout, "node : [%p]\n", node);
//	fprintf(stdout, "data : %d[%p]\n", *((int *)node->data), node->data);
//	fprintf(stdout, "next : [%p]\n", next);

	return;
}

void displayNode(Node * node)
{
	fprintf(stdout, "%4d", *((int *)node->data));

	return;
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
	list->pushRear = pushRear;
	list->popFront = popFront;
	list->peekFront = peekFront;
	list->display = displayList;

	return;
}

int isEmptyList(List * list)
{
	return list->size == 0 ? 1 : 0;
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

int popFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}

	Node * temp = list->head;
	int result = *((int *)temp->data);
	list->head = list->head->next;
	if(list->head == NULL)
	{
		list->tail = NULL;
	}

	free(temp->data);
	free(temp);
	list->size--;

	return result;
}

int peekFront(List * list)
{
	if(list->isEmpty(list))
	{
		return -1;
	}
	
	int result = *((int *)list->head->data);

	return result;
}

void displayList(List * list)
{
	if(list->isEmpty(list))
	{
		return;
	}

	for(Node * temp = list->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%4d", *((int *)temp->data));	
	}

	return ;
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
	if(adjGraph->vertices == NULL)
	{
		fputs("adjGraph->vertices malloc() error\n", stderr);
		return;
	}
	for(int i = 0; i < size; i++)
	{
		adjGraph->vertices[i] = i;
	}

	adjGraph->parent = (int *)malloc(sizeof(int) * size);
	if(adjGraph->parent == NULL)
	{
		fputs("adjGraph->parent malloc() error\n", stderr);
		return;
	}
	for(int i = 0; i < size; i++)
	{
		adjGraph->parent[i] = -1;
	}

	adjGraph->adj = (Node **)malloc(sizeof(Node) * size);
	if(adjGraph->adj == NULL)
	{
		fputs("adjGraph->adj malloc() error\n", stderr);
		return;
	}

	adjGraph->insertEdge = insertEdge;
	adjGraph->setRoot = setRoot;
	adjGraph->display = displayAdjGraph;
	adjGraph->displayParent = displayParent;

	return;
}

void insertEdge(AdjGraph * adjGraph, int u, int v)
{
	adjGraph->adj[u] = createNode((char *)&v, adjGraph->adj[u]);
	adjGraph->adj[v] = createNode((char *)&u, adjGraph->adj[v]);

	return;
}

void setRoot(AdjGraph * adjGraph, int root)
{
	adjGraph->parent[root] = -1;
	int i = root;
	List * list = createList();

	for(;;)
	{
		for(Node * temp = adjGraph->adj[i]; temp != NULL; temp = temp->next)
		{
			if(adjGraph->parent[*((int *)temp->data)] == -1)
			{
				adjGraph->parent[*((int *)temp->data)] = i;
				list->pushRear(list, *((int *)temp->data));
//				fprintf(stdout, "\t\ttemp->data, i : %d, %d\n", *((int *)temp->data), i);
			}
		}
		if(list->isEmpty(list)) break;
		i = list->popFront(list);
//		fprintf(stdout, "\t\tlist->pop : %d\n", i);
	}
}

void displayAdjGraph(AdjGraph * adjGraph)
{
	for(int i = 0; i < adjGraph->size; i++)
	{
		fprintf(stdout, "%3d", adjGraph->vertices[i]);

		for(Node * temp = adjGraph->adj[i]; temp != NULL; temp = temp->next)
		{
			fprintf(stdout, "%5d", *((int *)temp->data));
		}
		fputc('\n', stdout);
	}

	return;
}

void displayParent(AdjGraph * adjGraph)
{
	for(int i = 1; i < adjGraph->size; i++)
	{
		fprintf(stdout, "%d\n", adjGraph->parent[i] + 1);
	}
}
