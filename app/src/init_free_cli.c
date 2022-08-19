#include "ft_cli.h"

void	init_cli(cli *data)
{
	data->name = NULL;
	data->dir = NULL;
	data->include = NULL;
	data->homedir = NULL;
	data->libft_url = NULL;
	data->libft_file = NULL;
	data->ft_dir = NULL;
	data->help = 0;
	data->libft = 0;
	data->actions = 0;
}

void	free_cli(cli *data)
{
	memfree((void *)&data->name);
	memfree((void *)&data->dir);
	memfree((void *)&data->include);
	free_libft(data);
}
