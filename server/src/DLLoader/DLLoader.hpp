/*
** EPITECH PROJECT, 2021
** R_TYPE
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <cstring>
#include <iostream>
#include <memory>
#if defined(WIN32) || defined(_WIN32) \
    || defined(__WIN32) && !defined(__CYGWIN__)
    //Include asio.hpp because if we put Windows.h we get double include error for windows compilation
    #include <asio.hpp> //for windows.h
    #define LIBTYPE          HINSTANCE
    #define OPENLIB(libname) LoadLibrary(libname)
    #define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
    #define CLOSELIB(handle) FreeLibrary(handle)
#else
    #include <dlfcn.h>
    #define LIBTYPE void *
    #define OPENLIB(libname) \
        dlopen((libname), RTLD_LAZY | RTLD_NODELETE | RTLD_GLOBAL)
    #define LIBFUNC(lib, fn) dlsym((lib), (fn))
    #define CLOSELIB(handle) dlclose(handle)
#endif

template <typename T> class DLLoader {
  public:
    static T *getEntryPoint(std::string filePath, std::string entryName)
    {
        LIBTYPE handle = NULL;
        T *(*instance)(void) = nullptr;
        T *ptr = NULL;

        handle = OPENLIB(filePath.c_str());
        if (handle == NULL) {
            std::cerr << "Could not retreive handle from lib" << std::endl;
            return nullptr;
        }
        *(void **) &instance = LIBFUNC(handle, entryName.c_str());
        if (!instance) {
            std::cerr << "Could not retrieve instance from handler"
                      << std::endl;
            return nullptr;
        }
        ptr = (instance) ();
        CLOSELIB(handle);
        return ptr;
    }

    static void getClosePoint(std::string filePath, std::string closePoint, T *ptr)
    {
        LIBTYPE handle = NULL;
        void (*instance)(T *) = nullptr;

        if (ptr == nullptr)
            return;
        handle = OPENLIB(filePath.c_str());
        if (handle == NULL) {
            std::cerr << "Could not open lib from path given" << std::endl;
            return;
        }
        *(void **) &instance = LIBFUNC(handle, closePoint.c_str());
        if (!instance) {
            std::cerr << "Could not retrieve instance from handler"
                      << std::endl;
            return;
        }
        (instance)(ptr);
        CLOSELIB(handle);
    }
};

#endif /* !DLLOADER_HPP_ */