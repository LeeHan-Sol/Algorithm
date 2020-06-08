#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}List;

List * createList();
void initList(List *);

typedef struct AdjListGraph
{
	int size;
	int * vertices;
	Node ** adj;

	void (*init)(struct AdjListGraph);
}AdjListGraph;

AdjListGraph * createAdjListGraph();
void initAdjListGraph(AdjListGraph *);

int main()
{
	int n = 1;
	Node * node = createNode((char *)&n, NULL);

	fprintf(stdout, "node : %d[%p]\n", *((int *)node->data), node);
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
	node->data = data;
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

	return ;
}

AdjListGraph * createAdjListGraph(int size)
{
	AdjListGraph * new_alg = (AdjListGraph *)malloc(sizeof(AdjListGraph));
	if(new_alg == NULL)
	{
		fputs("new_alg fail malloc()\n", stderr);
		exit(1);
	}

	new_alg->init = initAdjListGraph;
	new_alg->init(new_alg, size);

	return new_alg;
}

void initAdjListGraph(AdjListGraph * alg, int size)
{
	alg->size = size;
	alg->vertices = (int *)malloc(sizeof(int) * size);
	if(alg->vertices == NULL)
	{
		fputs("alg->vertices fail malloc()\n", stderr);
		exit(1);
	}

	alg->adj = (Node **)malloc(sizeof(Node *) * size);
	if(alg->adj == NULL)
	{
		fputs("alg->adj fail malloc()\n", stderr);
		exit(1);
	}
	memset(alg->adj, 0x00, sizeof(Node **) * size);

	return ;
}
