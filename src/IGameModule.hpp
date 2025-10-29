/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.rodde
** File description:
** Parser
*/

#ifndef IGAMEMODULE_HPP_
    #define IGAMEMODULE_HPP_
    #include "Share.hpp"
    #include "Keys.hpp"

namespace Arc {
    class IGameModule {
        public :
            virtual ~IGameModule() = default;
            virtual Arc::InfoGame loop_game(bool run) = 0;
            virtual int handleKeyPress(Arc::Keys c) = 0;
            virtual const std :: string &getName() const = 0;
            virtual void setHighestScore(std::size_t best_score) = 0;
    };
}

#endif
