/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML(const std::string &name) : name(name), window(),
    texts(), event(), rect(), map_pos(), font()
{  
}

const std::string &SFML::getName() const
{
    return name;
}

void SFML::init(Arc::InfoGame info)
{
    window.create(sf::VideoMode(info.window_size.first, info.window_size.second), "SFML Window");
    if (!font.loadFromFile(info.font)) {
        std::cerr << "Failed to load font" << std::endl;
    }
    textures.clear();
    for (const auto &asset : info.assets_dico) {
        sf::Texture texture;
        if (texture.loadFromFile(asset.image_path)) {
            textures.push_back(texture);
        } else {
            textures.push_back(sf::Texture());
        }
    }
    map_pos = sf::Vector2f(info.map.pos.first, info.map.pos.second);
}

void SFML::display(Arc::InfoGame info)
{
    window.clear();
    print_map(info);
    print_score(info);
    window.display();
}

void SFML::print_menu(Arc::InfoGame info, size_t i)
{
    sf::Text text;
    text.setFont(font);
    text.setString(info.map.val[i]);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    if (info.highest_score.pos.first == -1000){
        text.setPosition(map_pos.x, map_pos.y * 15);    
    } else {
        text.setPosition(map_pos.x, map_pos.y);
    }
    window.draw(text);
}

int SFML::print_game(Arc::InfoGame info, size_t i, size_t j)
{
    for (size_t k = 0; k < info.assets_dico.size(); k++) {
        if (info.assets_dico[k].c == info.map.val[i][j]) {
            if (!textures[k].getSize().x || !textures[k].getSize().y) {
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(info.assets_dico[k].image_size.first, info.assets_dico[k].image_size.second));
                rect.setFillColor(sf::Color(info.assets_dico[k].rgb.first, info.assets_dico[k].rgb.second.first, info.assets_dico[k].rgb.second.second));
                rect.setPosition(map_pos);
                window.draw(rect);
            } else {
                sf::Sprite sprite(textures[k]);
                sprite.setPosition(map_pos);
                window.draw(sprite);
            }
            map_pos.x += info.assets_dico[k].image_size.first;
            return 1;
        }
    }
    return 0;
}

void SFML::print_map(Arc::InfoGame info)
{
    for (size_t i = 0; i < info.map.val.size(); i++) {
        for (size_t j = 0; j < info.map.val[i].size(); j++) {
            if (!print_game(info, i, j)) {
                print_menu(info, i);
                break;
            }
        }
        map_pos.y += info.assets_dico[0].image_size.second;
        map_pos.x = info.map.pos.first;
    }
    map_pos.y = info.map.pos.second;
}

void SFML::print_score(Arc::InfoGame info)
{
    int dicoSize = info.assets_dico.size();

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(27);
    text.setFillColor(sf::Color::White);

    text.setPosition(info.score.pos.first * 30, info.score.pos.second * 30);
    text.setString("Score: " + std::to_string(info.score.val));
    window.draw(text);

    text.setPosition(info.highest_score.pos.first * 30, info.highest_score.pos.second * 30);
    text.setString("Highest score: " + std::to_string(info.highest_score.val));
    window.draw(text);

    text.setPosition(info.timer.pos.first * 30, info.timer.pos.second * 30);
    text.setString("Timer: " + std::to_string(info.timer.val));
    window.draw(text);
}

Arc::Keys SFML::getKeyPress()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                return static_cast<Arc::Keys>(static_cast<int>(Arc::Keys::A) + (event.key.code - sf::Keyboard::A));
            }
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    return Arc::Keys::UP;
                case sf::Keyboard::Right:
                    return Arc::Keys::RIGHT;
                case sf::Keyboard::Down:
                    return Arc::Keys::DOWN;
                case sf::Keyboard::Left:
                    return Arc::Keys::LEFT;
                case sf::Keyboard::Return:
                    return Arc::Keys::ENTER;
                case sf::Keyboard::Escape:
                    return Arc::Keys::ESC;
                default:
                    break;
            }
        }
    }
    return Arc::Keys::NONE;
}

void SFML::stop()
{
    window.close();
}

extern "C" Arc::IDisplayModule *createGraph()
{
    return new SFML("SFML");
}
