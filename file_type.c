#include <dirent.h>
#include <sys/stat.h>

#include "file_type.h"

int file_type_p(int type, int mask)
{
	/* If no options are specified, do no filtering */
	if (!mask)
		return 1;

	return mask & type;
}

int mask_from_mode_t(mode_t mode)
{
	switch (mode & S_IFMT) {
		case S_IFDIR:
			return TYPE_DIR;
		case S_IFREG:
			return TYPE_FILE;
		case S_IFLNK:
			return TYPE_LINK;
	}

	return 0;
}

int mask_from_d_type(int d_type)
{
	switch (d_type) {
		case DT_LNK:
			return TYPE_LINK;
		case DT_REG:
			return TYPE_FILE;
		case DT_DIR:
			return TYPE_DIR;
	}

	return 0;
}
