#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
	struct stat statbuf;

	if (parse_args(argc, argv, &args))
		usage();

	stack = dir_stack_new(args.directory);

	if (-1 == stat(args.directory, &statbuf)) {
		perror("stat");
		return 1;
	}

	if (file_type_p(mask_from_mode_t(statbuf.st_mode), args.file_type))
		printf("%s\n", args.directory);

	if (!S_ISDIR(statbuf.st_mode))
		return 0;

	while (stack) {
		dirp = opendir(stack->name);
		current = dir_stack_pop(&stack);

		if (dirp == NULL) {
			perror("opendir");
			continue;
		}

		while ((dir = readdir(dirp))) {
			joined = path_join(current, dir->d_name);

			if (exclude_p(dir->d_name))
				continue;

			if (dir->d_type == DT_DIR)
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
