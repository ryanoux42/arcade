/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.rodde
** File description:
** Parser
*/

#ifndef IDISPLAYMODULE_HPP_
    #define IDISPLAYMODULE_HPP_
    #include "Share.hpp"
    #include "Keys.hpp"

namespace Arc {
    class IDisplayModule {
        public :
            virtual ~IDisplayModule() = default;
            virtual void init(Arc::InfoGame info) = 0;
            virtual void display(Arc::InfoGame info) = 0;
            virtual Arc::Keys getKeyPress() = 0;
            virtual void stop() = 0;
            virtual const std :: string &getName() const = 0;
    };
}

#endif
