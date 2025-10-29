/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/

#include "SDL2.hpp"

SDL2::SDL2(const std::string &name) : name(name), window(NULL), screenSurface(),
    renderer(), event(), rect(), Message_rect(), Sans()
{
}

const std::string &SDL2::getName() const
{
    return name;
}

void SDL2::init(Arc::InfoGame info)
{
    int k = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0
        || IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    else {
        TTF_Init();
        if (window)
            SDL_SetWindowSize(window, info.window_size.first, info.window_size.second);
        else {
            window = SDL_CreateWindow("SDL Window", 0, 0,
            info.window_size.first, info.window_size.second, SDL_WINDOW_SHOWN);
            if (window == nullptr) {
                std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return;
            }
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return;
            }
        }
        textures.clear();
        for (k; k < info.assets_dico.size(); k++) {
            screenSurface = IMG_Load(info.assets_dico[k].image_path.c_str());
            if (screenSurface != NULL) {
                textures.push_back(SDL_CreateTextureFromSurface(renderer, screenSurface));
            } else {
                textures.push_back(nullptr);
            }
            SDL_FreeSurface(screenSurface);
        }
        Sans = TTF_OpenFont(info.font.c_str(), 27);
        if (!Sans)
            Sans = TTF_OpenFont("./src/Ressources/Roblox.ttf", 27);
        rect.x = 0;
        rect.y = 0;
        rect.w = 30;
        rect.h = 30;
        Message_rect.x = 0;
        Message_rect.y = 0;
        Message_rect.w = 30;
        Message_rect.h = 30;
    }
}

int SDL2::print_game(Arc::InfoGame info, int i, int j)
{
    for (int k = 0; k < info.assets_dico.size(); k++) {
        if (info.assets_dico[k].c == info.map.val[i][j]) {
            if (textures[k] != nullptr) {
                SDL_RenderCopy(renderer, textures[k], nullptr, &rect);
            } else {
                SDL_SetRenderDrawColor(renderer, info.assets_dico[k].rgb.first,
                info.assets_dico[k].rgb.second.first,
                info.assets_dico[k].rgb.second.second, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            rect.x += info.assets_dico[k].image_size.first;
            return 1;
        }
    }
    return 0;
}

void SDL2::print_menu(Arc::InfoGame info, int i)
{
    screenSurface = TTF_RenderText_Solid(Sans,
    info.map.val[i].c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, screenSurface);
    SDL_QueryTexture(texture, nullptr, nullptr, &Message_rect.w, &Message_rect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &Message_rect);
    SDL_FreeSurface(screenSurface);
    SDL_DestroyTexture(texture);
    Message_rect.y += 30;
}

void SDL2::print_map(Arc::InfoGame info)
{
    for (int i = 0; i < info.map.val.size(); i++) {
        for (int j = 0; j < info.map.val[i].size(); j++) {
            if (!print_game(info, i, j)) {
                print_menu(info, i);
                break;
            }
        }
        rect.y += info.assets_dico[0].image_size.second;
        rect.x = info.map.pos.first;

    }
    rect.y = info.map.pos.second;
    Message_rect.y = 0;
}

void SDL2::print_score(Arc::InfoGame info)
{
    int dico_size = info.assets_dico.size();
    Message_rect.y = info.score.pos.second * 30;
    Message_rect.x = info.score.pos.first * 30;
    screenSurface = TTF_RenderText_Solid(Sans,
    ("Score: " + std::to_string(info.score.val)).c_str() , {255, 255, 255});
    textures[dico_size] = SDL_CreateTextureFromSurface(renderer, screenSurface);
    SDL_QueryTexture(textures[dico_size],
    nullptr, nullptr, &Message_rect.w, &Message_rect.h);
    SDL_RenderCopy(renderer, textures[dico_size], nullptr, &Message_rect);
    Message_rect.y = info.highest_score.pos.second * 30;
    Message_rect.x = info.highest_score.pos.first * 30;
    screenSurface = TTF_RenderText_Solid(Sans,
    ("Highest score: " + std::to_string(info.highest_score.val)).c_str() , {255, 255, 255});
    textures[dico_size] = SDL_CreateTextureFromSurface(renderer, screenSurface);
    SDL_QueryTexture(textures[dico_size],
    nullptr, nullptr, &Message_rect.w, &Message_rect.h);
    SDL_RenderCopy(renderer, textures[dico_size], nullptr, &Message_rect);
    Message_rect.y = info.timer.pos.second * 30;
    Message_rect.x = info.timer.pos.first * 30;
    screenSurface = TTF_RenderText_Solid(Sans, ("Timer: " + std::to_string(info.timer.val)).c_str() , {255, 255, 255});
    textures[dico_size] = SDL_CreateTextureFromSurface(renderer, screenSurface);
    SDL_QueryTexture(textures[dico_size], nullptr, nullptr, &Message_rect.w, &Message_rect.h);
    SDL_RenderCopy(renderer, textures[dico_size], nullptr, &Message_rect);
    SDL_FreeSurface(screenSurface);
    SDL_DestroyTexture(textures[dico_size]);
    Message_rect.y = 0;
    Message_rect.x = 0;
}

void SDL2::display(Arc::InfoGame info)
{
    rect.x = info.map.pos.first;
    rect.y = info.map.pos.second;
    rect.w = info.assets_dico[0].image_size.first;
    rect.h = info.assets_dico[0].image_size.second;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    print_map(info);
    print_score(info);
    SDL_RenderPresent(renderer);
}

Arc::Keys SDL2::getKeyPress()
{
    unsigned int c = 0;

    if (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return Arc::Keys::ESC;
        } else if (event.type == SDL_KEYDOWN) {
            c = event.key.keysym.sym;
        }
    }
    if (c >= 'a' && c <= 'z') {
        return static_cast<Arc::Keys>(c - 96);
    }
    switch (c) {
        case 27: return Arc::Keys::ESC;
        case SDLK_UP: return Arc::Keys::UP;
        case SDLK_RIGHT: return Arc::Keys::RIGHT;
        case SDLK_DOWN: return Arc::Keys::DOWN;
        case SDLK_LEFT: return Arc::Keys::LEFT;
        case SDLK_RETURN: return Arc::Keys::ENTER;
    }
    return Arc::Keys::NONE;
}

void SDL2::stop()
{
    TTF_CloseFont(Sans);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

extern "C" Arc::IDisplayModule *createGraph()
{
    return new SDL2("SDL2");
}
