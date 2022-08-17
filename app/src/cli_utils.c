#include "ft_cli.h"

char	*join(char *s1, char *s2)
{
	char	*join;

	join = malloc(strlen(s1) + strlen(s2) + 1);
	if (join)
	{
		strcpy(join, s1);
		strcat(join, s2);
	}
	return (join);
}

char	*strmapi(char const *s, int (*f)(int))
{
	unsigned int	i;
	char			*s_cpy;

	if (!s)
		return (NULL);
	i = 0;
	s_cpy = strdup(s);
	if (!s_cpy)
		return (NULL);
	while (s_cpy[i])
	{
		s_cpy[i] = (*f)(s_cpy[i]);
		i++;
	}
	return (s_cpy);
}

void	memfree(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*join_free_null(char **s1, char **s2)
{
	char	*str;

	str = join(*s1, *s2);
	memfree((void *)s1);
	memfree((void *)s2);
	return (str);
}

char	*substr(char const *s, size_t start, size_t len)
{
	size_t	s_len;
	size_t	malloc_size;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start < s_len)
		malloc_size = s_len - start;
	if (start >= s_len)
		malloc_size = 0;
	if (malloc_size > len)
		malloc_size = len;
	substr = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if (!substr)
		return (NULL);
	if (malloc_size == 0)
	{
		substr[0] = '\0';
		return (substr);
	}
	strcpy(substr, (s + start));
	return (substr);
}
