#include "ft_cli.h"

void	validate_name(cli *data)
{
	if (isalnum(data->name[0]))
		building_project(data);
	else
		dprintf(2, "ft: %s: not a valid name\n", data->name);
}
