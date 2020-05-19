#include "Tree.h"

Tree * createTree()
{
	Tree * newTree = (Tree *)malloc(sizeof(Tree));

	newTree->init = initTree;
	newTree->init(newTree);

	return newTree;
}

void initTree(Tree * tree)
{
	tree->root = NULL;

	tree->isEmpty = isEmptyTree;
	tree->setRoot = setRoot;

	tree->countNode = countNode;

	tree->display = displayTree;
}

int isEmptyTree(Tree * tree)
{
	return tree->root == NULL ? 1 : 0;
}

void setRoot(Tree * tree, List * list, int * countNode, int data)
{
	Item * item = NULL;

	if(list->searchData(list, data) == NULL)
	{
		return ;
	}

	item = list->searchData(list, data);
	tree->root = item->node;
	tree->root->parent = NULL;
	
	list->clear(list);

	list->pushFront(list, item);

	for(item = list->head; item != NULL; item = item->next)
	{
		for(int i = 0; i < item->node->countChild; i++)
		{
			if(item->node->child[i] != item->node->parent)
			{
				item->node->child[i]->setParent(item->node, item->node->child[i]);
				list->pushRear(list, createItem(item->node->child[i]));
			}
		}
		
//		list->popFront(list);
	}

//	list->display(list);
//	puts("");

//	fprintf(stdout, "list->tail : %d [%p]\n", list->tail->node->data, list->tail);
	for(item = list->tail; item != NULL; item = item->prev)
	{
//			fprintf(stdout, "item->node, item, item->prev, item->next : %d [%p], [%p], [%p], [%p]\n", item->node->data, item->node, item, item->prev, item->next);
		if(item->node->countChild == 0)
		{
			item->node->parent->totalNode++;
		}
		else
		{
			if(item->node->parent != NULL)
				item->node->parent->totalNode += item->node->totalNode;
		}
		
//		if(item->node->parent != NULL)
//			fprintf(stdout, "item->node->parent & ->totalNode : %d, %d\n", item->node->parent->data, item->node->parent->totalNode);
//		puts("");
		countNode[item->node->data - 1] = item->node->totalNode;
	}
	
	return ;
}

int countNode(Tree * tree, List * list, int data)
{
	Item * item = list->searchData(list, data);

	return item->node->totalNode;
}

void displayTree(Tree * tree)
{
	if(tree->isEmpty(tree))
	{
//		fprintf(stdout, "tree가 비었습니다.\n");
		return ;
	}

	List * list = createList();

	list->pushFront(list, createItem(tree->root));

	while(list->peekFront(list) != NULL)
	{
		for(int i = 0; i < list->peekFront(list)->node->countChild; i++)
		{
			if(list->peekFront(list)->node->child[i] != list->peekFront(list)->node->parent)
				list->pushRear(list, createItem(list->peekFront(list)->node->child[i]));
		}
		
		list->peekFront(list)->node->display(list->peekFront(list)->node);
		list->popFront(list);
	}

	return ;
}
