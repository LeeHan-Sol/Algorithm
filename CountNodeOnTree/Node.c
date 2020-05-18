#include "Node.h"

Node * createNode(int data)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;
	newNode->init(newNode, data);

	return newNode;
}

void initNode(Node * node, int data)
{
	node->data = data;
	node->countChild = 0;
	node->parent = NULL;
	node->child = NULL;
	node->totalNode = 1;

	node->addConnection = addConnection;
	node->setParent = setParent;
	node->swapRelation = swapRelation;

	node->display = displayNode;
	node->displayChild = displayChild;
}

int addConnection(Node * uNode, Node * vNode)
{
	//return 0: 정상 종료, 1: 동적할당 **오류 2: 동적할당 *오류
	uNode->countChild++;

	if(uNode->countChild == 1)
	{
		uNode->child = (Node **)malloc(sizeof(Node *));
		if(uNode->child == NULL)
		{
//			puts("ERROR : Node.c addConnection() (Node **)malloc()");
			return 1;
		}
	}
	else
	{
		uNode->child = realloc(uNode->child, sizeof(Node *) * uNode->countChild);
		if(uNode->child == NULL)
		{
//			puts("ERROR : Node.c addConnection() (Node **)realloc()");
			return 1;
		}
	}

	uNode->child[uNode->countChild - 1] = (Node *)malloc(sizeof(Node));
	if(uNode->child[uNode->countChild - 1] == NULL)
	{
//		puts("ERROR : Node.c addConnection() (Node *)malloc()");
		return 2;
	}

	uNode->child[uNode->countChild - 1] = vNode;
	
	return 0;
}

int setParent(Node * uNode, Node * vNode)
{
	vNode->parent = uNode;

	return 0;
}

Node * swapRelation(Node * currentNode, Node * parentNode)
{
	if(parentNode != NULL)
	{
		Node * temp = parentNode->parent;
		if(temp != NULL)
		{
			swapRelation(parentNode, temp);

			parentNode->parent = currentNode;		
		}
		else
		{
			parentNode->parent = currentNode;
		}
	}

	return currentNode;
}

void displayNode(Node * node)
{
	printf("%d [%p] ", node->data, node);
	if(node->parent != NULL)
		printf("부모 : %d\n", node->parent->data);
	else
		puts("");
}

void displayChild(Node * node)
{
	for(int i = 0; i < node->countChild; i++)
	{
		fprintf(stdout, "%4d", node->child[i]->data);
	}
	puts("");
}
