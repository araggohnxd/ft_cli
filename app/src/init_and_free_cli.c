#include "ft_cli.h"

void	init_libft(cli *data)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((data->homedir = getenv("HOME")) == NULL)
		data->homedir = getpwuid(getuid())->pw_dir;
	data->ft_dir = join(data->homedir, "/.config/ft");
	data->libft_file = join(data->ft_dir, "/libft");
	fd = open(data->libft_file, O_RDONLY);
	if (fd == -1)
	{
		int	create;

		printf(NO_CONFIG_FILE);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				continue;
			else if (*line == '\0' || *line == '\n')
				free(line);
			else
				break ;
		}
		mkdir(data->ft_dir, 0755);
		create = open(data->libft_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(create, line, strlen(line));
		close(create);
		fd = open(data->libft_file, O_RDONLY);
	}
	data->libft_url = get_next_line(fd);
	data->libft_url[strlen(data->libft_url) - 1] = '\0';
	close(fd);
	free(line);
	printf("\n");
}

void	init_cli(cli *data)
{
	data->name = NULL;
	data->dir = NULL;
	data->include = NULL;
	data->homedir = NULL;
	data->libft_url = NULL;
	data->libft_file = NULL;
	data->ft_dir = NULL;
	data->libft = 0;
	data->actions = 0;
}

void	free_libft(cli *data)
{
	memfree((void *)&data->libft_url);
	memfree((void *)&data->ft_dir);
	memfree((void *)&data->libft_file);
}

void	free_cli(cli *data)
{
	memfree((void *)&data->name);
	memfree((void *)&data->dir);
	memfree((void *)&data->include);
	free_libft(data);
}
