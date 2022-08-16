#include "ft_cli.h"

static void	write_in_file(cli *data, char *file, char *text)
{
	char	*pathfile;
	int		fd;
	char	*mapi;

	pathfile = join(data->dir, file);
	mapi = NULL;
	fd = open(pathfile, O_WRONLY);
	if (!strcmp(text, DOT_H))
	{
		mapi = strmapi(data->name, &toupper);
		dprintf(fd, text, mapi, mapi, mapi);
		free(mapi);
	}
	else if (!strcmp(text, MAKEFILE))
		dprintf(fd, text, data->name, data->name);
	else
		dprintf(fd, text, data->name);
	close(fd);
	free(pathfile);
}

void	write_in_files(cli *data)
{
	char	*include = join("includes/", data->include);
	char	*file[5] = {"Makefile", "README.md", include, "src/main.c", ".gitignore"};
	char	*text[5] = {MAKEFILE, README, DOT_H, MAIN, GITIGNORE};
	int		i;

	i = 0;
	while (i < 5)
	{
		write_in_file(data, file[i], text[i]);
		i++;
	}
	free(include);
}
