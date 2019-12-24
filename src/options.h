#ifndef OPTIONS_H

#include <limits.h>
#include <sys/stat.h>

struct args {
	int file_type_mask;
	char *directory;
};

int parse_args(int argc, char *argv[], struct args *args);

#endif
