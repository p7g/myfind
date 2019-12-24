#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "dir_stack.h"
#include "file_type.h"
#include "options.h"

static struct dir_stack *dir_stack_new(const char *name, int ft)
{
	struct dir_stack *new;
	size_t len;

	len = strlen(name);
	new = malloc(sizeof(struct dir_stack));
	new->name = malloc(len + 1);
	strncpy(new->name, name, len);
	new->name[len] = '\0';
	new->next = NULL;
	new->file_type = ft;

	return new;
}

static void dir_stack_push(struct dir_stack **stack, const char *name, int ft)
{
	struct dir_stack *new;

	new = dir_stack_new(name, ft);
	new->next = *stack;
	*stack = new;
}

void dir_stack_stat(dir_stack **stack, const char *name,
		const struct stat *s)
{
	dir_stack_push(stack, name, mask_from_mode_t(s->st_mode));
}

void dir_stack_dirent(dir_stack **stack, const char *name,
		const struct dirent *de)
{
	dir_stack_push(stack, name, mask_from_d_type(de->d_type));
}

dir_stack *dir_stack_pop(struct dir_stack **stack)
{
	struct dir_stack *popped;

	popped = *stack;
	*stack = popped->next;

	return popped;
}

void dir_stack_free(dir_stack *stack)
{
	free(stack->name);
	free(stack);
}
