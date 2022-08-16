#include "ft_cli.h"

int	main(int argc, char **argv)
{
	cli	data;

	if (argc != 2)
	{
		dprintf(2, "ft: invalid number of arguments\n");
		dprintf(2, "usage: ft <project-name>\n");
		return (1);
	}
	init_cli(&data, argv);
	validate_name(&data);
	write_in_files(&data);
	free_cli(&data);
	return (0);
}
