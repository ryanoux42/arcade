/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/
#include <iostream>
#include <dlfcn.h>
#include "LibLoad.hpp"

const char* Arc::FailLoadingLib::what() const noexcept
{
    return msg;
}

template<typename T> Arc::LibLoad<T>::LibLoad()
{
}

template Arc::LibLoad<Arc::IGameModule>::LibLoad();
template Arc::LibLoad<Arc::IDisplayModule>::LibLoad();

template<typename T> Arc::LibLoad<T>::~LibLoad()
{
}

template Arc::LibLoad<Arc::IGameModule>::~LibLoad();
template Arc::LibLoad<Arc::IDisplayModule>::~LibLoad();

template<typename T> void *Arc::LibLoad<T>::loadLib(const std::string &libpath)
{
    void *libaccess = dlopen(libpath.c_str(), RTLD_NOW);

    if (!libaccess) {
        throw FailLoadingLib(dlerror());
    }
    dlerror();
    return libaccess;
}

template void *Arc::LibLoad<Arc::IGameModule>::loadLib(const std::string &libpath);
template void *Arc::LibLoad<Arc::IDisplayModule>::loadLib(const std::string &libpath);

template<typename T> T* Arc::LibLoad<T>::getLibObject(void *libaccess, const std::string &entryPoint)
{
    T* (*entry)() = (T* (*)())dlsym(libaccess, entryPoint.c_str());

    if (!entry) {
        return nullptr;
    }
    dlerror();
    return entry();
}

template Arc::IGameModule *Arc::LibLoad<Arc::IGameModule>::getLibObject(void *libaccess, const std::string &entryPoint);
template Arc::IDisplayModule*Arc::LibLoad<Arc::IDisplayModule>::getLibObject(void *libaccess, const std::string &entryPoint);

template<typename T> void Arc::LibLoad<T>::closeLib(void *libaccess)
{
    if (libaccess != nullptr) {
        dlclose(libaccess);
        libaccess = nullptr;
    }
}

template void Arc::LibLoad<Arc::IGameModule>::closeLib(void *libaccess);
template void Arc::LibLoad<Arc::IDisplayModule>::closeLib(void *libaccess);
