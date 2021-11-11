/*
** EPITECH PROJECT, 2021
** ConfigFileExternal
** File description:
** ConfigFileExternal.hpp
*/

#ifndef CONFIGFILEEXTERNAL_HPP
#define CONFIGFILEEXTERNAL_HPP

#include "ConfigFile.hpp"
#include "ConfigFileTools.hpp"

class ConfigFileExternal
{
    public:
        static std::any getVector2D(const std::string &data);
};

#endif