#include "ft_cli.h"

static void	handle_double_dash(cli *data, char *str)
{
	if (strcmp(str, "help") == 0)
		data->help = 1;
	else if (strcmp(str, "libft") == 0)
		data->libft = 1;
	else if (strcmp(str, "actions") == 0)
		data->actions = 1;
	else
		exit_error_msg(data, "invalid option", str);
}

static void	handle_single_dash(cli *data, char *str)
{
	while (*str)
	{
		if (*str == 'h')
			data->help = 1;
		else if (*str == 'l')
			data->libft = 1;
		else if (*str == 'a')
			data->actions = 1;
		else
		{
			char	tmp[2] = "";

			tmp[0] = *str;
			exit_error_msg(data, "invalid option", tmp);
		}
		++str;
	}
}

void	parse_arguments(cli *data, char **argv)
{
	char	*current;
	size_t	index;

	for (index = 1; argv[index]; index++)
	{
		current = argv[index];
		if (current[0] != '-' && !data->name)
			data->name = strdup(current);
		else if (current[0] != '-' && data->name)
			exit_error_msg(data, "invalid argument", current);
		else if (current[0] == '-')
		{
			++current;
			if (current[0] == '-')
			{
				++current;
				handle_double_dash(data, current);
			}
			else
				handle_single_dash(data, current);
		}
	}
	if (data->help)
		display_help();
	if (!data->name)
		exit_error_msg(data, "missing argument", "project name");
	if (data->libft)
		init_libft(data);
}
