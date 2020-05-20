//스택 수열
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
	void (*clear)(struct Stack *);

	void (*push)(struct Stack *, int);
	int (*pop)(struct Stack *);
	int (*size)(struct Stack *);
	int (*isEmpty)(struct Stack *);
	int (*top)(struct Stack *);
	void (*display)(struct Stack *);
}Stack;

Stack * createStack();
void initStack(Stack *);
void freeStack(Stack *);
void clearStack(Stack *);

void push(Stack *, int);
int pop(Stack *);
int size(Stack *);
int isEmptyStack(Stack *);
int top(Stack *);
void displayStack(Stack *);

int main()
{
	int n = 0;
	int max = 2;

	scanf("%d", &n);
	if(1 > n || n > 100000) return 0;

	int * sequence = (int *)malloc(sizeof(int) * n);
	if(sequence == NULL) return 0;
	memset(sequence, 0, n);

	int sp = 0;
	int * stackProcess = (int *)malloc(sizeof(int) * n * 2);
	if(stackProcess == NULL) return 0;
//	memset(stackProcess, -1, n*2);

	Stack * stack = createStack();

	for(int i = 0; i < n; i++)
		scanf("%d", (sequence + i));

//	for(int i = 0; i < n; i++)
//		fprintf(stdout, "%4d", *(sequence + i));

	stack->push(stack, 1);
	stackProcess[sp] = 1;
	sp++;

	for(int i = 0; i < n; i++)
	{
//		fprintf(stdout, "sequence, top : %d, %d\n", sequence[i], stack->top(stack));
		if(sequence[i] > stack->top(stack))
		{
			for(; sequence[i] > stack->top(stack); max++)
			{
//				fprintf(stdout, "\t\t j : %d\n", j);
				stack->push(stack, max);
				stackProcess[sp] = 1;
				sp++;
			}
			
//			fprintf(stdout, "\t\ttop : %d\n", stack->top(stack));
		}

		if(sequence[i] == stack->top(stack))
		{
//			fprintf(stdout, "\tpop : %d\n", stack->top(stack));
			stack->pop(stack);
			stackProcess[sp] = 0;
			sp++;
		}
		else if(sequence[i] < stack->top(stack))
		{
			stackProcess[0] = -1;
			break;
		}
	}

	for(int i = 0; i < n*2; i++)
	{
		if(stackProcess[i] == -1)
		{
			fprintf(stdout, "NO\n");
			break;
		}
		else if(stackProcess[i] == 0)
		{
			fprintf(stdout, "-\n");
		}
		else if(stackProcess[i] == 1)
		{
			fprintf(stdout, "+\n");
		}
	}

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
	stack->clear = clearStack;

	stack->push = push;
	stack->pop = pop;
	stack->size = size;
	stack->isEmpty = isEmptyStack;
	stack->top = top;
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
		return 0;
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

void displayStack(Stack * stack)
{
	if(stack->isEmpty(stack))
	{
		fprintf(stdout, "stack이 비어있습니다.\n");

		return ;
	}

	for(Node * temp = stack->head; temp != NULL; temp = temp->next)
	{
		fprintf(stdout, "%4d", temp->data);
	}
	puts("");

	return ;
}
