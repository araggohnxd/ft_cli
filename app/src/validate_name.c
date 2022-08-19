#include "ft_cli.h"

void	validate_name(cli *data)
{
	if (isalnum(data->name[0]))
		building_project(data);
	else
		exit_error_msg(data, "not a valid name", data->name);
}
