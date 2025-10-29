/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/
#include <iostream>
#include "Menu.hpp"

Menu::Menu(const std::string &lname,  std::vector<std::string> graphsLib,
std::vector<std::string> gamesLib, std::size_t indGraphs) : name(lname), game(), ind(0)
{
    std::vector<Arc::Share> tests = {Arc::Share('<', std::make_pair(0, 2), "", std::make_pair(0, 2),std::make_pair(0, std::make_pair(0, 2))),
    Arc::Share('x', std::make_pair(2, 0), "", std::make_pair(0, 2),std::make_pair(0, std::make_pair(0, 2)))};
    std::vector<std::string> map;

    map.push_back("Game lib:");
    int len_games = gamesLib.size();
    int ok = 0;
    for (int i = 0; i < len_games; i++) {
        if (ok == 0) {
            map.push_back(gamesLib[i] += "<");
            ok = 1;
        } else {
            map.push_back(gamesLib[i] += " ");
        }
    }
    map.push_back("Graphical lib:");
    std::size_t len = graphsLib.size();
    for (std::size_t i = 0; i < len; i++) {
        if (i == indGraphs) {
            map.push_back(graphsLib[i] += "x");
        } else {
            map.push_back(graphsLib[i] += " ");
        }
    }
    Arc::GameStat<std::vector<std::string>> info_map;
    info_map.val = map;
    info_map.pos = std::make_pair(0, 0);
    Arc::GameStat<std::size_t> info_score;
    info_score.val = 0;
    info_score.pos = std::make_pair(-100, -100);
    Arc::GameStat<std::size_t> info_highest_score;
    info_highest_score.val = 0;
    info_highest_score.pos = std::make_pair(-1000, -100);
    Arc::GameStat<std::size_t> info_timer;
    info_timer.val = 0;
    info_timer.pos = std::make_pair(-100, -100);
    game = Arc::InfoGame(tests, info_map, std::make_pair(0, 1), info_score, info_highest_score, std::make_pair(1800, 1000), "./src/Ressources/Roblox.ttf", info_timer);
}

const std::string &Menu::getName() const
{
    return name;
}

void Menu::setHighestScore(std::size_t best_score)
{
    game.highest_score.val = best_score;
}

Arc::InfoGame Menu::loop_game(bool run)
{
    (void)run;
    return game;
}

std::size_t Menu::move_jump(std::size_t offset)
{
        if (0 < game.pos_player.second && game.pos_player.second < game.map.val.size()
        && game.map.val[game.pos_player.second] == "Graphical lib:") {
             game.pos_player.second += offset;
             return 1;
        }
        return 0;
}

std::size_t Menu::move_taken(std::size_t offset)
{
        if (0 < game.pos_player.second && game.pos_player.second < game.map.val.size()
        && game.map.val[game.pos_player.second][game.map.val[game.pos_player.second].size() - 1] == 'x') {
            game.pos_player.second += offset;
            ind += offset;
            return 1;
        }
        return 0;
}

void Menu::go_down()
{
    game.map.val[game.pos_player.second][game.map.val[game.pos_player.second].size() - 1] = ' ';
    game.pos_player.second += 1;
    ind += 1;
    if (game.pos_player.second >= game.map.val.size()) {
        game.pos_player.second = 1;
        ind = 0;
    }
    while (move_jump(1) == 1 || move_taken(1) == 1) {
    }
    if (game.pos_player.second >= game.map.val.size()) {
        game.pos_player.second = 1;
        ind = 0;
    }
    game.map.val[game.pos_player.second][game.map.val[game.pos_player.second].size() - 1] = '<';
}

void Menu::go_up()
{
    game.map.val[game.pos_player.second][game.map.val[game.pos_player.second].size() - 1] = ' ';
    game.pos_player.second -= 1;
    ind -= 1;
    if (game.pos_player.second <= 0) {
        game.pos_player.second = game.map.val.size() - 1;
        ind = game.map.val.size() - 3;
    }
    while (move_jump(-1) == 1 || move_taken(-1) == 1) {
    }
    if (game.pos_player.second <= 0) {
        game.pos_player.second = game.map.val.size() - 1;
        ind = game.map.val.size() - 3;
    }
    game.map.val[game.pos_player.second][game.map.val[game.pos_player.second].size() - 1] = '<';
}

int Menu::handleKeyPress(Arc::Keys c)
{
    switch (c) {
        case Arc::Keys::UP: go_up(); return 0;
        case Arc::Keys::DOWN: go_down(); return 0;
        case Arc::Keys::L: return -1;
        case Arc::Keys::G: return -2;
        case Arc::Keys::ESC: return -4;
        case Arc::Keys::ENTER: return (ind + 1);
        default: return 0;
    }
    return 0;
}
