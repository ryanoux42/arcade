/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#ifndef SFML_HPP_

  #define SFML_HPP_
  #include "../../IDisplayModule.hpp"

  #include "SFML/Graphics.hpp"
  #include "SFML/Window.hpp"
  #include "SFML/System.hpp"
  #include "SFML/Audio.hpp"
  #include "SFML/Network.hpp"

  #include <iostream>

class SFML: public Arc::IDisplayModule {
  protected:
    std::string name;
    sf::RenderWindow window;
    std::vector<sf::Texture> textures;
    sf::Font font;
    std::vector<sf::Text> texts;
    sf::Event event;
    sf::RectangleShape rect;
    sf::RectangleShape message_rect;
    sf::Vector2f map_pos;
    sf::Vector2f tile_pos;
  public:
    SFML(const std::string &name);
    ~SFML() = default;
    void init(Arc::InfoGame info);
    void display(Arc::InfoGame line);
    Arc::Keys getKeyPress();
    void stop();
    void print_map(Arc::InfoGame info);
    int print_game(Arc::InfoGame info, size_t i, size_t j);
    void print_score(Arc::InfoGame info);
    void print_menu(Arc::InfoGame info, size_t i);
    const std :: string &getName() const;
};

#endif
