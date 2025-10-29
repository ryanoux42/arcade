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
	make -C Ncurses
	make -C SDL2
	make -C SFML

clean :
	rm -f $(OBJ)
	make clean -C Ncurses
	make clean -C SDL2
	make clean -C SFML

fclean : clean
	rm -f $(NAME)
	make fclean -C Ncurses
	make fclean -C SDL2
	make fclean -C SFML

re : fclean all

tests_run:
	$(CC) $(OBJ) $(TSRC) --coverage -lcriterion -I ./includes/ -o unit_tests

coverage:
	gcovr --exclude tests/

.PHONY: re clean fclean all tests_run coverage
