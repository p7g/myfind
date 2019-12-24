#ifndef FILE_TYPE_H

#include <sys/stat.h>

#define TYPE_FILE (1 << 0)
#define TYPE_DIR  (1 << 1)
#define TYPE_LINK (1 << 2)

int file_type_p(int type, int mask);
int mask_from_mode_t(mode_t mode);
int mask_from_d_type(int d_type);

#endif
