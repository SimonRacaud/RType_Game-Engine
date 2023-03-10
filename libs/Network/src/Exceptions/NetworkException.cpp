/*
** EPITECH PROJECT, 2021
** NetworkException.cpp
** File description:
** Implementation of exceptions for network
*/

#include "Exceptions/NetworkException.hpp"
#include <utility>

using namespace Network;

invalidConnection::invalidConnection(const std::string &message, const std::string &ip, std::size_t port)
    : _message(formatString::format(message, ip, port))
{
    formatString::removeIdentifiers(_message);
}

const char *invalidConnection::what() const noexcept
{
    return _message.c_str();
}

connectionFailed::connectionFailed(const std::string &message, const std::string &ip, std::size_t port)
    : _message(formatString::format(message, ip, port))
{
    formatString::removeIdentifiers(_message);
}

const char *connectionFailed::what() const noexcept
{
    return _message.c_str();
}