CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = gnl

$(NAME): get_next_line.c get_next_line_utils.c
	$(CC) $(CFLAGS) get_next_line.c get_next_line_utils.c -o $(NAME)

test: clean $(NAME)
	./$(NAME) < text.txt

test2: clean $(NAME)
	./$(NAME) < text2.txt

clean:
	rm -rf *.o ./a.out ./$(NAME)