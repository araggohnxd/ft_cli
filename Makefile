NAME				:= ft

HEADER_PATH			:= ./app/include
HEADER_FILES		:= ft_cli.h

SOURCE_PATH			:= ./app/src
SOURCE_FILES		:= main.c
SOURCE_FILES 		+= init_free_cli.c
SOURCE_FILES 		+= init_free_libft.c
SOURCE_FILES		+= validate_name.c
SOURCE_FILES		+= building_project.c
SOURCE_FILES 		+= cli_utils.c
SOURCE_FILES 		+= get_next_line.c
SOURCE_FILES 		+= write_in_files.c
SOURCE_FILES 		+= parsing.c
SOURCE_FILES 		+= help.c
SOURCE_FILES 		+= error.c

OBJECT_PATH			:= ./app/obj
OBJECT_FILES		:= $(SOURCE_FILES:%.c=$(OBJECT_PATH)/%.o)

LOCAL_INSTALL		:= /usr/local/bin
LOCAL_MAN			:= /usr/share/man/man1/ft.1
MAN_FILE			:= ./assets/ft_man

CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra -g3
IFLAGS				:= -I ./app/include
LDFLAGS				:= -lreadline
REMOVE				:= rm -rf

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

all:				$(NAME)

$(NAME):			$(OBJECT_FILES)
					$(CC) $(CFLAGS) -o $@ $(OBJECT_FILES) $(LDFLAGS)

$(OBJECT_PATH)/%.o:	%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJECT_PATH):
					mkdir -p $@

clean:
					$(REMOVE) $(OBJECT_PATH)

fclean:				clean
					$(REMOVE) $(NAME)

install:			$(NAME)
					cp $(NAME) $(LOCAL_INSTALL)
					cp $(MAN_FILE) $(LOCAL_MAN)
					gzip $(LOCAL_MAN)

re:					fclean all

.PHONY:				all clean fclean re install
