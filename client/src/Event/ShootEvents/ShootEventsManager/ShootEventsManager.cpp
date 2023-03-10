/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEventsManager
*/

#include "ShootEventsManager.hpp"

#include <stdexcept>
#include "Component/Shooting.hpp"
#include "GameCore/GameCore.hpp"

ShootEventsManager::ShootEventsManager()
{
    GET_EVENT_REG.registerCallback(std::function<void(const ChargeShot *e)>(chargeShot));
    GET_EVENT_REG.registerCallback(std::function<void(const ReleaseChargedShot *e)>(releaseShot));
}

void chargeShot(const ChargeShot *e)
{
    auto &shooting = GET_COMP_M.get<Component::Shooting>(e->_entity);

    shooting._chargeStart = std::chrono::steady_clock::now();
}

void releaseShot(const ReleaseChargedShot *e)
{
    auto now = std::chrono::steady_clock::now();
    auto &shooting = GET_COMP_M.get<Component::Shooting>(e->_entity);
    auto &pos = GET_COMP_M.get<Engine::Position>(e->_entity);
    auto &hit = GET_COMP_M.get<Engine::Hitbox>(e->_entity);

    size_t nb_sec = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch() - shooting._chargeStart.time_since_epoch())
                        .count();
    if (nb_sec >= 1)
        nb_sec += 1;
    const vector2D position(
        pos.x + hit.x + GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_ANIMATION_FOCUS_SIZE")[0].x, pos.y);
    std::vector<vector2D> velocityList = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_VELOCITY");
    if (velocityList.size() != 5)
        throw std::invalid_argument("Velocity must have 5 values");
    if (nb_sec > 4)
        nb_sec = 4;
    try {
        GameCore::entityFactory.createBullet(position, velocityList[nb_sec], e->_owner, nb_sec);
    } catch (std::exception const &e) {
        std::cerr << "ShootEventsManager : fail to create Bullet entity. " << e.what() << std::endl;
    }
}