##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## SFML
##

SRC = SFML.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_sfml.so

CSFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o SFML.o -c -fPIC SFML.cpp $(CSFML_FLAGS)
	g++ -shared -o $(NAME) $(OBJ) $(CSFML_FLAGS)
	cp $(NAME) ../../../lib/$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re: fclean all