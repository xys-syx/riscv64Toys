#include <time.h>
#include <stdio.h>

#include "collections.h"


typedef struct {
	int value;
} item;

static int itemComparer(void* a, void* b)
{
	if (((item*)a)->value > ((item*)b)->value)
		return 1;
	else if (((item*)a)->value < ((item*)b)->value)
		return -1;
	else
		return 0;
}

static void itemDtor(void* x, void* y)
{
	UNUSED(y);
	free(x);
}

static void itemPrinter(void* x, void* y)
{
	UNUSED(y);
	printf("  %d", ((item*)x)->value);
}

static item* makeItem(int value)
{
	item* x = allocStruct(item);
	x->value = value;
	return x;
}

void treeTest(void);

void treeTest()
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	srand(ts.tv_nsec / 1000);

	RbTree* tree = createRbTree(itemComparer, itemDtor, itemPrinter);
	for (int i = 0; i < 20; i++)
	{
		int value = rand() * 100l / RAND_MAX;
		printf("add %d\n", value);

		if (tryAddRbTreeItem(tree, makeItem(value), NULL))
		{
			traceRbTree(tree);
			printf("\n");
		}
	}
	releaseRbTree(tree);
}