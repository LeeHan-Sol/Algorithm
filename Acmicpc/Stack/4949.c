//균형잡힌 세상
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
	int count = 0;
	int size = 2;
	int * result = (int *)malloc(sizeof(int));

	char * string = (char *)malloc(sizeof(char) * 104);
	memset(string, 0, 104);

	Stack * stack = createStack();

	for(;;)
	{
		fgets(string, 104, stdin);
		string[strlen(string) - 1] = 0x00;
		int length = strlen(string);
		if(length > 101) break;

		if(strncmp((string + 0), ".", 1) == 0) break;
//		fprintf(stdout, "length : %ld\n", strlen(string));
//		fprintf(stdout, "문자열\n%s\n", string);

		count++;
		if(count == size)
		{
			size *= 2;
			result = realloc(result, sizeof(int) * size);
		}


		for(int i = 0; i < length; i++)
		{
			if(strncmp((string + i), "(", 1) == 0)
			{
				stack->push(stack, 2);
			}
			else if(strncmp((string + i), "[", 1) == 0)
			{
				stack->push(stack, 3);
			}
			else if(strncmp((string + i), ")", 1) == 0)
			{
				if(stack->top(stack) == 2) stack->pop(stack);
				else
				{
					stack->push(stack, -2);
				}
			}
			else if(strncmp((string + i), "]", 1) == 0)
			{
				if(stack->top(stack) == 3) stack->pop(stack);
				else
				{
					stack->push(stack, -3);
				}
			}
		}

		if(stack->top(stack) == -1)
		{
			result[count - 1] = 1;
		}
		else
		{
			result[count - 1] = 0;
		}
		
//		stack->display(stack);
		stack->clear(stack);
		for(int i = 0 ; i < strlen(string); i++)
			memset(string + i, 0, 1);
	}

	for(int i = 0; i < count; i++)
	{
		fprintf(stdout, "%s\n", result[i] == 1 ? "yes" : "no");
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
