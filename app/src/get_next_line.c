#include "ft_cli.h"
#define TRUE 1
#define BUFFER_SIZE	42
#define MAX_FD_VALUE 1024

static char	*extract_line(char *buffer, char *cache)
{
	size_t	i;
	char	*aux;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		++i;
	aux = substr(buffer, 0, (i + 1));
	if (buffer[i] && buffer[i + 1])
		strcpy(cache, &buffer[i + 1]);
	else
		bzero(cache, strlen(cache));
	free(buffer);
	return (aux);
}

static char	*read_line(int fd, char *buffer)
{
	int		read_ret;
	char	*aux;

	read_ret = TRUE;
	while (read_ret)
	{
		if (strchr(buffer, '\n'))
			break ;
		aux = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!aux)
			return (NULL);
		read_ret = read(fd, aux, BUFFER_SIZE);
		if (read_ret < 1)
		{
			free(aux);
			break ;
		}
		aux[read_ret] = '\0';
		buffer = join_free_null(&buffer, &aux);
	}
	if (!*buffer)
		memfree((void *)&buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	cache[BUFFER_SIZE + 1];
	char		*buffer;

	if (fd < 0 || fd >= MAX_FD_VALUE || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_line(fd, strdup(cache));
	return (extract_line(buffer, cache));
}
