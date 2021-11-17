/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#ifndef GAMEROOM_HPP
#define GAMEROOM_HPP

#include <thread>
#include <vector>
#include <cstddef>

#include "AsioServerTCP.hpp"
#include "AsioConnectionUDP.hpp"

class GameRoom
{
    public:
        GameRoom(size_t id);
        GameRoom(const GameRoom &);
        ~GameRoom();

        size_t getId() const;

        void create();
        void run();
        void destroy();

        GameRoom &operator=(const GameRoom &);

    private:
        size_t _id;
        std::thread _thread;
};

#endif