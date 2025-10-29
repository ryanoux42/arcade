/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.rodde
** File description:
** Parser
*/

#ifndef LIBLOAD_HPP_
    #define LIBLOAD_HPP_

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

namespace Arc {
    template<typename T> class LibLoad {
        public :
            LibLoad();
            ~LibLoad();
            void *loadLib(const std::string &libpath);
            T *getLibObject(void *libaccess, const std::string &entryPoint);
            void closeLib(void *libaccess);
    };
    class FailLoadingLib : public std::exception {
        public:
            FailLoadingLib(const char *message) : msg(message) {};
            const char* what() const noexcept;
        private:
            const char *msg;
    };
}
#endif
