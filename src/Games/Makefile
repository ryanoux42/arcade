##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## root
##

SRC	        =

OBJ	        =	$(SRC:.cpp=.o)

NAME	    =	name

all : $(NAME)

$(NAME) :	$(OBJ)
	make -C Snake
	make -C Nibbler
	make -C Pac-Man

clean :
	rm -f $(OBJ)
	make clean -C Snake
	make clean -C Nibbler
	make clean -C Pac-Man

fclean : clean
	rm -f $(NAME)
	make fclean -C Snake
	make fclean -C Nibbler
	make fclean -C Pac-Man

re : fclean all

tests_run:
	$(CC) $(OBJ) $(TSRC) --coverage -lcriterion -I ./includes/ -o unit_tests

coverage:
	gcovr --exclude tests/

.PHONY: re clean fclean all tests_run coverage
