/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/
#include <iostream>
#include "Ncurses.hpp"
#include <ncurses.h>
#include <unistd.h>

Ncurses::Ncurses(const std::string &name) : name(name)
{
}

const std::string &Ncurses::getName() const
{
    return name;
}

void Ncurses::init(Arc::InfoGame info)
{
    (void)info;
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
}

void Ncurses::init_color(Arc::InfoGame info)
{
    int len_dico = info.assets_dico.size();

    start_color();
    for (int i = 0; i < len_dico; i += 1) {
        init_pair(i + 1, info.assets_dico[i].ncurseclr.first, info.assets_dico[i].ncurseclr.second);
    }
}

void Ncurses::find_correspondance_dico(Arc::InfoGame info, std::string line, int px, int py)
{
    int len_dico = info.assets_dico.size();
    int len_str = line.size();

    for (int i = 0; i < len_str; i += 1) {
        for (int j = 0; j < len_dico; j += 1) {
            if (info.assets_dico[j].c == line[i]) {
                attron(COLOR_PAIR(j + 1));
                mvprintw(py, px, "%c", line[i]);
                attroff(COLOR_PAIR(j + 1));
                break;
            }
            mvprintw(py, px, "%c", line[i]);
        }
        px += 1;
    }
}

void Ncurses::print_map(Arc::InfoGame info)
{
    int len_map = info.map.val.size();
    int px = info.map.pos.first;
    int py = info.map.pos.second;

    for (int i = 0; i < len_map; i += 1) {
        find_correspondance_dico(info, info.map.val[i], px, py);
        py += 1;
    }
}

void Ncurses::print_score(Arc::InfoGame info)
{
    mvprintw(info.score.pos.second, info.score.pos.first, "score %d", info.score.val);
    mvprintw(info.highest_score.pos.second, info.highest_score.pos.first, "best score %d", info.highest_score.val);
    mvprintw(info.timer.pos.second, info.timer.pos.first, "timer %d", info.timer.val);
}

void Ncurses::display(Arc::InfoGame info)
{
    clear();
    usleep(50000);
    init_color(info);
    print_map(info);
    print_score(info);
    refresh();
}

Arc::Keys Ncurses::getKeyPress()
{
    int c = getch();

    if (c >= 'a' && c <= 'z') {
        return static_cast<Arc::Keys>(c - 96);
    }
    switch (c) {
        case 27: return Arc::Keys::ESC;
        case 10: return Arc::Keys::ENTER;
        case KEY_UP: return Arc::Keys::UP;
        case KEY_RIGHT: return Arc::Keys::RIGHT;
        case KEY_DOWN: return Arc::Keys::DOWN;
        case KEY_LEFT: return Arc::Keys::LEFT;
    }
    return Arc::Keys::NONE;
}

void Ncurses::stop()
{
    endwin();
}

extern "C" Arc::IDisplayModule *createGraph()
{
    return new Ncurses("Ncurses");
}
