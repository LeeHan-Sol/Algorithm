//스택
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int data;
	struct Node * next;

	void (*init)(struct Node *, int);
	void (*free)(struct Node *);
}Node;

Node * createNode(int);
void initNode(Node *, int);
void freeNode(Node *);

typedef struct Stack
{
	Node * head;

	void (*init)(struct Stack *);
	void (*free)(struct Stack *);

	void (*push)(struct Stack *, int);
	int (*pop)(struct Stack *);
	int (*size)(struct Stack *);
	int (*isEmpty)(struct Stack *);
	int (*top)(struct Stack *);
}Stack;

Stack * createStack();
void initStack(Stack *);
void freeStack(Stack *);

void push(Stack *, int);
int pop(Stack *);
int size(Stack *);
int isEmptyStack(Stack *);
int top(Stack *);

int main()
{
	int n = 0;
	scanf("%d", &n);
	getchar();

	char ** input = NULL;
	input = (char **)malloc(sizeof(char *) * n);
	if(input == NULL) return 0;
	for(int i = 0; i < n; i++)
	{
		*(input + i) = (char *)malloc(sizeof(char) * 16);
		memset(*(input + i), 0x00, 16);
		if(*(input + i) == NULL) return 0;
	}

	Stack * stack = createStack();

	for(int i = 0; i < n; i++)
	{
		fgets(*(input + i), 15, stdin);
	}

	for(int i = 0; i < n; i++)
	{
		if(strncmp(*(input + i), "push", 4) == 0)
		{
			int integer = 0;

			integer = atoi((*(input + i) + 5));

			stack->push(stack, integer);
		}
		else if(strncmp(*(input + i), "top", 3) == 0)
		{
			fprintf(stdout, "%d\n", stack->top(stack));
		}
		else if(strncmp(*(input + i), "size", 4) == 0)
		{
			fprintf(stdout, "%d\n", stack->size(stack));
		}
		else if(strncmp(*(input + i), "empty", 5) == 0)
		{
			fprintf(stdout, "%d\n", stack->isEmpty(stack));
		}
		else if(strncmp(*(input + i), "pop", 3) == 0)
		{
			fprintf(stdout, "%d\n", stack->pop(stack));
		}
	}

	stack->free(stack);
	return 0;
}

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
	node->next = NULL;

	node->free = freeNode;

	return ;
}

void freeNode(Node * node)
{
	node->data = 0;
	node->next = NULL;

	free(node);
	
	return ;
}

Stack * createStack()
{
	Stack * newStack = (Stack *)malloc(sizeof(Stack));

	newStack->init = initStack;
	newStack->init(newStack);

	return newStack;
}

void initStack(Stack * stack)
{
	stack->head = NULL;

	stack->free = freeStack;

	stack->push = push;
	stack->pop = pop;
	stack->size = size;
	stack->isEmpty = isEmptyStack;
	stack->top = top;

	return ;
}

void freeStack(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		free(stack);

		return ;
	}

	while(stack->head != NULL)
	{
		Node * node = stack->head;

		stack->head = stack->head->next;

		node->free(node);
		node = NULL;
	}

	stack->head = NULL;
	free(stack);

	return ;
}

void push(Stack * stack, int data)
{
	Node * node = createNode(data);

	if(stack->isEmpty(stack))
	{
		stack->head = node;

		return ;
	}

	node->next = stack->head;
	stack->head = node;

	return ;
}

int pop(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		return -1;
	}

	int pop = 0;
	Node * node = stack->head;
	stack->head = stack->head->next;
	
	pop = node->data;

	node->free(node);
	node = NULL;

	return pop;
}
int size(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		return 0;
	}

	int size = 0;

	for(Node * temp = stack->head; temp != NULL && ++size; temp = temp->next)
	{
	}
	
	return size;
}

int isEmptyStack(Stack * stack)
{
	return stack->head == NULL ? 1 : 0;
}

int top(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		return -1;
	}

	return stack->head->data; 
}

