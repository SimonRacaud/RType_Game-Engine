/*
** EPITECH PROJECT, 2021
** NetworkEventManager
** File description:
** NetworkEventManager.cpp
*/

#include "Event/GUI/SelectPreviousScene.hpp"
#include "Scene/EndGame/EndGameScene.hpp"
#include "NetworkEventManager.hpp"
#include "GameCore/GameCore.hpp"
#include "EngineCore.hpp"

NetworkEventManager::NetworkEventManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();
    reg.registerCallback<RoomListEventRefresh>(NetworkEventManager::refreshRoomList);
    reg.registerCallback<QuitEvent>(NetworkEventManager::Quit);
    reg.registerCallback<NewGameEvent>(NetworkEventManager::NewGame);
    reg.registerCallback<JoinRoomEvent>(NetworkEventManager::JoinRoom);
}

void NetworkEventManager::refreshRoomList(const RoomListEventRefresh *)
{
    GameCore::engine.getEntityManager().remove(Engine::ClusterName::ROOM_LIST_ITEMS);
    GameCore::networkCore.getRoomList();
}

void NetworkEventManager::NewGame(const NewGameEvent *)
{
    GameCore::networkCore.createRoom();
}

void NetworkEventManager::JoinRoom(const JoinRoomEvent *e)
{
    GameCore::networkCore.joinRoom(e->_roomId);
}

void NetworkEventManager::Quit(const QuitEvent *)
{
    GameCore::networkCore.quitRoom();
    GET_SCENE_M.select<Scene::EndGameScene>();
}