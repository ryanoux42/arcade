/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef SDL2_HPP_

  #define SDL2_HPP_
  #include "../../IDisplayModule.hpp"

  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
  #include <iostream>

class SDL2 : public Arc::IDisplayModule {
  protected:
    std::string name;
    SDL_Window* window;
    SDL_Surface *screenSurface;
    std::vector<SDL_Texture*> textures;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Rect rect;
    SDL_Rect Message_rect;
    TTF_Font *Sans;
  public:
    SDL2(const std::string &name);
    ~SDL2() = default;
    void init(Arc::InfoGame info);
    void display(Arc::InfoGame line);
    Arc::Keys getKeyPress();
    void stop();
    void print_map(Arc::InfoGame info);
    int print_game(Arc::InfoGame info, int i, int j);
    void print_score(Arc::InfoGame info);
    void print_menu(Arc::InfoGame info, int i);
    const std :: string &getName() const;
};

#endif
