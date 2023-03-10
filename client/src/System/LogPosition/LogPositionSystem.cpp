/*
** EPITECH PROJECT , 2021
** LogPositionSystem
** File description:
** \file LogPositionSystem.cpp
** \author simon
** \brief
** \date 04/11/2021
*/

#include "LogPositionSystem.hpp"
#include <iostream>

using namespace System;
using namespace Engine;
using namespace std;

static const Engine::Time freq = static_cast<Engine::Time>(1000);

LogPositionSystem::LogPositionSystem() : Engine::AbstractSystem<LogPositionSystem>(freq, SystemPriority::LOW)
{
    this->setRequirements<Engine::Velocity, Engine::Velocity>();
}

void LogPositionSystem::run(const vector<Entity> &entities)
{
    for (const Entity &entity : entities) {
        auto [position, velocity] = GET_COMP_M.getList<Engine::Velocity, Engine::Velocity>(entity);

        cerr << "Log : Entity[id=" << entity << "] " << position << " " << velocity << endl;
    }
}