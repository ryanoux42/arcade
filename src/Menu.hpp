/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef MENU_HPP_

    #define MENU_HPP_
    #include "IGameModule.hpp"

class Menu : public Arc::IGameModule {
  protected:
    std::string name;
    Arc::InfoGame game;
    std::size_t ind;
  public:
    Menu(const std::string &lname,  std::vector<std::string> graphsLib,
    std::vector<std::string> gamesLib, std::size_t indGraphs);
    ~Menu() = default;
    const std :: string &getName() const;
    void setHighestScore(std::size_t best_score);
    Arc::InfoGame loop_game(bool run);
    std::size_t move_jump(std::size_t offset);
    std::size_t move_taken(std::size_t offset);
    void go_down();
    void go_up();
    int handleKeyPress(Arc::Keys c);
};

#endif
