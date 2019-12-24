#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir_stack.h"
#include "options.h"
#include "paths.h"

static void usage()
{
	fprintf(stderr, "USAGE:\n\tmyfind DIR [OPTS]\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dir;
	dir_stack *stack;
	char *joined, *current;
	struct args args;

	if (parse_args(argc, argv, &args))
		usage();

	stack = dir_stack_new(args.directory);

	while (stack) {
		dirp = opendir(stack->name);
		current = dir_stack_pop(&stack);

		if (dirp == NULL) {
			perror("opendir");
			continue;
		}

		while ((dir = readdir(dirp))) {
			joined = path_join(current, dir->d_name);

			if (dir->d_type == DT_DIR && !exclude_p(dir->d_name))
				dir_stack_push(&stack, joined);

			if (file_type_p(dir->d_type, args.file_type))
				printf("%s\n", joined);

			free(joined);
		}

		free(current);
		closedir(dirp);
	}

	return 0;
}
