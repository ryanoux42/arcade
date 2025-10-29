/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef NCURSES_HPP_

    #define NCURSES_HPP_
    #include "../../IDisplayModule.hpp"

class Ncurses : public Arc::IDisplayModule {
  protected:
    std::string name;
  public:
    Ncurses(const std::string &name);
    ~Ncurses() = default;
    void init(Arc::InfoGame info);
    void display(Arc::InfoGame info);
    Arc::Keys getKeyPress();
    void stop();
    const std :: string &getName() const;
    void init_color(Arc::InfoGame info);
    void print_map(Arc::InfoGame info);
    void find_correspondance_dico(Arc::InfoGame info, std::string line, int px, int py);
    void print_score(Arc::InfoGame info);
};

#endif
