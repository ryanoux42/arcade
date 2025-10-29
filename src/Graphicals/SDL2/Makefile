##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## task01
##

SRC = SDL2.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_sdl2.so

SDL2 = -lSDL2 -lSDL2_ttf -lSDL2_image

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o SDL2.o -c -fPIC SDL2.cpp $(SDL2)
	g++ -shared -o $(NAME) $(OBJ) $(SDL2)
	cp $(NAME) ../../../lib/$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re: fclean all