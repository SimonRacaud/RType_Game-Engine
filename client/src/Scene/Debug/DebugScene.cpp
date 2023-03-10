/*
** EPITECH PROJECT , 2021
** DebugScene
** File description:
** \file DebugScene.cpp
** \author simon
** \brief
** \date 08/11/2021
*/

#include "DebugScene.hpp"
#include "Entities/Enemy/Enemy.hpp"
#include "Entities/Equipment/Equipment.hpp"
#include "GameCore/GameCore.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "Entities/Player/Player.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/ColliderSystem/ColliderSystem.hpp"
#include "Components/Hitbox.hpp"
#include "System/TimerSystem/TimerSystem.hpp"
using namespace Scene;

DebugScene::DebugScene(std::string testParam)
    : Engine::AbstractScene<DebugScene>(Engine::ClusterName::HOME), _audio("asset/music/R_Type-03_Game1.ogg")
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, 10);
    std::cerr << testParam << std::endl;
}

// Must be in an Entity's factory
static const auto destruct = [] (Engine::Entity entity, Engine::EntityName name,
                          Engine::ClusterName cluster) {
    std::cerr << "DESTROY " << entity << " " << (int)name << " " << (int)cluster << "\n";
};

void DebugScene::open()
{
    //Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    //Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();

    //Player p({40, 80}, {10, 10}, {40, 40}, "asset/sprites/r-typesheet1.gif"); // outdated
    Enemy enemy(this->getCluster(), vector2D(200, 200), vector2D(0, 0), vector2f(1, 1), "asset/sprites/r-typesheet42.gif", 3, surface(vector2D(33, 18), vector2D(33, 18)));

    /**
     * Entities (must be in an entity's factory)
     */
    //Engine::Entity entity = entityManager.create(destruct, Engine::ClusterName::START, Engine::EntityName::EMPTY, true);

    // entityManager.create(destruct, Engine::ClusterName::START, Engine::EntityName::TEST);
    // Engine::Entity entity2 = entityManager.create(nullptr, Engine::ClusterName::GLOBAL, Engine::EntityName::TEST);

    /**
     * Network ID
     */
    // entityManager.setNetworkId(entity, 42);
//    std::cerr << "Net Id = " << entityManager.getNetworkId(entity) << std::endl;

    /**
     * Components (must be in an entity's factory)
     */
    // componentManager.add<Engine::Position>(entity, 10, 10);
    // componentManager.add<Engine::Position>(entity2, 10, 10);
    // componentManager.add<Engine::Velocity>(entity, 1, 0);


    //    try {
    //        entityManager.remove(Engine::EntityName::TEST);
    //    } catch (Engine::BasicException const &e) {
    //        std::cerr << "En error occurred\n";
    //    }

    //    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);
    //
    //    // Create entities here...
    //
    //    componentManager.add<Engine::Velocity>(entity, 10, 10);
    //    componentManager.add<Engine::Velocity>(entity, 1, 0);
    //
    //    std::shared_ptr<TextManager> tmp = std::make_shared<TextManager>();
    //    tmp->setColor(color_e::RED);
    //    tmp->setContent("mdr");
    //    tmp->setFont("asset/font/Code-Bold.ttf");
    //    componentManager.add<Engine::Render>(entity, tmp);
    //
    //    componentManager.add<Engine::InputEvent>(entity, [](const Engine::Entity &) {
    //        auto pos = GameCore::event->getMousePos();
    //        std::cout << "Mouse pos -> {" << pos.x << ", " << pos.y << "}" << std::endl;
    //    });
    //
    //    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/R_Type-01_theme.ogg");
    //    GET_EVENT_REG.registerEvent<AudioEventVolume>("asset/music/R_Type-01_theme.ogg", 100);
    //    Button test("button", {110, 110}, {1, 1}, std::make_shared<AudioEventPlay>("asset/music/R_Type-01_theme.ogg"));
    //
    //    // other
    //    entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);
    //    componentManager.add<Engine::Velocity>(entity, 20, 20);
    //    std::shared_ptr<ShapeManager> tmp2 = std::make_shared<ShapeManager>(vector2D(200, 200), vector2D(20, 20), color_e::GREEN);
    //    componentManager.add<Engine::Render>(entity, tmp2);
    Equipment(this->getCluster(), vector2D(700, 80));
    GET_EVENT_REG.registerEvent<AudioEventPlay>(_audio);

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::RenderSystem,
        System::InputEventSystem,
        Engine::ColliderSystem,
        Engine::TimerSystem>();
}