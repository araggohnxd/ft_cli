#include "ft_cli.h"

void	init_cli(cli *data, char **argv)
{
	data->name = strdup(argv[1]);
	data->dir = NULL;
	data->include = NULL;
}

void	free_cli(cli *data)
{
	free(data->name);
	if (data->dir)
		free(data->dir);
	if (data->include)
		free(data->include);
}
