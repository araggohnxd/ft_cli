#include "ft_cli.h"

int	check_libft(cli *data, char **argv)
{
	if (strcmp(argv[2], "--libft") != 0)
	{
		dprintf(2, "ft: %s: invalid option", argv[2]);
		return (1);
	}
	data->libft = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	cli	data;

	if (argc < 2 || argc > 3)
	{
		dprintf(2, "ft: invalid amount of arguments\n");
		dprintf(2, "usage: ft <project-name> [--libft]\n");
		return (1);
	}
	if (argc == 3 && check_libft(&data, argv))
		return (1);
	init_cli(&data, argv);
	validate_name(&data);
	write_in_files(&data);
	free_cli(&data);
	return (0);
}
