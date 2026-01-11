CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D BUFFER_SIZE=6
NAME = gnl

all: $(NAME)

$(NAME): main.c get_next_line.c get_next_line_utils.c
	$(CC) $(CFLAGS) main.c get_next_line.c get_next_line_utils.c -o $(NAME)

test: clean $(NAME)
	@echo "===== TEST 1 ====="
	./$(NAME) < test1.txt
	@echo
	@echo "===== TEST 2 ====="
	./$(NAME) < test2.txt
	@echo
	@echo "===== TEST 3 ====="
	./$(NAME) < test3.txt
	@echo
	@echo "===== TEST 4 ====="
	./$(NAME) < test4.txt


clean:
	rm -rf *.o ./a.out

fclean: clean
	rm -rf ./$(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full ./$(NAME) < test3.txt