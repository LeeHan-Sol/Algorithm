#include "Tree.h"

int main()
{
	int n = 0, r = 0, q = 0;
	scanf("%d %d %d", &n, &r, &q);

	List * list = createList();
	int * quary = (int *)malloc(sizeof(int) * q);
	if(quary == NULL)
	{
		return 0;
	}

	int * countNode = (int *)malloc(sizeof(int) * n);
	if(countNode == NULL)
	{
		return 0;
	}

	for(int i = 0; i < n - 1; i++)
	{
		int u = 0, v = 0;
		scanf("%d %d", &u, &v);

		list->pushData(list, u, v);	
	}

//	list->display(list);
//	puts("");

	Tree * tree = createTree();
	
	tree->setRoot(tree, list, countNode, r);
//	fprintf(stdout, "tree->root : %d\n", tree->root->data);

//	list->display(list);
//	puts("");

//	tree->display(tree);
//	puts("");

	for(int i = 0; i < q; i++)
	{
		scanf("%d", quary + i);
	}

	for(int i = 0; i < q; i++)
	{
		int count = countNode[*(quary + i) - 1];
		fprintf(stdout, "%d\n", count);
	}

	return 0;
}

/*
 * FIN_main()
int main()
{
	int n = 0, r = 0, q = 0;
	int * quary = NULL;

	Tree * tree = createTree();

	scanf("%d %d %d", &n, &r, &q);

	quary = (int *)malloc(sizeof(int) * q);

	for(int i = 0; i < n - 1; i++)
	{
		int u = 0, v = 0;
		scanf("%d %d", &u, &v);
		
		tree->addNode(tree, u, v);
	}

	puts("tree 항목");
	tree->display(tree);
	puts("");

	printf("after tree->setRoot(%d)\n", r);
	tree->setRoot(tree, r);
	tree->display(tree);
	puts("");

	for(int i = 0; i < q; i++)
	{
		scanf("%d", quary + i);
	}
	puts("");

	for(int i = 0; i < q; i++)
	{
		int count = tree->countNode(tree, *(quary + i));

		printf("%d\n", count);
	}
	
	return 0;
}
*/
