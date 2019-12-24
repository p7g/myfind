#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "dir_stack.h"

struct dir_stack *dir_stack_new(const char *name)
{
	static char path_buf[PATH_MAX];
	struct dir_stack *new;
	size_t len;

	realpath(name, path_buf);
	len = strlen(path_buf);

	new = malloc(sizeof(struct dir_stack));
	new->name = malloc(len + 1);
	strncpy(new->name, path_buf, len);
	new->name[len] = '\0';
	new->next = NULL;

	return new;
}

void dir_stack_push(struct dir_stack **stack, const char *name)
{
	struct dir_stack *new;

	new = dir_stack_new(name);
	new->next = *stack;
	*stack = new;
}

char *dir_stack_pop(struct dir_stack **stack)
{
	struct dir_stack *popped;
	char *name;

	popped = *stack;
	*stack = popped->next;
	name = popped->name;
	free(popped);

	return name;
}