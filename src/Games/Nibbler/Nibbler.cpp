/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"
#include <iostream>
#include <unistd.h>
#include <ctime>

Nibbler::Nibbler(const std::string &lname) : name(lname), game(), gameLose(false), gameRunning(true), goTop(true), goRight(false), goLeft(false), goBottom(false), play(true)
{
    std::vector<Arc::Share> dico = {Arc::Share('#', std::make_pair(0, 5), "./src/Ressources/marioWall.png", std::make_pair(30, 30),std::make_pair(0, std::make_pair(128, 0))),
    Arc::Share('0', std::make_pair(4, 0), "./src/Ressources/coin.png", std::make_pair(30, 30), std::make_pair(255, std::make_pair(0, 0))),
    Arc::Share('8', std::make_pair(1, 0), "./src/Ressources/bowser_head.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('=', std::make_pair(1, 0), "./src/Ressources/bowser_body.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share('<', std::make_pair(1, 0), "./src/Ressources/troll_tail.png", std::make_pair(30, 30), std::make_pair(128, std::make_pair(0, 255))),
    Arc::Share(' ', std::make_pair(0, 0), "./src/Ressources/floor_is_lava.png", std::make_pair(30, 30), std::make_pair(0, std::make_pair(0, 0)))};
    std::vector<std::string> map = {
        "###########################################################",
        "#                                                         #",
        "#    ####                                         ####    #",
        "#    ####                    #                    ####    #",
        "#    ####                    #                    ####    #",
        "#                            #                            #",
        "#          ##########        #        ##########          #",
        "#                            #                            #",
        "#                            #                            #",
        "#                                                         #",
        "#     ##                                           ##     #",
        "#     ##        ###########################        ##     #",
        "#     ##                                           ##     #",
        "#                                                         #",
        "#                                                         #",
        "#                                                         #",
        "#                                                         #",
        "#    ####                    8                    ####    #",
        "#    ####                    =                    ####    #",
        "#    ####                    =                    ####    #",
        "#                            <                            #",
        "###########################################################"
    };
    Arc::GameStat<std::vector<std::string>> info_map;
    info_map.val = map;
    info_map.pos = std::make_pair(1, 1);
    Arc::GameStat<std::size_t> info_score;
    info_score.val = 0;
    info_score.pos = std::make_pair(1, 23);
    Arc::GameStat<std::size_t> info_highest_score;
    info_highest_score.val = 0;
    info_highest_score.pos = std::make_pair(1, 24);
    Arc::GameStat<std::size_t> info_timer;
    info_timer.val = 500;
    info_timer.pos = std::make_pair(51, 0);
    game = Arc::InfoGame(dico, info_map, std::make_pair(29, 17), info_score, info_highest_score, std::make_pair(1800, 1000), "./src/Ressources/Roblox.ttf", info_timer);
    mapWidth = game.map.val.begin()->length();
    mapHeight = game.map.val.size();
    nibblerPos = {std::make_pair(29, 17), std::make_pair(29, 18), std::make_pair(29, 19), std::make_pair(29, 20)};
    generateApples();
}

const std::string &Nibbler::getName() const
{
    return name;
}

void Nibbler::setHighestScore(std::size_t best_score)
{
    game.highest_score.val = best_score;
}

void Nibbler::gameLost()
{
    gameLose = true;
    gameRunning = false;
    game.timer.pos = {-50, -50};
    game.score.pos = {1, 5};
    game.highest_score.pos = {1, 6};
    game.map.val = {"You lose !",
    "Press 'R' to restart a game, "
    "Press 'M' to go back to Menu,",
    "or 'ESC' to leave the game."};
}

void Nibbler::generateApples()
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
    for (int i = 0; i < 10; i++) {
        if (!appleSpawn.empty()) {
            int applePosition = std::rand() % appleSpawn.size();
            std::size_t appleX = appleSpawn[applePosition].first;
            std::size_t appleY = appleSpawn[applePosition].second;
            game.map.val[appleX][appleY] = '0';
            appleSpawn.erase(appleSpawn.begin() + applePosition);
            applesPos.push_back(std::make_pair(appleX, appleY));
        }
    }
}

void Nibbler::moveTop()
{
    if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '0') {
        applesPos.pop_back();
        game.score.val += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second -= 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    } else if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '#') {
        if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '#' && game.map.val[game.pos_player.second][game.pos_player.first + 1] == ' ') {
            goTop = false;
            goRight = true;
            moveRight();
        } else if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == ' ' && game.map.val[game.pos_player.second][game.pos_player.first + 1] == '#') {
            goTop = false;
            goLeft = true;
            moveLeft();
        } else {
            gameRunning = false;
        }
    } else if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '=' ||
        game.map.val[game.pos_player.second - 1][game.pos_player.first] == '<') {
        gameLost();
    } else {
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = ' ';
        nibblerPos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second -= 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = '<';
    }
}

void Nibbler::moveRight()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '0') {
        applesPos.pop_back();
        game.score.val += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first += 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    } else if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '#') {
        if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == '#' && game.map.val[game.pos_player.second + 1][game.pos_player.first] == ' ') {
            goRight = false;
            goBottom = true;
            moveBottom();
        } else if (game.map.val[game.pos_player.second - 1][game.pos_player.first] == ' ' && game.map.val[game.pos_player.second + 1][game.pos_player.first] == '#') {
            goRight = false;
            goTop = true;
            moveTop();
        } else {
            gameRunning = false;
        }
    } else if (game.map.val[game.pos_player.second][game.pos_player.first + 1] == '=' ||
        game.map.val[game.pos_player.second][game.pos_player.first + 1] == '<') {
        gameLost();
    } else {
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = ' ';
        nibblerPos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first += 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = '<';
    }
}

void Nibbler::moveBottom()
{
    if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '0') {
        applesPos.pop_back();
        game.score.val += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second += 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    } else if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '#') {
        if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '#' && game.map.val[game.pos_player.second][game.pos_player.first + 1] == ' ') {
            goBottom = false;
            goRight = true;
            moveRight();
        } else if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == ' ' && game.map.val[game.pos_player.second][game.pos_player.first + 1] == '#') {
            goBottom = false;
            goLeft = true;
            moveLeft();
        } else {
            gameRunning = false;
        }
    } else if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '=' ||
        game.map.val[game.pos_player.second + 1][game.pos_player.first] == '<') {
        gameLost();
    } else {
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = ' ';
        nibblerPos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.second += 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = '<';
    }
}

void Nibbler::moveLeft()
{
    if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '0') {
        applesPos.pop_back();
        game.score.val += 1;
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first -= 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
    } else if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '#') {
        if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == '#' && game.map.val[game.pos_player.second - 1][game.pos_player.first] == ' ') {
            goLeft = false;
            goTop = true;
            moveTop();
        } else if (game.map.val[game.pos_player.second + 1][game.pos_player.first] == ' ' && game.map.val[game.pos_player.second - 1][game.pos_player.first] == '#') {
            goLeft = false;
            goBottom = true;
            moveBottom();
        } else {
            gameRunning = false;
        }
    } else if (game.map.val[game.pos_player.second][game.pos_player.first - 1] == '=' ||
        game.map.val[game.pos_player.second][game.pos_player.first - 1] == '<') {
        gameLost();
    } else {
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = ' ';
        nibblerPos.pop_back();
        game.map.val[game.pos_player.second][game.pos_player.first] = '=';
        game.pos_player.first -= 1;
        nibblerPos.insert(nibblerPos.begin(), game.pos_player);
        game.map.val[game.pos_player.second][game.pos_player.first] = '8';
        game.map.val[nibblerPos.back().second][nibblerPos.back().first] = '<';
    }
}

Arc::InfoGame Nibbler::loop_game(bool run)
{
    if (run && play) {
        usleep(40000);
        if (applesPos.empty()) {
            generateApples();
            game.timer.val = 500;
        }
        if (game.timer.val == 0) {
            gameLost();
        }
        if (!gameLose) {
            game.timer.val -= 1;
        }
        if (gameRunning || !gameLose) {
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

int Nibbler::handleKeyPress(Arc::Keys c)
{
    if (!goBottom && !gameLose) {
        if (c == Arc::Keys::Z) {
            gameRunning = true;
            goTop = true;
            goRight = false;
            goBottom = false;
            goLeft = false;
        }
    }
    if (!goLeft && !gameLose) {
        if (c == Arc::Keys::D) {
            gameRunning = true;
            goTop = false;
            goRight = true;
            goBottom = false;
            goLeft = false;
        }
    }
    if (!goTop && !gameLose) {
        if (c == Arc::Keys::S) {
            gameRunning = true;
            goTop = false;
            goRight = false;
            goBottom = true;
            goLeft = false;
        }
    }
    if (!goRight && !gameLose) {
        if (c == Arc::Keys::Q) {
            gameRunning = true;
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
    return new Nibbler("Nibbler");
}
