#ifndef DIR_STACK_H

typedef struct dir_stack {
	char *name;
	struct dir_stack *next;
} dir_stack;

dir_stack *dir_stack_new(const char *name);
void dir_stack_push(dir_stack **stack, const char *name);
char *dir_stack_pop(dir_stack **stack);

#endif
