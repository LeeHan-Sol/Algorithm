#include "Tree.h"

/*
int main()
{
	Node * node = createNode(node, 1);
	Tree * tree = createTree();
	tree->root = node;

	for(int i = 0; i < 4; i++)
		node->addChild(node, i+2);

	node->display(node);

	for(int i = 0; i < 4; i++)
		node->display(node->child[i]);

	if(node->setParent(node, 0))
		node->parent->display(node->parent);
	puts("");

	tree->root = node->parent;

	fprintf(stdout, "tree 항목\n");
	tree->display(tree);
	fprintf(stdout, "tree, tree->root : [%p], [%p]\n", tree, tree->root);

	tree->addNode(tree, 3, 31);

	fprintf(stdout, "tree 항목\n");
	tree->display(tree);
	fprintf(stdout, "tree, tree->root : [%p], [%p]\n", tree, tree->root);

	return 0;
}
*/
/*
int main()
{
	Tree * tree = createTree();
	Node * node = (Node *)malloc(sizeof(Node));

	if(tree->addNode(tree, 2, 5)) printf("삽입\n");
	if(tree->addNode(tree, 1, 2)) printf("삽입\n");
	if(tree->addNode(tree, 1, 3)) printf("삽입\n");
	if(tree->addNode(tree, 2, 6)) printf("삽입\n");
	if(tree->addNode(tree, 2, 7)) printf("삽입\n");
	if(tree->addNode(tree, 3, 8)) printf("삽입\n");
	if(tree->addNode(tree, 1, 4)) printf("삽입\n");
	if(tree->addNode(tree, 4, 10)) printf("삽입\n");
	if(tree->addNode(tree, 4, 11)) printf("삽입\n");
	if(tree->addNode(tree, 4, 12)) printf("삽입\n");
	if(tree->addNode(tree, 4, 13)) printf("삽입\n");
	if(tree->addNode(tree, 3, 9)) printf("삽입\n");
	if(tree->addNode(tree, 0, 1)) printf("삽입\n");

	fprintf(stdout, "tree 항목\n");
	tree->display(tree);
	puts("");

	fprintf(stdout, "result : %d [%p]\n", (int)0, tree->searchData(tree, 0));
	puts("");

	fprintf(stdout, "result : %d [%p]\n", (int)1, node);
	puts("");

	node = tree->searchData(tree, 2);
	if(node != NULL)
	{
		fprintf(stdout, "result : %d [%p]\n", (int)2, node);
		puts("");
	}

	fprintf(stdout, "result : %d [%p]\n", (int)3, tree->searchData(tree, 3));
	puts("");

	fprintf(stdout, "tree 항목\n");
	tree->display(tree);
	puts("");

	return 0;
}
*/
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
