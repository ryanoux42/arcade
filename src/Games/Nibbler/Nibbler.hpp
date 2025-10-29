/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_

    #define NIBBLER_HPP_
    #include "../../IGameModule.hpp"

class Nibbler : public Arc::IGameModule {
  protected:
    std::string name;
    Arc::InfoGame game;
    std::vector<std::pair<std::size_t, std::size_t>> nibblerPos;
    std::vector<std::pair<std::size_t, std::size_t>> applesPos;
    bool gameLose;
    bool gameRunning;
    bool goTop;
    bool goRight;
    bool goBottom;
    bool goLeft;
    int mapHeight;
    int mapWidth;
    bool play;
  public:
    Nibbler(const std::string &name);
    ~Nibbler() = default;
    Arc::InfoGame loop_game(bool run);
    int handleKeyPress(Arc::Keys c);
    const std :: string &getName() const;
    void setHighestScore(std::size_t best_score);
    void gameLost();
    void generateApples();
    void moveTop();
    void moveRight();
    void moveBottom();
    void moveLeft();
};

#endif
