/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef PACMAN_HPP_

    #define PACMAN_HPP_
    #include "../../IGameModule.hpp"
    #include <random>

class Pacman : public Arc::IGameModule {
  protected:
    std::string name;
    Arc::InfoGame game;
    bool gameRunning;
    bool goTop;
    bool goRight;
    bool goBottom;
    bool goLeft;
    int mapHeight;
    int mapWidth;
    int sleepTime;
    bool play;
    bool playghost;
    std::size_t invicible;
    std::string lose;
    std::vector<bool> ghostGoTop;
    std::vector<bool> ghostGoRight;
    std::vector<bool> ghostGoBottom;
    std::vector<bool> ghostGoLeft;
    std::vector<std::pair<size_t, size_t>> ghostPos;
    std::vector<char> previousChar;
  public:
    Pacman(const std::string &name);
    ~Pacman() = default;
    Arc::InfoGame loop_game(bool run);
    int handleKeyPress(Arc::Keys c);
    const std :: string &getName() const;
    void setHighestScore(std::size_t best_score);
    void moveGhost(int ghost);
    void handleGhost();
    void gameLost();
    void gameWin();
    void generateApple();
    void moveTop();
    void moveRight();
    void moveBottom();
    void moveLeft();
    bool moveGhostTop(int ghost);
    bool moveGhostRight(int ghost);
    bool moveGhostBottom(int ghost);
    bool moveGhostLeft(int ghost);
    void chooseRandomDirection(int ghost);
    void isLose();
};

#endif
