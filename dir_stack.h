#ifndef DIR_STACK_H

#include <dirent.h>
#include <sys/stat.h>

typedef struct dir_stack {
	char *name;
	int file_type;
	struct dir_stack *next;
} dir_stack;

void dir_stack_free(dir_stack *stack);
void dir_stack_stat(dir_stack **stack, const char *name,
		const struct stat *s);
void dir_stack_dirent(dir_stack **stack, const char *name,
		const struct dirent *de);
dir_stack *dir_stack_pop(dir_stack **stack);

#endif
