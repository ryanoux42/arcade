/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/
#include <iostream>
#include "Core.hpp"
#include "Menu.hpp"

const char* Arc::Core::Error::what() const noexcept
{
    return msg;
}

Arc::Core::Core(const std::string &libpath) : loadDisplay(), loadGame(), graph(nullptr), game(nullptr), accesLibs(), indGraphs(0), indGames(0)
{
    void *lib = loadDisplay.loadLib(libpath);

    if (std::unique_ptr<IDisplayModule>(loadDisplay.getLibObject(lib, "createGraph")) == nullptr) {
        loadDisplay.closeLib(lib);
        throw Core::Error("It's not a graphical lib");
    }
    loadDisplay.closeLib(lib);
    indGraphs = accesLibs.findIndexGraph(libpath);
    graph = std::unique_ptr<IDisplayModule>(loadDisplay.getLibObject(accesLibs.graphsLib.at(indGraphs),"createGraph"));
    game = std::make_unique<Menu>("menu", accesLibs.graphsLibName, accesLibs.gamesLibName, indGraphs);
}

Arc::Core::~Core()
{
    graph.reset();
    game.reset();
    std::size_t len = accesLibs.graphsLib.size();
    for (std::size_t i = 0; i < len; i++) {
        loadDisplay.closeLib(accesLibs.graphsLib.at(i));
    }
    std::size_t len_games = accesLibs.gamesLib.size();
    for (std::size_t i = 0; i < len_games; i++) {
        loadGame.closeLib(accesLibs.gamesLib.at(i));
    }
}

std::vector<std::string> Arc::Core::string_to_vector(std::string str, char delim)
{
    std::size_t pos;
    std::string word;
    std::vector<std::string> res;

    while ((pos = str.find(delim)) != std::string::npos) {
        word = str.substr(0, pos);
        res.push_back(word);
        str.erase(0, pos + 1);
    }
    res.push_back(str);
    return res;
}

void Arc::Core::get_highscore()
{
    std::string line;
    std::ifstream ifs ("./src/Ressources/Save.txt", std::ifstream::in);
    std::vector<std::string> fst_arr;

    if (!ifs) {
      throw Core::Error("Can't open file");
    }
    while (std::getline(ifs, line)) {
        fst_arr = string_to_vector(line, ' ');
        mapBestScore[fst_arr[0]] = std::stoi(fst_arr[1]);
    }
    ifs.close();
}

void Arc::Core::putHighestScore()
{
    if (mapBestScore.find(game->getName()) == mapBestScore.end()) {
        mapBestScore[game->getName()] = 0;
    }
    game->setHighestScore(mapBestScore.at(game->getName()));
}

void Arc::Core::save_bestscore()
{
    InfoGame test = game->loop_game(false);
    std::ofstream out("./src/Ressources/Save.txt", std::ifstream::out);
    if (test.score.val > test.highest_score.val) {
        mapBestScore[game->getName()] = test.score.val;
    }
    if (out) {
        for (auto i = mapBestScore.begin(); i != mapBestScore.end(); ++i) {
            out << i->first << " " << i->second << "\n";
        }
        out.close();
    }
}

void Arc::Core::run()
{
    Keys c = Keys::NONE;
    int val = 0;
    InfoGame test = game->loop_game(false);

    get_highscore();
    putHighestScore();
    graph->init(test);
    while (val != QUIT) {
        test = game->loop_game(true);
        graph->display(test);
        c = graph->getKeyPress();
        val = game->handleKeyPress(c);
        changeLib(val);
        if (val == RESTART) {
            changeLibGame(false);
        }
        if (val > 0) {
            choice_with_menu(val);
        }
    }
    graph->stop();
    save_bestscore();
}

void Arc::Core::choice_with_menu(int val)
{
    int len_games = accesLibs.gamesLib.size();

    val -= 1;
    if (val < len_games) {
        indGames = val;
        changeLibGame(false);
    } else {
        val -= len_games;
        indGraphs = val;
        graph->stop();
        graph.release();
        graph = std::unique_ptr<IDisplayModule>(loadDisplay.getLibObject(accesLibs.graphsLib.at(indGraphs),"createGraph"));
        changeLibGame(true);
    }
}

void Arc::Core::changeLib(int val)
{
    if (val == CHANGE_GRAPH) {
        graph->stop();
        indGraphs += 1;
        if (indGraphs == accesLibs.graphsLib.size()) {
            indGraphs = 0;
        }
        changeLibGraph();
    }
    if (val == CHANGE_GAME) {
        indGames += 1;
        if (indGames == accesLibs.gamesLib.size()) {
            indGames = 0;
        }
        changeLibGame(false);
    }
    if (val == BACK_MENU) {
        changeLibGame(true);
    }
}

void Arc::Core::changeLibGame(bool menu)
{
    InfoGame test = game->loop_game(false);

    if (test.score.val > test.highest_score.val) {
        mapBestScore[game->getName()] = test.score.val;
    }
    game.release();
    if (menu != true) {
        game = std::unique_ptr<IGameModule>(loadGame.getLibObject(accesLibs.gamesLib.at(indGames), "createGame"));
    } else {
        game = std::make_unique<Menu>("menu", accesLibs.graphsLibName, accesLibs.gamesLibName, indGraphs);
    }
    putHighestScore();
    graph->init(game->loop_game(false));
}

void Arc::Core::changeLibGraph()
{
    graph.release();
    graph = std::unique_ptr<IDisplayModule>(loadDisplay.getLibObject(accesLibs.graphsLib.at(indGraphs),"createGraph"));
    graph->init(game->loop_game(false));
}
