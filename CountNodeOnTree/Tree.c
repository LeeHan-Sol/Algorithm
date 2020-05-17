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

	tree->addNode = addNode;

	tree->searchData = searchData;
	tree->countNode = countNode;

	tree->display = displayTree;
}

int isEmptyTree(Tree * tree)
{
	return tree->root == NULL ? 1 : 0;
}

void setRoot(Tree * tree, int data)
{
	Node * node = tree->searchData(tree, data);

	if(node->parent == NULL)
		tree->root = node;
	else
	{
		tree->root = node->swapRelation(node, node->parent);	
	}

	node->parent = NULL;
}

int addNode(Tree * tree, int u, int v)
{	
	Node * uNode = searchData(tree, u);
	if(uNode == NULL)
	{
		uNode = createNode(uNode, u);
	}

	Node * vNode = searchData(tree, v);
	if(vNode == NULL)
	{
		vNode = createNode(vNode, v);
	}

	if(tree->isEmpty(tree))
	{
		tree->root = uNode;
	}

	uNode->addConnection(uNode, vNode);
	vNode->addConnection(vNode, uNode);

	uNode->setParent(uNode, vNode);

	return 0;
}

Node * searchData(Tree * tree, int data)
{
	if(tree->isEmpty(tree))
	{
//		fprintf(stdout, "Tree.c searchData() tree가 비어있습니다.\n");
		return (Node *)NULL;
	}

	Item * item = createItem(tree->root);
	List * list = createList();

	list->pushFront(list, item);

	while((item = list->peekFront(list)) != NULL)
	{
		if(item->node->data == data)
		{
			Node * temp = item->node;
			
			list->free(list);

			return temp;
		}
	
		for(int i = 0; i < item->node->countChild; i++)
		{
			if(item->node->child[i] != item->node->parent)
				list->pushRear(list, createItem(item->node->child[i]));
		}
		
		list->popFront(list);
	}
	
	return (Node *)NULL;
}

int countNode(Tree * tree, int data)
{
	if(tree->isEmpty(tree))
	{
		puts("Tree.c countNode() tree가 비어있습니다.");
		return 0;
	}

	Node * tempRoot = searchData(tree, data);
	if(tempRoot == NULL)
	{
		puts("Tree.c countNode() %d 데이터를 찾을 수 없습니다.");
		return 0;
	}

	int count = 0;

	List * list = createList();

	list->pushFront(list, createItem(tempRoot));

	Item * temp = NULL;

	while((temp = list->peekFront(list)) != NULL)
	{
		for(int i = 0; i < temp->node->countChild; i++)
		{
			if(temp->node->child[i] != temp->node->parent)
			{
				list->pushRear(list, createItem(temp->node->child[i]));
			}
		}

		list->popFront(list);
		count++;
	}
		
		return count;
}

void displayTree(Tree * tree)
{
	if(tree->isEmpty(tree))
	{
		fprintf(stdout, "tree가 비었습니다.\n");
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
