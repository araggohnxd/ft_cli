#include "ft_cli.h"

int	main(int argc, char **argv)
{
	cli	data;

	if (argc == 1)
	{
		dprintf(2, "usage: ft [PROJECT-NAME] [OPTIONS]...\n");
		dprintf(2, "try 'ft --help' for more information\n");
		return (1);
	}
	init_cli(&data);
	parse_arguments(&data, argv);
	validate_name(&data);
	write_in_files(&data);
	free_cli(&data);
	return (0);
}
