#include "ft_cli.h"

static void	init_libft(cli *data)
{
	int		fd;
	char	*line;
	char	*homedir;
	char	*ft_dir;
	char	*libft_file;

	line = NULL;
	if ((homedir = getenv("HOME")) == NULL)
		homedir = getpwuid(getuid())->pw_dir;
	ft_dir = join(homedir, "/.config/ft");
	libft_file = join(ft_dir, "/libft");
	fd = open(libft_file, O_RDONLY);
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
		mkdir(ft_dir, 0755);
		create = open(libft_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(create, line, strlen(line));
		close(create);
		fd = open(libft_file, O_RDONLY);
	}
	data->libft_url = get_next_line(fd);
	data->libft_url[strlen(data->libft_url) - 1] = '\0';
	close(fd);
	free(line);
	free(ft_dir);
	free(libft_file);
}

void	init_cli(cli *data, char **argv)
{
	data->name = strdup(argv[1]);
	data->dir = NULL;
	data->include = NULL;
	data->libft_url = NULL;
	if (data->libft)
		init_libft(data);
}

void	free_cli(cli *data)
{
	free(data->name);
	if (data->dir)
		free(data->dir);
	if (data->include)
		free(data->include);
	if (data->libft_url)
		free(data->libft_url);
}
