#include "ft_cli.h"

static void	make_actions(cli *data)
{
	chdir(data->name);
	if (access(".github/workflows/main.yaml", F_OK) == 0)
	{
		dprintf(2, "ft: actions: yaml file already exists\n");
		return;
	}
	system("git clone git@github.com:araggohnxd/vogsphere-github-actions.git");
	system("mkdir -p .github/workflows");
	system("mv vogsphere-github-actions/main.yaml .github/workflows");
	system("rm -rf vogsphere-github-actions");
	chdir("../");
}

static int	retry_libft(cli *data)
{
	int	c;

	if (access(data->libft_file, F_OK) == 0)
		unlink(data->libft_file);
	dprintf(2, BAD_LIB_URL);
	c = getchar();
	if (c == 'y' || c == 'Y' || c == '\n')
	{
		free_libft(data);
		init_libft(data);
	}
	else
		return (1);
	return (0);
}

static void	make_libft(cli *data)
{
	char	*aux;
	char	*full_command;
	int		sysret = 1;

	chdir(data->name);
	if (access("libft", F_OK) == 0)
	{
		dprintf(2, "ft: libft: library already exists\n");
		return;
	}
	while (sysret != 0)
	{
		aux = join("git clone ", data->libft_url);
		full_command = join(aux, " libft");
		sysret = WEXITSTATUS(system(full_command));
		free(aux);
		free(full_command);
		if (sysret != 0)
			if (retry_libft(data) != 0)
				return;
	}
	chdir("libft");
	system("rm -rf .git*");
	chdir("../");
}

static void	make_file(char *path, char *file)
{
	char	*pathname;

	pathname = join(path, file);
	creat(pathname, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	printf("Created file %s\n", pathname);
	free(pathname);
}

static int	make_dir(char *pathdir)
{
	DIR	*dir;

	dir = opendir(pathdir);
	if (dir)
	{
		dprintf(2, "ft: %s: directory already exists\n", pathdir);
		closedir(dir);
		return (1);
	}
	else
		mkdir(pathdir, 0755);
	return (0);
}

static void	make_include(cli *data)
{
	char	*pathinclude;

	data->include = join(data->name, ".h");
	pathinclude = join(data->dir, "includes/");
	make_file(pathinclude, data->include);
	free(pathinclude);
}

static void	make_main(cli *data)
{
	char	*pathmain;

	pathmain = join(data->dir, "sources/");
	make_file(pathmain, "main.c");
	free(pathmain);
}

static void	make_dir_structs(cli *data)
{
	char *dirs[2];

	dirs[0] = join(data->dir, "includes");
	dirs[1] = join(data->dir, "sources");
	for(int i = 0; i < 2; i++)
	{
		printf("Created dir %s\n", dirs[i]);
		make_dir(dirs[i]);
	}
	for(int i = 0; i < 2; i++)
		free(dirs[i]);
}

static void	make_structs(cli *data)
{
	make_file(data->dir, "Makefile");
	make_file(data->dir, "README.md");
	make_file(data->dir, ".gitignore");
	make_dir_structs(data);
	make_main(data);
	make_include(data);
}

static char	*make_path_dir(char *cwd, char *name)
{
	char	*new_dir;
	char	*temp;

	temp = join(cwd, "/");
	new_dir = join(temp, name);
	free(temp);
	temp = new_dir;
	new_dir = join(new_dir, "/");
	free(temp);
	return (new_dir);
}

void	building_project(cli *data)
{
	char	*cwd;

	printf("\nStarting to build %s\n", data->name);
	cwd = getcwd(NULL, 0);
	data->dir = make_path_dir(cwd, data->name);
	free(cwd);
	if (make_dir(data->name) != 0)
	{
		if (data->libft)
			make_libft(data);
		if (data->actions)
			make_actions(data);
		printf("Done building %s\n", data->name);
		free_cli(data);
		exit(0);
	}
	make_structs(data);
	if (data->libft)
		make_libft(data);
	if (data->actions)
		make_actions(data);
	printf("Done building %s\n", data->name);
}
