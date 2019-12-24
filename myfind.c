#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir_stack.h"
#include "paths.h"

int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dir;
	dir_stack *stack;
	char *joined, *current;

	if (argc < 2) {
		printf("USAGE:\n\tmyfind DIR [OPTS]\n");
		exit(1);
	}

	stack = dir_stack_new(argv[1]);

	while (stack) {
		dirp = opendir(stack->name);

		current = dir_stack_pop(&stack);

		if (dirp == NULL) {
			perror("opendir");
			continue;
		}

		while ((dir = readdir(dirp))) {
			joined = path_join(current, dir->d_name);

			if (dir->d_type == DT_DIR) {
				if (exclude_p(dir->d_name))
					continue;
				dir_stack_push(&stack, joined);
			} else {
				printf("%s\n", joined);
			}

			free(joined);
		}

		free(current);
		closedir(dirp);
	}

	return 0;
}
