#include "ft_cli.h"

void	exit_error_msg(cli *data, char *str, char *msg)
{
	free_cli(data);
	dprintf(2, "ft: %s: %s\n", str, msg);
	exit(1);
}

void	display_help(void)
{
	printf(HELP_MSG);
	exit(0);
}

void	parse_arguments(cli *data, char **argv)
{
	for (size_t index = 1; argv[index]; index++)
	{
		if (argv[index][0] != '-' && !data->name)
			data->name = strdup(argv[index]);
		else if (argv[index][0] != '-' && data->name)
			exit_error_msg(data, argv[index], "invalid option");
		else if (argv[index][0] == '-' && (strcmp(argv[index], "--help") == 0 || strcmp(argv[index], "-h") == 0))
			data->help = 1;
		else if (argv[index][0] == '-' && (strcmp(argv[index], "--libft") == 0 || strcmp(argv[index], "-l") == 0))
			data->libft = 1;
		else if (argv[index][0] == '-' && (strcmp(argv[index], "--actions") == 0 || strcmp(argv[index], "-a") == 0))
			data->actions = 1;
		else if (argv[index][0] == '-' && (strcmp(argv[index], "-la") == 0 || strcmp(argv[index], "-al") == 0))
		{
			data->libft = 1;
			data->actions = 1;
		}
		else
			exit_error_msg(data, argv[index], "invalid option");
	}
	if (!data->name)
		exit_error_msg(data, "missing argument", "project name");
	if (data->help)
		display_help();
	if (data->libft)
		init_libft(data);
}

int	main(int argc, char **argv)
{
	cli	data;

	if (argc == 1)
		display_help();
	init_cli(&data);
	parse_arguments(&data, argv);
	validate_name(&data);
	write_in_files(&data);
	free_cli(&data);
	return (0);
}
