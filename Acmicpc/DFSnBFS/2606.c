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

typedef struct AdjListGraph
{
	int size;
	int * vertices;
	Node ** adj;

	void (*init)(struct AdjListGraph *, int );
	int (*isEmpty)(struct AdjListGraph *);
	void (*display)(struct AdjListGraph *);
	void (*insertEdge)(struct AdjListGraph *, int, int);
	int (*DFS)(struct AdjListGraph *);
}AdjListGraph;

AdjListGraph * createAdjListGraph(int);
void initAdjListGraph(AdjListGraph *, int);
int isEmptyAdjListGraph(AdjListGraph *);
void displayAdjListGraph(AdjListGraph *);
void insertEdge(AdjListGraph *, int, int);
int DFS(AdjListGraph *);

int main()
{
	int n = 0, m = 0;
	scanf("%d", &n);
	getchar();
	if(0 > n || n > 100) return 0;
	
	scanf("%d", &m);
	getchar();

	AdjListGraph * alg = createAdjListGraph(n);
	
	for(int i = 0; i < m; i++)
	{
		int u = 0, v = 0;
		scanf("%d %d", &u, &v);
		
		alg->insertEdge(alg, u - 1, v - 1);
	}

//	alg->display(alg);

	fprintf(stdout, "%d\n", alg->DFS(alg));

	free(alg);

	return 0;
}

/*
int main()
{
	List * list = createList();

	for(int i = 0; i < 4; i++)
	{
		list->pushFront(list, i);
	}

	list->display(list);

	for(int i = 0; i < 2; i++)
	{
		list->popFront(list);
	}

	list->display(list);

	list->pushFront(list, 0);
	list->pushFront(list, 1);

	list->display(list);

	for(int i = 0; i < 4; i++)
	{
		list->popFront(list);
		list->display(list);
	}

	list->display(list);

	return 0;
}
*/

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
	for(int i = 0; i < size; i++)
	{
		alg->vertices[i] = i + 1;
	}

	alg->adj = (Node **)malloc(sizeof(Node *) * size);
	if(alg->adj == NULL)
	{
		fputs("alg->adj fail malloc()\n", stderr);
		exit(1);
	}
	memset(alg->adj, 0x00, sizeof(Node **) * size);

	alg->isEmpty = isEmptyAdjListGraph;
	alg->display = displayAdjListGraph;
	alg->insertEdge = insertEdge;
	alg->DFS = DFS;

	return ;
}

int isEmptyAdjListGraph(AdjListGraph * alg)
{
	return alg->size == 0 ? 1 : 0;
}

void displayAdjListGraph(AdjListGraph * alg)
{
	if(alg->isEmpty(alg))
	{
		return ;
	}

	fprintf(stdout, "정점의 개수 : %d\n", alg->size);
	for(int i = 0; i < alg->size; i++)
	{
		fprintf(stdout, "%3d   ", alg->vertices[i]);
		
		for(Node * temp = alg->adj[i]; temp != NULL; temp = temp->next)
		{
			fprintf(stdout, "%4d[%p]", *((int *)temp->data) + 1, temp->data);
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

int DFS(AdjListGraph * alg)
{
	int count = 0;

	int * visited = (int *)malloc(sizeof(int) * alg->size);
	memset(visited, 0, sizeof(int) * alg->size);

	List * queue = createList();
	queue->pushFront(queue, 0);
	visited[queue->peekFront(queue)] = 1;

	for(;;)
	{
		if(queue->isEmpty(queue))
		{
			break;
		}

		if(visited[queue->peekFront(queue)] == 0)
		{
			count++;
			visited[queue->peekFront(queue)] = 1;
//fprintf(stdout, "count :%d\n", count);
		}

		for(Node * temp = alg->adj[queue->popFront(queue)]; temp != NULL; temp = temp->next)
		{
//fprintf(stdout, "temp->data : %d\n", *((int *)temp->data)+1);
			if(visited[*((int *)temp->data)] == 0)
			{
//fprintf(stdout, "push : %d\n", *((int *)temp->data));
				queue->pushFront(queue, *((int *)temp->data));
			}
//queue->display(queue);

//			for(int i = 0; i < alg->size; i++)
//			{
//				fprintf(stdout, "%4d", visited[i]);
//			}
//			fputc('\n', stdout);
		}
	}

	free(visited);
	free(queue);
	return count;
}
