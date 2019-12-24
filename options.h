#ifndef OPTIONS_H

#include <limits.h>
#include <sys/stat.h>

#define TYPE_FILE (1 << 0)
#define TYPE_DIR  (1 << 1)
#define TYPE_LINK (1 << 2)

struct args {
	int file_type;
	char *directory;
};

int parse_args(int argc, char *argv[], struct args *args);
int file_type_p(int type, int mask);
int mask_from_mode_t(mode_t mode);

#endif
