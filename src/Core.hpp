/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.rodde
** File description:
** Parser
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include <memory>
#include "LibLoad.hpp"
#include "SafeDirectoryLister.hpp"
#include <fstream>
#include <regex>

#define CHANGE_GRAPH -1
#define CHANGE_GAME -2
#define BACK_MENU -3
#define QUIT -4
#define RESTART -5

namespace Arc {
    class Core {
        public :
            Core(const std::string &libpath);
            ~Core();
            void run();
            std::vector<std::string> string_to_vector(std::string str, char delim);
            void get_highscore();
            void putHighestScore();
            void save_bestscore();
            void changeLib(int val);
            void choice_with_menu(int val);
            void changeLibGame(bool menu);
            void changeLibGraph();
            class Error : public std::exception {
                public:
                    Error(const char *message) : msg(message) {};
                    const char* what() const noexcept;
                private:
                    const char *msg;
            };
        private:
            Arc::LibLoad<IDisplayModule> loadDisplay;
            Arc::LibLoad<IGameModule> loadGame;
            std::unique_ptr<Arc::IDisplayModule> graph;
            std::unique_ptr<Arc::IGameModule> game;
            SafeDirectoryLister accesLibs;
            std::size_t indGraphs;
            std::size_t indGames;
            std::string data;
            std::map<std::string, std::size_t> mapBestScore;
    };
}
#endif
