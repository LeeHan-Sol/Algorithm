#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	int countChild;
	struct Node * parent;
	struct Node ** child;
	int totalNode;

	void (*init)(struct Node *, int);
	
	int (*addConnection)(struct Node *, struct Node *);
	int (*setParent)(struct Node *, struct Node *);
	struct Node * (*swapRelation)(struct Node *, struct Node *);

	void (*display)(struct Node *);
	void (*displayChild)(struct Node *);
}Node;

Node * createNode(int);

void initNode(Node *, int);

int addConnection(Node *, Node *);
int setParent(Node *, Node *);
Node * swapRelation(Node *, Node *);

void displayNode(Node *);
void displayChild(Node *);

#endif
