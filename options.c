#include <getopt.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "options.h"

static int parse_types(const char *types, struct args *args)
{
	size_t len, i, mask;

	len = strlen(types);
	mask = 0;

	for (i = 0; i < len; i += 1) {
		switch (types[i]) {
			case 'f':
				mask |= TYPE_FILE;
				break;
			case 'l':
				mask |= TYPE_LINK;
				break;
			case 'd':
				mask |= TYPE_DIR;
				break;
			default:
				return -1;
		}
	}

	args->file_type = mask;

	return 0;
}

int file_type_p(int type, int mask)
{
	/* If no options are specified, do no filtering */
	if (!mask)
		return 1;

	return mask & type;
}

int parse_args(int argc, char *argv[], struct args *args)
{
	char opt;

	args->file_type = 0;
	args->directory = NULL;

	while ((opt = getopt(argc, argv, "t:")) != -1) {
		switch (opt) {
			case 't':
				if (parse_types(optarg, args)) {
					fprintf(stderr, "Invalid value for option -t\n");
					return -1;
				}
				break;
			default:
				fprintf(stderr, "Unknown option -%c\n", opt);
				return -1;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "Expected directory");
		return -1;
	}

	args->directory = argv[optind];

	return 0;
}
