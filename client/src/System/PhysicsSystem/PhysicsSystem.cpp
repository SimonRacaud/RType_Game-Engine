/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 PhysicsSystem.cpp.cc
*/

#include "PhysicsSystem.hpp"
#include "FactoryShortcuts.hpp"

using namespace Engine;

static const Time refreshFreq = static_cast<Time>(10);
static const SystemPriority priority = SystemPriority::HIGH;

PhysicsSystem::PhysicsSystem()
    : AbstractSystem<PhysicsSystem>(refreshFreq, priority), _lastExecTime(Clock::now())
{
    this->setRequirements<Engine::Position, Engine::Velocity>();
}

void PhysicsSystem::run(const std::vector<Engine::Entity> &entities)
{
    TimePoint now = Clock::now();
    float delta = (float)DurationCast(Clock::now() - _lastExecTime).count() / 1000;

    for (const Entity &entity : entities) {
        auto [position, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(entity);
        position.x += velocity.x * delta;
        position.y += velocity.y * delta;
    }
    _lastExecTime = now;
}
