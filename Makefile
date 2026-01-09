CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D BUFFER_SIZE=5
NAME = gnl

all: $(NAME)

$(NAME): get_next_line.c get_next_line_utils.c
	$(CC) $(CFLAGS) get_next_line.c get_next_line_utils.c -o $(NAME)

test: clean $(NAME)
	./$(NAME) < text.txt

test2: clean $(NAME)
	./$(NAME) < text2.txt

clean:
	rm -rf *.o ./a.out

fclean: clean
	rm -rf ./$(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full ./$(NAME)