/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/
#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Wrong number of argument" << std::endl;
        return 84;
    }
    try {
        Arc::Core core(av[1]);
        core.run();
    } catch (const Arc::FailLoadingLib &e) {
        std :: cerr << "Failure LibLoad: " << e.what() << std :: endl ;
        return 84;
    } catch (const Arc::Core::Error &e) {
        std :: cerr << "Failure Core: " << e.what() << std :: endl ;
        return 84;
    } catch (const Arc::SafeDirectoryLister::Error &e) {
        std :: cerr << "Failure Menu: " << e.what() << std :: endl ;
        return 84;
    }
    return 0;
}