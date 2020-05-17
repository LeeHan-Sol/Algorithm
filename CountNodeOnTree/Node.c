#include "Node.h"

Node * createNode(Node * parentNode, int data)
{
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->init = initNode;
	newNode->init(newNode, data);
	newNode->parent = parentNode;

	return newNode;
}

void initNode(Node * node, int data)
{
	node->data = data;
	node->countChild = 0;
	node->parent = NULL;
	node->child = NULL;

	node->addConnection = addConnection;
	node->setParent = setParent;
	node->swapRelation = swapRelation;

	node->display = displayNode;
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
			puts("ERROR : Node.c addConnection() (Node **)malloc()");
			return 1;
		}
	}
	else
	{
		uNode->child = realloc(uNode->child, sizeof(Node *) * uNode->countChild);
		if(uNode->child == NULL)
		{
			puts("ERROR : Node.c addConnection() (Node **)realloc()");
			return 1;
		}
	}

	uNode->child[uNode->countChild - 1] = (Node *)malloc(sizeof(Node));
	if(uNode->child[uNode->countChild - 1] == NULL)
	{
		puts("ERROR : Node.c addConnection() (Node *)malloc()");
		return 2;
	}

	uNode->child[uNode->countChild - 1] = vNode;
	
	return 0;
}

int setParent(Node * uNode, Node * vNode)
{
	//return 0: 정상종료, 1: 부모를 정할 수 없음
	if(vNode->parent == NULL)
	{
		vNode->parent = uNode;
	}
	else if(uNode->parent == NULL)
	{
		uNode->parent = vNode;
	}
	else
	{
		puts("ERROR : Node.c setParent() 부모를 정할 수 없습니다.\n");
		return 1;
	}
	
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
