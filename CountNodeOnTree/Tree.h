#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "List.h"

typedef struct Tree
{
	Node * root;

	void (*init)(struct Tree *);
	int (*isEmpty)(struct Tree *);
	void (*setRoot)(struct Tree *, List *, int);

	int (*addNode)(struct Tree *, int, int);

	int (*countNode)(struct Tree *, List *, int);

	void (*display)(struct Tree *);
}Tree;

Tree * createTree();

void initTree(Tree *);
int isEmptyTree(Tree *);
void setRoot(Tree *, List *, int); 

int addNode(Tree *, int, int);

int countNode(Tree *, List *, int);

void displayTree(Tree *);

#endif
