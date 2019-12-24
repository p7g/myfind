#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# define PATH_SEP '\\'
#else
# define PATH_SEP '/'
#endif

struct dir_stack {
	char *name;
	struct dir_stack *next;
};

static struct dir_stack *dir_stack_new(const char *name)
{
	static char path_buf[PATH_MAX];
	struct dir_stack *new;
	size_t len;

	realpath(name, path_buf);
	len = strlen(path_buf);

	new = malloc(sizeof(struct dir_stack));
	new->name = malloc(len + 1);
	strncpy(new->name, path_buf, len);
	new->name[len] = '\0';
	new->next = NULL;

	return new;
}

static void dir_stack_free(struct dir_stack *stack)
{
	free(stack->name);
	free(stack);
}

static int exclude_p(const char *name)
{
	if (strlen(name) > 2 || *name != '.')
		return 0;
	if (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))
		return 1;
	return 0;
}

static char *path_join(const char *a, const char *b)
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

int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dir;
	struct dir_stack *stack, *current, *tmp;
	char *joined;

	if (argc < 2) {
		printf("USAGE:\n\tmyfind DIR [OPTS]\n");
		exit(1);
	}

	stack = dir_stack_new(argv[1]);

	while (stack) {
		dirp = opendir(stack->name);

		current = stack;
		stack = stack->next;

		if (dirp == NULL) {
			perror("opendir");
			continue;
		}

		while ((dir = readdir(dirp))) {
			joined = path_join(current->name, dir->d_name);

			if (dir->d_type == DT_DIR) {
				if (exclude_p(dir->d_name))
					continue;
				tmp = stack;
				stack = dir_stack_new(joined);
				stack->next = tmp;
			} else {
				printf("%s\n", joined);
			}

			free(joined);
		}

		dir_stack_free(current);
		closedir(dirp);
	}

	return 0;
}
