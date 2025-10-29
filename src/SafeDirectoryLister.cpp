/*
** EPITECH PROJECT, 2024
** Z.cpp
** File description:
** ex00
*/

#include "SafeDirectoryLister.hpp"
#include <memory>
#include "LibLoad.hpp"

const char* Arc::SafeDirectoryLister::Error::what() const noexcept
{
    return msg;
}

Arc::SafeDirectoryLister::SafeDirectoryLister() : _dir(NULL), graphsLibName(), gamesLibName(), graphsLib(), gamesLib()
{
    open("lib");
    findLib();
}

Arc::SafeDirectoryLister::~SafeDirectoryLister()
{
    if (_dir != NULL) {
        closedir(_dir);
    }
}

void Arc::SafeDirectoryLister::open(const std::string& path)
{
    if (_dir != NULL) {
        closedir(_dir);
    }
    if ((_dir = opendir(path.c_str())) == NULL) {
        throw Error("Open directory");
    }
}

void Arc::SafeDirectoryLister::findLib()
{
    std::string filename;
    struct dirent *_read;
    std::size_t pos;

    _read = readdir(_dir);
    while (_read != 0) {
        if (_read == NULL) {
            throw Error("Read directory");
        }
        filename = _read->d_name;
        pos = filename.find(".");
        if (pos != std::string::npos) {
            if (filename.substr(pos) == ".so") {
                checkType("lib/" + filename);
            }
        }
        _read = readdir(_dir);
    }
}

void Arc::SafeDirectoryLister::checkType(const std::string& filename)
{
    Arc::LibLoad<IDisplayModule> loadDisplay;
    Arc::LibLoad<IGameModule> loadGame;
    void *lib = loadDisplay.loadLib(filename);

    if (std::unique_ptr<IDisplayModule>(loadDisplay.getLibObject(lib, "createGraph")) != nullptr) {
        graphsLibName.push_back(filename);
        graphsLib.push_back(lib);
        return ;
    }
    loadDisplay.closeLib(lib);
    lib = loadGame.loadLib(filename);
    if (std::unique_ptr<IGameModule>(loadGame.getLibObject(lib, "createGame")) != nullptr) {
        gamesLibName.push_back(filename);
        gamesLib.push_back(lib);
        return ;
    }
    loadGame.closeLib(lib);
}

std::size_t Arc::SafeDirectoryLister::findIndexGraph(const std::string& lib)
{
    std::size_t len = graphsLibName.size();

    for (std::size_t i = 0; i < len; i++) {
        if (graphsLibName[i] == lib) {
            return i;
        }
    }
    return 0;
}
