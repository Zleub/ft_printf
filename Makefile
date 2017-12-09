
SRC = ft_printf.c
OBJ = $(subst .c,.o,$(SRC))

NAME = libftprintf.a
CC ?= clang
CFLAGS ?= -Wall -Werror -Wextra

all: $(NAME) tests

$(NAME): $(OBJ)
	ar rc $(NAME) $^

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

tests:
	make -C tests

.PHONY: $(NAME) all re clean fclean tests
