NAME	= pipex
HEADER	= pipex.h libft.h
SRC	= pipex.c init.c helper.c path.c free.c error.c error_2.c pipping.c
LIBFT	= libft/libft.a
CC	= cc
FLAGS	= -Werror -Wextra -Wall -g
vpath libft.h libft

all: $(NAME)

$(NAME): $(HEADER) $(SRC) $(SRC:.c=.o) ${LIBFT}
	$(CC) $(FLAGS) $(SRC:.c=.o) -L./libft -lft -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) -c $(FLAG) $< -o $@

clean:
	rm -rf *.o
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
