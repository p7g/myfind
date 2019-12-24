#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "dir_stack.h"
#include "file_type.h"
#include "options.h"
#include "paths.h"

static void __attribute__((noreturn)) usage()
{
	fprintf(stderr, "USAGE:\n\tmyfind DIR [OPTS]\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dir;
	dir_stack *stack, *current;
	char *joined;
	struct args args;
	struct stat statbuf;

	stack = NULL;

	if (parse_args(argc, argv, &args))
		usage();

	if (-1 == stat(args.directory, &statbuf)) {
		perror("stat");
		return 1;
	}

	dir_stack_stat(&stack, args.directory, &statbuf);

	while (stack) {
		current = dir_stack_pop(&stack);

		if (file_type_p(current->file_type, args.file_type_mask))
			printf("%s\n", current->name);

		if (current->file_type & TYPE_DIR) {
			dirp = opendir(current->name);

			if (dirp == NULL) {
				perror("opendir");
				continue;
			}

			while ((dir = readdir(dirp))) {
				joined = path_join(current->name, dir->d_name);

				if (exclude_p(dir->d_name))
					continue;

				dir_stack_dirent(&stack, joined, dir);

				free(joined);
			}

			closedir(dirp);
		}

		dir_stack_free(current);
	}

	return 0;
}
