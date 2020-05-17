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
	void (*setRoot)(struct Tree *, int);

	int (*addNode)(struct Tree *, int, int);

	Node * (*searchData)(struct Tree *, int);
	int (*countNode)(struct Tree *, int);

	void (*display)(struct Tree *);
}Tree;

Tree * createTree();

void initTree(Tree *);
int isEmptyTree(Tree *);
void setRoot(Tree *, int); 

int addNode(Tree *, int, int);

Node * searchData(Tree *, int);
int countNode(Tree *, int);

void displayTree(Tree *);

#endif
