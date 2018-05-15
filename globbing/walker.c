/*
 * file: walker.c
 * author: iomonad
 */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char*
base(char *path)
{
	char		*start;

	if (strcmp(path, "/") == 0)
		return (path);
	start = strchr(path, '\0');
	while (start > path && *(start - 1) != '/')
		start--;
	return (start);
}

/*
 * Find correct shit by reading
 * your fckng pattern
 */
void
find_single_pattern(const char *path,
					char **patterns,
					char **results)
{
	DIR* dir = NULL;
	struct dirent *entry = NULL;
	size_t i, j = 0, k = 0;

	if ((dir = opendir(path)) != NULL)
	{
		while (i = 0, (entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") == 0
				|| strcmp(entry->d_name, "..") == 0)
				continue;
			while (patterns[i] != NULL)
			{
				/*
				 * Match patterns
				 */
				if (strstr(entry->d_name, base(patterns[i])) == NULL)
				{
					k = 1 ;
					break ;
				}
				i++;
			}
			if (!(k ^= 1))
				continue ;
			results[j] = strdup(entry->d_name);
			j++;
		}
		closedir(dir);
	}
}

/*
 * Apply unique inclusive pattern
 * for all folder accurences;
 * TODO: support absolute paths
 */
void
full_inclusive_pattern(const char *path,
					   char **results,
					   size_t i)
{
	DIR* dir = NULL;
	struct dirent *entry = NULL;

	if ((dir = opendir(path)) != NULL)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") == 0
				|| strcmp(entry->d_name, "..") == 0)
				continue;
			results[i] = strdup(entry->d_name);
			i++;
		}
		closedir(dir);
	}
}