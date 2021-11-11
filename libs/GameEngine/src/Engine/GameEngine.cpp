/*
** EPITECH PROJECT , 2021
** Engine
** File description:
** \file Engine.cpp
** \author simon
** \brief
** \date 02/11/2021
*/

#include "GameEngine.hpp"
#include "Utils/SignalManager.hpp"

using namespace Engine;
using namespace std;

GameEngine::GameEngine()
    : _entityManager(new EntityManager),
      _systemManager(new SystemManager),
      _componentManager(new ComponentManager),
      _sceneManager(new SceneManager)
{
    SignalManager::apply();
}

GameEngine::~GameEngine() noexcept
{
    delete _sceneManager;
    delete _entityManager;
    delete _componentManager;
    delete _systemManager;
}

void GameEngine::quit()
{
    this->_loop = false;
}

void GameEngine::exec()
{
    size_t securityCounter = 0; // avoid infinite loop

    while (_loop && securityCounter < MAX_THROW_EXIT) {
        try {
            this->_sceneManager->run();
            this->_eventRegister.execQueue();
        } catch (BasicException const &e) {
            std::cerr << "[Engine] " << e.what() << std::endl;
            securityCounter++;
        }
    }
}

ComponentManager &GameEngine::getComponentManager()
{
    return *_componentManager;
}

IEntityManager &GameEngine::getEntityManager()
{
    return *_entityManager;
}

SystemManager &GameEngine::getSystemManager()
{
    return *_systemManager;
}

SceneManager &GameEngine::getSceneManager()
{
    return *_sceneManager;
}

Event::EventCallbackRegister &GameEngine::getEventRegister()
{
    return _eventRegister;
}