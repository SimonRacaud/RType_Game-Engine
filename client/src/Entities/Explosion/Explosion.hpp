/*
** EPITECH PROJECT, 2021
** Explosion
** File description:
** Explosion.hpp
*/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Item/vector2D.hpp"
#include "CustomCluster.hpp"
#include "GameCore/GameCore.hpp"

using Engine::ClusterName;

class Explosion
{
    public:
        Explosion(ClusterName cluster, const vector2D &pos);
        ~Explosion() = default;

        void setNetworkId(uint32_t entityId);

    private:
        Engine::Entity _entity;
};

#endif