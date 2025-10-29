/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef SNAKE_HPP_

    #define SNAKE_HPP_
    #include "../../IGameModule.hpp"

class Snake : public Arc::IGameModule {
  protected:
    std::string name;
    Arc::InfoGame game;
    std::vector<std::pair<std::size_t, std::size_t>> snakePos;
    bool gameRunning;
    bool goTop;
    bool goRight;
    bool goBottom;
    bool goLeft;
    int mapHeight;
    int mapWidth;
    int sleepTime;
    bool play;
  public:
    Snake(const std::string &name);
    ~Snake() = default;
    Arc::InfoGame loop_game(bool run);
    int handleKeyPress(Arc::Keys c);
    const std :: string &getName() const;
    void setHighestScore(std::size_t best_score);
    void gameLost();
    void generateApple();
    void moveTop();
    void moveRight();
    void moveBottom();
    void moveLeft();
};

#endif
