/*
** EPITECH PROJECT, 2021
** ComponentRollback.cpp
** File description:
** Apply component received from the network to the local game engine
*/

#include "ComponentRollback.hpp"

#include "Components/Health.hpp"
#include "Components/AnimationInfo.hpp"
#include "Component/Render.hpp"
#include "AnimationManager/AnimationManager.hpp"

const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>> ComponentRollback::hashcodeComponents{
        {Engine::Position::type.hash_code(), ComponentRollback::RollbackPosition},
        {Engine::Velocity::type.hash_code(), ComponentRollback::ApplyComponent<Engine::Velocity>},
        {Engine::ScoreComponent::type.hash_code(), ComponentRollback::ApplyComponent<Engine::ScoreComponent>},
        {Engine::EquipmentComponent::type.hash_code(), ComponentRollback::ApplyComponent<Engine::EquipmentComponent>},
        {Component::Health::type.hash_code(), ComponentRollback::ApplyComponent<Component::Health>},
        {Component::AnimationInfo::type.hash_code(), ComponentRollback::ApplyAnimationInfo}
    };

void ComponentRollback::Apply(Tram::ComponentSync const &tram)
{
    const Engine::Entity entity = GET_ENTITY_M.getId(tram.networkId);

    if (hashcodeComponents.contains(tram.componentType)) {
        hashcodeComponents.at(tram.componentType)(entity, tram.component, tram.timestamp);
    } else {
        std::cerr << "ComponentRollback::Apply component not found." << std::endl;
    }
}

void ComponentRollback::ApplyAnimationInfo(Engine::Entity id, void *component, long)
{
    try {
        Component::AnimationInfo *info = reinterpret_cast<Component::AnimationInfo *>(component);
        auto &render = GET_COMP_M.get<Engine::Render>(id);
        auto &hitbox = GET_COMP_M.get<Engine::Hitbox>(id);

        if (render._src.empty() == false) {
            auto *enemyRender = reinterpret_cast<AnimationManager *>(render._src[0].get());

            const surface surface(info->_animPos, info->_animSize);
            enemyRender->setFocus(surface);
            enemyRender->setSrcPath(info->_path);
            enemyRender->setNbMember(info->_nbFrames);
            enemyRender->refresh();
        }
        // update hitbox size
        hitbox.x = (float)info->_animSize.x;
        hitbox.y = (float)info->_animSize.y;
    } catch (Engine::NotFoundException const &) {
        // the component doesn't exist anymore. Ignore
    } catch (std::exception const &e) {
        std::cerr << "ComponentRollback::ApplyComponent Fail to apply changes" << std::endl;
    }
}

void ComponentRollback::RollbackPosition(Engine::Entity id, void *component, long int timestamp)
{
    auto &oldComponent = GET_COMP_M.get<Engine::Position>(id);
    const auto &velocity = GET_COMP_M.get<Engine::Velocity>(id);
    const Engine::Position *newComponent = reinterpret_cast<Engine::Position *>(component);
    float deltaTime = (GET_NOW - timestamp) / 1000;

    oldComponent.x = newComponent->x + (velocity.x * deltaTime);
    oldComponent.y = newComponent->y + (velocity.y * deltaTime);
}
