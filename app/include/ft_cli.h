#ifndef FT_CLI
# define FT_CLI

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HELP_MSG "\
USAGE\n\
	ft [project-name] [OPTIONS]..\n\
\n\
OPTIONS\n\
	-h, --help	display this help message\n\
	-l, --libft	clone your libft into the new project directory\n\
	-a, --actions	clone a GitHub Actions workflow for Vogsphere pushing\n\
\n\
"

# define NO_CONFIG_FILE "\
\nA config file for your default libft repository wasn't found.\n\
Enter a URL to set it as default:\n\
"

# define BAD_LIB_URL "\
\nThe URL you provided is not valid.\n\
Want to try again? (y/n): \
"

# define MAKEFILE_LIB "\
NAME				:= %s\n\
\n\
HEADER_PATH			:= ./includes\n\
HEADER_FILES		:= %s.h\n\
\n\
LIBFT_PATH			:= ./libft\n\
LIBFT				:= $(LIBFT_PATH)/libft.a\n\
\n\
SOURCE_PATH			:= ./sources\n\
SOURCE_FILES		:= main.c\n\
\n\
OBJECT_PATH			:= ./objects\n\
OBJECT_FILES		:= $(SOURCE_FILES:%%.c=$(OBJECT_PATH)/%%.o)\n\
\n\
CC					:= cc\n\
CFLAGS				:= -Wall -Wextra -Werror\n\
IFLAGS				:= -I $(HEADER_PATH)\n\
LDFLAGS				:= -L $(LIBFT_PATH) -lft\n\
REMOVE				:= rm -rf\n\
\n\
ifdef C_DEBUG\n\
	CFLAGS += -g3\n\
endif\n\
\n\
vpath				%%.c $(SOURCE_PATH)\n\
vpath				%%.h $(HEADER_PATH)\n\
\n\
all:				$(NAME)\n\
\n\
$(NAME):			$(OBJECT_FILES) $(LIBFT) \n\
					$(CC) $(CFLAGS) -o $@ $(OBJECT_FILES) $(LDFLAGS)\n\
\n\
$(OBJECT_PATH)/%%.o:	%%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)\n\
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@\n\
\n\
$(OBJECT_PATH):\n\
					mkdir -p $@\n\
$(LIBFT):\n\
					$(MAKE) -C $(LIBFT_PATH)\n\
\n\
clean:\n\
					$(REMOVE) $(OBJECT_PATH)\n\
					$(MAKE) -C $(LIBFT_PATH) clean\n\
\n\
fclean:				clean\n\
					$(REMOVE) $(NAME)\n\
					$(MAKE) -C $(LIBFT_PATH) fclean\n\
\n\
re:					fclean all\n\
\n\
.PHONY:				all clean fclean re\n\
"

# define MAKEFILE_NOLIB "\
NAME				:= %s\n\
\n\
HEADER_PATH			:= ./includes\n\
HEADER_FILES		:= %s.h\n\
\n\
SOURCE_PATH			:= ./sources\n\
SOURCE_FILES		:= main.c\n\
\n\
OBJECT_PATH			:= ./objects\n\
OBJECT_FILES		:= $(SOURCE_FILES:%%.c=$(OBJECT_PATH)/%%.o)\n\
\n\
CC					:= cc\n\
CFLAGS				:= -Wall -Wextra -Werror\n\
IFLAGS				:= -I $(HEADER_PATH)\n\
REMOVE				:= rm -rf\n\
\n\
ifdef C_DEBUG\n\
	CFLAGS += -g3\n\
endif\n\
\n\
vpath				%%.c $(SOURCE_PATH)\n\
vpath				%%.h $(HEADER_PATH)\n\
\n\
all:				$(NAME)\n\
\n\
$(NAME):			$(OBJECT_FILES)\n\
					$(CC) $(CFLAGS) -o $@ $(OBJECT_FILES)\n\
\n\
$(OBJECT_PATH)/%%.o:	%%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)\n\
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@\n\
\n\
$(OBJECT_PATH):\n\
					mkdir -p $@\n\
\n\
clean:\n\
					$(REMOVE) $(OBJECT_PATH)\n\
\n\
fclean:				clean\n\
					$(REMOVE) $(NAME)\n\
\n\
re:					fclean all\n\
\n\
.PHONY:				all clean fclean re\n\
"

# define GITIGNORE "\
# Prerequisites\n\
*.d\n\
\n\
# Object files\n\
*.o\n\
*.ko\n\
*.obj\n\
*.elf\n\
\n\
# Linker output\n\
*.ilk\n\
*.map\n\
*.exp\n\
\n\
# Precompiled Headers\n\
*.gch\n\
*.pch\n\
\n\
# Libraries\n\
*.lib\n\
*.a\n\
*.la\n\
*.lo\n\
\n\
# Shared objects (inc. Windows DLLs)\n\
*.dll\n\
*.so\n\
*.so.*\n\
*.dylib\n\
\n\
# Executables\n\
*.exe\n\
*.out\n\
*.app\n\
*.i*86\n\
*.x86_64\n\
*.hex\n\
\n\
# Debug files\n\
*.dSYM/\n\
*.su\n\
*.idb\n\
*.pdb\n\
\n\
# Kernel Module Compile Results\n\
*.mod*\n\
*.cmd\n\
.tmp_versions/\n\
modules.order\n\
Module.symvers\n\
Mkfile.old\n\
dkms.conf\n\
\n\
# Custom files\n\
%s\n\
.normignore\n\
\n\
# Custom directories\n\
.vscode/\n\
"

# define README "# %s\n"

# define DOT_H "\
#ifndef %s_H\n\
# define %s_H\n\
\n\
#endif /* %s_H */\n\
"

# define MAIN "\
#include \"%s.h\"\n\
\n\
int	main(void)\n\
{\n\
\treturn (0);\n\
}\n\
"

typedef struct s_cli
{
	char	*name;
	char	*dir;
	char	*include;
	char	*libft_url;
	char	*homedir;
	char	*ft_dir;
	char	*libft_file;
	int		libft;
	int		actions;
	int		help;
}	cli;

void	parse_arguments(cli *data, char **argv);
void	init_cli(cli *data);
void	init_libft(cli *data);
void	free_cli(cli *data);
void	free_libft(cli *data);
void	validate_name(cli *data);
void	building_project(cli *data);
void	write_in_files(cli *data);
void	display_help(void);
void	exit_error_msg(cli *data, char *str, char *msg);

// Utils
void	memfree(void **ptr);
char	*join(char *s1, char *s2);
char	*join_free_null(char **s1, char **s2);
char	*strmapi(char const *s, int (*f)(int));
char	*get_next_line(int fd);
char	*substr(char const *s, size_t start, size_t len);

#endif /* FT_CLI */
