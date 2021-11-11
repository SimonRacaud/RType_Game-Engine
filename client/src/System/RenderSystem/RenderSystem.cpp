/*
** EPITECH PROJECT , 2021
** RenderSystem
** File description:
** RenderSystem.cpp
*/

#include <iostream>
#include "RenderSystem.hpp"
#include "Component/Render.hpp"
#include "GameCore/GameCore.hpp"
#include "Interface/IMovable.hpp"

System::RenderSystem::RenderSystem() : Engine::AbstractSystem<RenderSystem>()
{
    this->setRequirements<Engine::Render>();
}

void System::RenderSystem::run(const std::vector<Engine::Entity> &entities)
{
    if (GameCore::window && GameCore::window->isOpen()) {
        GameCore::window->clear();
        for (const Engine::Entity &entity : entities) {
            auto [render] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::Render>(entity);

            if (Engine::EngineFactory::getInstance().getComponentManager().hasComponent<Engine::Position>(entity)) {
                auto [position] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::Position>(entity);
                for (auto &itr : render._src) {
                    if (dynamic_cast<IMovable *>(itr.get())->getPosition() != vector2D(position.x, position.y)) {
                        dynamic_cast<IMovable *>(itr.get())->setPosition(vector2D(position.x, position.y));
                        itr->refresh();
                    }
                }
            }
            for (int it = render._pos.size() - 1; it >= 0; it--)
                render._src[render._pos[it]]->draw(GameCore::window);
        }
        GameCore::window->refresh();
    } else {
        throw std::invalid_argument("Window is close");
    }
}