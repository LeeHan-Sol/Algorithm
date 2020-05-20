//괄호
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
	void (*clear)(struct Stack *);
	int (*size)(struct Stack *);
	int (*isEmpty)(struct Stack *);
	int (*top)(struct Stack *);
	void (*display)(struct Stack *);
}Stack;

Stack * createStack();
void initStack(Stack *);
void freeStack(Stack *);

void push(Stack *, int);
int pop(Stack *);
void clearStack(Stack *);
int size(Stack *);
int isEmptyStack(Stack *);
int top(Stack *);
void displayStack(Stack *);

int main()
{
	int n = 0;
	
	scanf("%d", &n);
	getchar();

	int * result = (int *)malloc(sizeof(int) * n);
	memset(result, 0, n);

	char ** string = (char **)malloc(sizeof(char *) * n);
	if(string == NULL) return 0;

	for(int i = 0; i < n; i++)
	{
		*(string + i) = (char *)malloc(sizeof(char) * 52); 
		if(*(string + i) == NULL) return 0;
		memset(*(string + i), 0, 52);
	}

	Stack * stack = createStack();

	for(int i = 0; i < n; i++)
	{
		fgets((*(string + i)), 52, stdin);
		int length = strlen((*(string + i))) - 1;
		if(length < 2 || length > 50) return 0;
//		*(*(string + i) + strlen(*(string + i)) - 1) = 0x00;
	}

	for(int i = 0; i < n; i++)
	{
		int length = strlen((*(string + i))) - 1;
		for(int j = 0; j < length; j++)
		{
			if(strncmp((*(string + i) + j), "(", 1) == 0)
			{
				stack->push(stack, 0);
			}
			else
			{
				if(stack->top(stack) == 0) stack->pop(stack);
				else stack->push(stack, 1);
			}
		}

		if(stack->top(stack) == -1)
		{
			*(result + i) = 1;
		}
		else
		{
			*(result + i) = 0;
		}

		stack->clear(stack);
	}

	for(int i = 0; i < n; i++)
	{
		if(*(result + i) == 1) fprintf(stdout, "YES");
		else fprintf(stdout, "NO");
		fprintf(stdout, "\n");
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
	stack->clear = clearStack;
	stack->display = displayStack;

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

void clearStack(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		return ;
	}

	for(int i = stack->size(stack); i > 0; i--)
	{
		stack->pop(stack);
	}
	
	stack->head = NULL;
	
	return ;
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

void displayStack(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		fprintf(stdout, "stack이 비어있습니다.");
	}

	for(Node * node = stack->head; node != NULL; node = node->next)
	{
		fprintf(stdout, "%4d", node->data);
	}
	puts("");

	return ;
}
