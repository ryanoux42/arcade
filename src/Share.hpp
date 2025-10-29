/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.rodde
** File description:
** Parser
*/

#ifndef SHARE_HPP_
    #define SHARE_HPP_
    #include <string>
    #include <utility>
    #include <vector>

namespace Arc {
    class Share {
        public :
            Share(char valc,  std::pair<std::size_t, std::size_t> valfrontclr, std::string path,
            std::pair<std::size_t, std::size_t> size,
            std::pair<std::size_t, std::pair<std::size_t, std::size_t>> color_rgb) :
            c(valc), ncurseclr(valfrontclr), image_path(path), image_size(size), rgb(color_rgb) {};
            ~Share() = default;
            char c;
            std::pair<std::size_t, std::size_t> ncurseclr;
            std::string image_path;
            std::pair<std::size_t, std::size_t> image_size;
            std::pair<std::size_t, std::pair<std::size_t, std::size_t>> rgb;
    };
    template<typename T> class GameStat {
        public :
            GameStat() {};
            ~GameStat() = default;
            T val;
            std::pair<std::size_t, std::size_t> pos;
    };
    class InfoGame {
        public :
            InfoGame() {};
            InfoGame(std::vector<Arc::Share> dico, GameStat<std::vector<std::string>> valmap,
            std::pair<std::size_t, std::size_t> pplayer, GameStat<std::size_t> valscore,
            GameStat<std::size_t> valhighest_score, std::pair<std::size_t, std::size_t> size_win,
            std::string text, GameStat<std::size_t> valtimer):
            assets_dico(dico), map(valmap), pos_player(pplayer), score(valscore),
            highest_score(valhighest_score), window_size(size_win),
            font(text), timer(valtimer) {};
            ~InfoGame() = default;
            std::vector<Arc::Share> assets_dico;
            GameStat<std::vector<std::string>> map;
            std::pair<std::size_t, std::size_t> pos_player;
            GameStat<std::size_t> score;
            GameStat<std::size_t> highest_score;
            std::pair<std::size_t, std::size_t> window_size;
            std::string font;
            GameStat<std::size_t> timer;
        };
}

#endif
