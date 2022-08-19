#include "ft_cli.h"

void	exit_error_msg(cli *data, char *str, char *msg)
{
	dprintf(2, "ft: %s: '%s'\n", str, msg);
	dprintf(2, "try 'ft --help' for more information\n");
	free_cli(data);
	exit(1);
}
