/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/

#include "Pacman.hpp"
#include <iostream>
#include <unistd.h>
#include <ctime>

Pacman::Pacman(const std::string &lname) : name(lname), game(), gameRunning(true), goTop(true), goRight(false), goLeft(false), sleepTime(55000), play(true), lose("FANT"), playghost(true)
{
    std::vector<Arc::Share> dico = {Arc::Share('#', std::make_pair(0, 1), "./src/Ressources/neonWall.png", std::make_pair(30, 30),std::make_pair(0, std::make_pair(0, 255))),
    Arc::Share('0', std::make_pair(3, 0), "./src/Ressources/apple.png", std::make_pair(30, 30), std::make_pair(255, std::make_pair(0, 0))),
    Arc::Share('8', std::make_pair(2, 0), "./src/Ressources/pacman.png", std::make_pair(30, 30), std::make_pair(255, std::make_pair(255, 0))),
    Arc::Share('F', std::make_pair(2, 0), "./src/Ressources/blue_ghost.jpg", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('A', std::make_pair(2, 0), "./src/Ressources/red_ghost.jpg", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('N', std::make_pair(2, 0), "./src/Ressources/green_ghost.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('T', std::make_pair(2, 0), "./src/Ressources/orange_ghost.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('.', std::make_pair(2, 0), "./src/Ressources/pacman_coin.png", std::make_pair(30, 30), std::make_pair(255, std::make_pair(165, 0))),
    Arc::Share(' ', std::make_pair(0, 0), " ", std::make_pair(30, 30), std::make_pair(0, std::make_pair(0, 0)))};
    std::vector<std::string> map = {
        "#####################",
        "#.........#.........#",
        "#0##.####.#.####.##0#",
        "#.##.####.#.####.##.#",
        "#...................#",
        "#.##.#.#######.#.##.#",
        "#....#....#....#....#",
        "####.####.#.####.####",
        "   #.#  FANT   #.#   ",
        "####.# ### ### #.####",
        "    .  #     #  .    ",
        "####.# ####### #.####",
        "   #.#         #.#   ",
        "####.# ####### #.####",
        "#.........#.........#",
        "#.##.####.#.####.##.#",
        "#0.#......8......#.0#",
        "##.#.#.#######.#.#.##",
        "#....#....#....#....#",
        "#.#######.#.#######.#",
        "#...................#",
        "#####################"
        };
    Arc::GameStat<std::vector<std::string>> info_map;
    info_map.val = map;
    info_map.pos = std::make_pair(1, 1);
    Arc::GameStat<std::size_t> info_score;
    info_score.val = 0;
    info_score.pos = std::make_pair(1, 24);
    Arc::GameStat<std::size_t> info_highest_score;
    info_highest_score.val = 0;
    info_highest_score.pos = std::make_pair(1, 25);
    Arc::GameStat<std::size_t> info_timer;
    info_timer.val = 0;
    info_timer.pos = std::make_pair(-50, -50);
    game = Arc::InfoGame(dico, info_map, std::make_pair(10, 16), info_score, info_highest_score, std::make_pair(1800, 1000), "./src/Ressources/Roblox.ttf", info_timer);
    mapWidth = game.map.val.begin()->length();
    mapHeight = game.map.val.size();
    for (int i = 0; i < 4; i++) {
        ghostPos.push_back(std::make_pair(8 + i, 8));
        previousChar.push_back(' ');
        ghostGoTop.push_back(true);
        ghostGoRight.push_back(false);
        ghostGoBottom.push_back(false);
        ghostGoLeft.push_back(false);
    }
    invicible = 800;
}

const std::string &Pacman::getName() const
{
    return name;
}

void Pacman::setHighestScore(std::size_t best_score)
{
    game.highest_score.val = best_score;
}

void Pacman::gameLost()
{
    gameRunning = false;
    for (int i = 0; i < 4; i++)
        ghostPos[i] = {-100, -100};
    game.pos_player = {-10, -10};
    game.timer.pos = {-50, -50};
    game.score.pos = {1, 8};
    game.highest_score.pos = {1, 9};
    game.map.val = {"You lose !",
    "Press 'R' to restart a game, "
    "Press 'M' to go back to Menu,",
    "or 'ESC' to leave the game."};
}

void Pacman::gameWin()
{
    gameRunning = false;
    game.timer.pos = {-50, -50};
    game.score.pos = {1, 8};
    game.highest_score.pos = {1, 9};
    game.map.val = {"You Win ! You can shower now.",
    "Press 'R' to restart a game, "
    "Press 'M' to go back to Menu,",
    "or 'ESC' to leave the game."};
}

void Pacman::moveTop()
{
    if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '0')
        invicible = 1000;
    if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '.') {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.score.val += 1;
        game.pos_player.second -= 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    } else if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '#') {
        return;
    } else {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.second -= 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    }
}

void Pacman::moveRight()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '0')
        invicible = 1000;
    if (game.pos_player.first + 1 == 20 && game.pos_player.second == 10) {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.first = 1;
    }
    if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '.') {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.score.val += 1;
        game.pos_player.first += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    } else if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '#') {
        return;
    } else {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.first += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    }
}

void Pacman::moveBottom()
{
    if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '0')
        invicible = 1000;
    if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '.') {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.score.val += 1;
        game.pos_player.second += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    } else if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '#') {
        return;
    } else {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.second += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    }
}

void Pacman::moveLeft()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '0')
        invicible = 1000;
    if (game.pos_player.first - 1 == 0 && game.pos_player.second == 10) {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.first = 19;
    }
    if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '.') {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.score.val += 1;
        game.pos_player.first -= 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    } else if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '#') {
        return;
    } else {
        game.map.val[game.pos_player.second][game.pos_player.first] = ' ';
        game.pos_player.first -= 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    }
}

bool Pacman::moveGhostTop(int ghost)
{
    if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1] == ' '
        || game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1] == ' ') {
        chooseRandomDirection(ghost);
        ghostGoTop[ghost] = false;
    }
    if (game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first] == '#'
        || lose.find(game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first]) != std::string::npos) {
        return false;
    } else {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = previousChar[ghost];
        previousChar[ghost] = game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first];
        ghostPos[ghost].second -= 1;
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = lose[ghost];
    }
    return true;
}

bool Pacman::moveGhostRight(int ghost)
{
    if (game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first] == ' '
        || game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first] == ' ') {
        chooseRandomDirection(ghost);
        ghostGoRight[ghost] = false;
    }
    if (ghostPos[ghost].first + 1 == 20 && ghostPos[ghost].second == 10) {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = ' ';
        ghostPos[ghost].first = 1;
    }
    if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1] == '#'
        || lose.find(game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1]) != std::string::npos) {
        return false;
    } else {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = previousChar[ghost];
        previousChar[ghost] = game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1];
        ghostPos[ghost].first += 1;
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = lose[ghost];
    }
    return true;
}

bool Pacman::moveGhostBottom(int ghost)
{
    if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1] == ' '
        || game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1] == ' ') {
        chooseRandomDirection(ghost);
        ghostGoBottom[ghost] = false;
    }
    if (game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first] == '#'
        || lose.find(game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first]) != std::string::npos) {
        return false;
    } else {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = previousChar[ghost];
        previousChar[ghost] = game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first];
        ghostPos[ghost].second += 1;
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = lose[ghost];
    }
    return true;
}

bool Pacman::moveGhostLeft(int ghost)
{
    if (game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first] == ' '
        || game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first] == ' ') {
        chooseRandomDirection(ghost);
        return false;
    }
    if (ghostPos[ghost].first - 1 == 0 && ghostPos[ghost].second == 10) {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = ' ';
        ghostPos[ghost].first = 19;
    }
    if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1] == '#'
        || lose.find(game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1]) != std::string::npos) {
        return false;
    } else {
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = previousChar[ghost];
        previousChar[ghost] = game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1];
        ghostPos[ghost].first -= 1;
        game.map.val[ghostPos[ghost].second][ghostPos[ghost].first] = lose[ghost];
    }
    return true;
}

int randomDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    return dis(gen);
}

void Pacman::chooseRandomDirection(int ghost)
{
    int side = randomDirection();
    switch (side) {
        case 0:
            if (game.map.val[ghostPos[ghost].second - 1][ghostPos[ghost].first] != '#') {ghostGoTop[ghost] = true;} break;
        case 1:
            if (game.map.val[ghostPos[ghost].second + 1][ghostPos[ghost].first] != '#') {ghostGoBottom[ghost] = true;} break;
        case 2:
            if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first - 1] != '#') {ghostGoLeft[ghost] = true;} break;
        case 3:
            if (game.map.val[ghostPos[ghost].second][ghostPos[ghost].first + 1] != '#') {ghostGoRight[ghost] = true;} break;
        default:
            chooseRandomDirection(ghost); break;
    }
}

void Pacman::moveGhost(int ghost)
{
    if (ghostGoTop[ghost])
        ghostGoTop[ghost] = moveGhostTop(ghost);
    else if (ghostGoBottom[ghost])
        ghostGoBottom[ghost] = moveGhostBottom(ghost);
    else if (ghostGoLeft[ghost])
        ghostGoLeft[ghost] = moveGhostLeft(ghost);
    else if (ghostGoRight[ghost])
        ghostGoRight[ghost] = moveGhostRight(ghost);
    else
        chooseRandomDirection(ghost);
}

void Pacman::handleGhost()
{
    if (playghost)
        for (int i = 0; i < 4; i++) {
            moveGhost(i);
        }
    playghost = !playghost;
}

void Pacman::isLose()
{
    for (int i = 0; i < 4; i++) {
        if (ghostPos[i].second == game.pos_player.second && ghostPos[i].first == game.pos_player.first) {
            if (invicible > 900) {
                previousChar[i] = ' ';
                ghostPos[i].second = 8;
                ghostPos[i].first = 8;
            } else {
                play = false;
                gameLost();
            }
        }
    }
}

Arc::InfoGame Pacman::loop_game(bool run)
{
    if (run && play) {
        usleep(sleepTime);
        if (gameRunning) {
            if (goTop) {
                moveTop();
            }
            if (goRight) {
                moveRight();
            }
            if (goBottom) {
                moveBottom();
            }
            if (goLeft) {
                moveLeft();
            }
            handleGhost();
        }
        if (game.score.val >= 168)
            gameWin();
    }
    invicible -= 1;
    isLose();
    play = !play;
    return game;
}

int Pacman::handleKeyPress(Arc::Keys c)
{
    if (c == Arc::Keys::Z) {
        goTop = true;
        goRight = false;
        goBottom = false;
        goLeft = false;
    }
    if (c == Arc::Keys::D) {
        goTop = false;
        goRight = true;
        goBottom = false;
        goLeft = false;
    }
    if (c == Arc::Keys::S) {
        goTop = false;
        goRight = false;
        goBottom = true;
        goLeft = false;
    }
    if (c == Arc::Keys::Q) {
        goTop = false;
        goRight = false;
        goBottom = false;
        goLeft = true;
    }
    switch (c) {
        case Arc::Keys::L: return -1;
        case Arc::Keys::G: return -2;
        case Arc::Keys::M: return -3;
        case Arc::Keys::ESC: return -4;
        case Arc::Keys::R: return -5;
        default: return 0;
    }
    return 0;
}

extern "C" Arc::IGameModule* createGame()
{
    return new Pacman("Pacman");
}
