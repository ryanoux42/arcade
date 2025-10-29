/*
** EPITECH PROJECT, 2024
** name
** File description:
** includes
*/

#ifndef SAFEDIRECTORYLISTER_HPP_

    #define SAFEDIRECTORYLISTER_HPP_
    #include <iostream>
    #include <string>
    #include <vector>
    #include <dirent.h>

namespace Arc {
  class SafeDirectoryLister {
    private:
      DIR *_dir;
    public:
      std::vector<std::string> graphsLibName;
      std::vector<std::string> gamesLibName;
      std::vector<void *> graphsLib;
      std::vector<void *> gamesLib;
      SafeDirectoryLister();
      ~SafeDirectoryLister();
      void open(const std::string& path);
      void findLib();
      void checkType(const std::string& file);
      std::size_t findIndexGraph(const std::string& lib);
      class Error : public std::exception {
          public:
              Error(const char *message) : msg(message) {};
              const char* what() const noexcept;
          private:
              const char *msg;
      };
  };
}
#endif
