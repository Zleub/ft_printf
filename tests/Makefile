SRC = $(shell find . -name "*.c")
OBJ = $(subst .c,.o,$(SRC))

CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L.. -lftprintf

TESTS = "Hello World !\n"

all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(patsubst %.c,%,$<) $<

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY: $(NAME) all re clean fclean
