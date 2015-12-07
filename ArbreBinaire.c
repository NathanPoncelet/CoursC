#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

typedef struct node
{
	char* mot;
	int occur;
	struct node *left;
	struct node *right;
} node ;


