#ifndef PATHS_H

#ifdef _WIN32
# define PATH_SEP '\\'
#else
# define PATH_SEP '/'
#endif

int exclude_p(const char *name);
char *path_join(const char *a, const char *b);

#endif
