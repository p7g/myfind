#ifndef OPTIONS_H

#include <limits.h>
#include <sys/stat.h>

struct args {
	char *directory;
	int file_type_mask;
};

int parse_args(int argc, char *argv[], struct args *args);

#endif
