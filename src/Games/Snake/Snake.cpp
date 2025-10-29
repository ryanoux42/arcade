/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/

#include "Snake.hpp"
#include <iostream>
#include <unistd.h>
#include <ctime>

Snake::Snake(const std::string &lname) : name(lname), game(), gameRunning(true), goTop(true), goRight(false), goLeft(false), goBottom(false), sleepTime(55000), play(true)
{
    std::vector<Arc::Share> dico = {Arc::Share('#', std::make_pair(0, 1), "./src/Ressources/Wall.png", std::make_pair(30, 30),std::make_pair(0, std::make_pair(128, 0))),
    Arc::Share('0', std::make_pair(3, 0), "./src/Ressources/apple.png", std::make_pair(30, 30), std::make_pair(255, std::make_pair(0, 0))),
    Arc::Share('8', std::make_pair(2, 0), "./src/Ressources/Snake_head.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('=', std::make_pair(2, 0), "./src/Ressources/snake_body.jpg", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('<', std::make_pair(2, 0), "./src/Ressources/Snake_tail.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share(' ', std::make_pair(0, 0), "./src/Ressources/dune.png", std::make_pair(30, 30), std::make_pair(0, std::make_pair(0, 0)))};
    std::vector<std::string> map = {
        "##################################################",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                       8                        #",
        "#                       =                        #",
        "#                       =                        #",
        "#                       <                        #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "#                                                #",
        "##################################################"
        };
    Arc::GameStat<std::vector<std::string>> info_map;
    info_map.val = map;
    info_map.pos = std::make_pair(1, 1);
    Arc::GameStat<std::size_t> info_score;
    info_score.val = 0;
    info_score.pos = std::make_pair(1, 18);
    Arc::GameStat<std::size_t> info_highest_score;
    info_highest_score.val = 0;
    info_highest_score.pos = std::make_pair(1, 19);
    Arc::GameStat<std::size_t> info_timer;
    info_timer.val = 0;
    info_timer.pos = std::make_pair(-50, -50);
    game = Arc::InfoGame(dico, info_map, std::make_pair(24, 7), info_score, info_highest_score, std::make_pair(1800, 1000), "./src/Ressources/Roblox.ttf", info_timer);
    mapWidth = game.map.val.begin()->length();
    mapHeight = game.map.val.size();
    snakePos = {std::make_pair(24, 7), std::make_pair(24, 8), std::make_pair(24, 9), std::make_pair(24, 10)};
    generateApple();
}

const std::string &Snake::getName() const
{
    return name;
}

void Snake::setHighestScore(std::size_t best_score)
{
    game.highest_score.val = best_score;
}

void Snake::gameLost()
{
    gameRunning = false;
    game.timer.pos = {-50, -50};
    game.score.pos = {1, 5};
    game.highest_score.pos = {1, 6};
    game.map.val = {"You lose !",
    "Press 'R' to restart a game, "
    "Press 'M' to go back to Menu,",
    "or 'ESC' to leave the game."};
}

void Snake::generateApple()
{
    std::srand(std::time(nullptr));
    std::vector<std::pair<std::size_t, std::size_t>> appleSpawn;

    for (std::size_t i = 0; i < game.map.val.size(); i++) {
        for (std::size_t j = 0; j < game.map.val[i].length(); j++) {
            if (game.map.val[i][j] == ' ') {
                appleSpawn.push_back(std::make_pair(i, j));
            }
        }
    }
    if (!appleSpawn.empty()) {
        int applePosition = std::rand() % appleSpawn.size() - 1;
        std::size_t appleX = appleSpawn[applePosition].first;
        std::size_t appleY = appleSpawn[applePosition].second;
        game.map.val[appleX][appleY] = '0';
    } else {
        gameLost();
    }
}

void Snake::moveTop()
{
    if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '0') {
        game.score.val += 1;
        if (sleepTime > 0) {
            sleepTime -= 5000;
        }
        generateApple();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second -= 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    }
    if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '#' ||
        game.map.val[game.pos_player.second - 1][game.pos_player.first] == '=' ||
        game.map.val[game.pos_player.second - 1][game.pos_player.first] == '<') {
        gameLost();
    } else {
        game.map.val[snakePos.back().second][snakePos.back().first] = ' ';
        snakePos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second -= 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[snakePos.back().second][snakePos.back().first] = '<';
    }
}

void Snake::moveRight()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '0') {
        game.score.val += 1;
        if (sleepTime > 0) {
            sleepTime -= 5000;
        }
        generateApple();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first += 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    }
    if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '#' ||
        game.map.val[game.pos_player.second][game.pos_player.first + 1] == '=' ||
        game.map.val[game.pos_player.second][game.pos_player.first + 1] == '<') {
        gameLost();
    } else {
        game.map.val[snakePos.back().second][snakePos.back().first] = ' ';
        snakePos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first += 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[snakePos.back().second][snakePos.back().first] = '<';
    }
}

void Snake::moveBottom()
{
    if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '0') {
        game.score.val += 1;
        if (sleepTime > 0) {
            sleepTime -= 5000;
        }
        generateApple();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second += 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    }
    if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '#' ||
        game.map.val[game.pos_player.second + 1][game.pos_player.first] == '=' ||
        game.map.val[game.pos_player.second + 1][game.pos_player.first] == '<') {
        gameLost();
    } else {
        game.map.val[snakePos.back().second][snakePos.back().first] = ' ';
        snakePos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second += 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[snakePos.back().second][snakePos.back().first] = '<';
    }
}

void Snake::moveLeft()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '0') {
        game.score.val += 1;
        if (sleepTime > 0) {
            sleepTime -= 5000;
        }
        generateApple();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first -= 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        return;
    }
    if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '#' ||
        game.map.val[game.pos_player.second][game.pos_player.first - 1] == '=' ||
        game.map.val[game.pos_player.second][game.pos_player.first - 1] == '<') {
        gameLost();
    } else {
        game.map.val[snakePos.back().second][snakePos.back().first] = ' ';
        snakePos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first -= 1;
        snakePos.insert(snakePos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[snakePos.back().second][snakePos.back().first] = '<';
    }
}

Arc::InfoGame Snake::loop_game(bool run)
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
        }
    }
    play = !play;
    return game;
}

int Snake::handleKeyPress(Arc::Keys c)
{
    if (!goBottom) {
        if (c == Arc::Keys::Z) {
            goTop = true;
            goRight = false;
            goBottom = false;
            goLeft = false;
        }
    }
    if (!goLeft) {
        if (c == Arc::Keys::D) {
            goTop = false;
            goRight = true;
            goBottom = false;
            goLeft = false;
        }
    }
    if (!goTop) {
        if (c == Arc::Keys::S) {
            goTop = false;
            goRight = false;
            goBottom = true;
            goLeft = false;
        }
    }
    if (!goRight) {
        if (c == Arc::Keys::Q) {
            goTop = false;
            goRight = false;
            goBottom = false;
            goLeft = true;
        }
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
    return new Snake("Snake");
}
