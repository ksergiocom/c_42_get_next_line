CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D BUFFER_SIZE=5
NAME = gnl

all: $(NAME)

$(NAME): get_next_line.c get_next_line_utils.c
	$(CC) $(CFLAGS) get_next_line.c get_next_line_utils.c -o $(NAME)

test1: clean $(NAME)
	./$(NAME) < test1.txt

test2: clean $(NAME)
	./$(NAME) < test2.txt

test3: clean $(NAME)
	./$(NAME) < test3.txt

test4: clean $(NAME)
	./$(NAME) < test4.txt

clean:
	rm -rf *.o ./a.out

fclean: clean
	rm -rf ./$(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full ./$(NAME)