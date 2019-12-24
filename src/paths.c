#include <stdlib.h>
#include <string.h>

#include "paths.h"

int exclude_p(const char *name)
{
	if (strlen(name) > 2 || *name != '.')
		return 0;
	if (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))
		return 1;
	return 0;
}

char *path_join(const char *a, const char *b)
{
	char *result;
	size_t len_a, len_b;

	len_a = strlen(a);
	len_b = strlen(b);
	result = malloc(len_a + len_b + 2); /* path sep + null byte */
	strncpy(result, a, len_a);
	result[len_a] = PATH_SEP;
	strncpy(result + len_a + 1, b, len_b);
	result[len_a + len_b + 1] = '\0';

	return result;
}
