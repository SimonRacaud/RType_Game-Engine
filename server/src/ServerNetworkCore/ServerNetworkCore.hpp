/*
** EPITECH PROJECT , 2021
** ServerNetworkCore
** File description:
** \file ServerNetworkCore.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef SERVERNETWORKCORE_HPP
#define SERVERNETWORKCORE_HPP

#include "InfoConnection.hpp"
#include "Network.hpp"
#include "Network/NetworkManager.hpp"
#include "NetworkRoom.hpp"
#include "globalServer.hpp"
#include "include/Asio/AsioConnectionTCP.hpp"
#include "include/Asio/AsioConnectionUDP.hpp"

#include "Network/Serializable.hpp"
#include "Network/Tram/ComponentSync.hpp"
#include "Network/Tram/CreateEntityReply.hpp"
#include "Network/Tram/CreateEntityRequest.hpp"
#include "Network/Tram/DestroyEntity.hpp"
#include "Network/Tram/EndGame.hpp"
#include "Network/Tram/GetRoomList.hpp"
#include "Network/Tram/JoinCreateRoomReply.hpp"
#include "Network/Tram/JoinRoom.hpp"

#include "GameRoomManager/GameRoomManager.hpp"
#include "GarbageEntity/GarbageEntity.hpp"
#include "IServerNetworkCore.hpp"

#include "Debug.hpp"
#include "utils/netVector2f.hpp"

#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

using std::make_shared;
using std::shared_ptr;
using std::vector;

using Network::InfoConnection;
using Network::netVector2f;
using IConnection = Network::IConnection<DataWrapper>;
using AsioServerTCP = Network::AsioConnectionTCP<DataWrapper>;
using AsioServerUDP = Network::AsioConnectionUDP<DataWrapper>;

class ServerNetworkCore : public IServerNetworkCore {
  public:
    ServerNetworkCore();
    virtual ~ServerNetworkCore() = default;

    /**
     * @brief Broadcast entity creation request
     * @param roomId
     * @param type Entity type name
     */
    void createEntity(size_t roomId, std::string const &type, netVector2f const &position, netVector2f const &velocity);
    /**
     * @brief Broadcast entity destruction request
     * @param roomId
     * @param id
     */
    void destroyEntity(size_t roomId, NetworkId id);
    /**
     * @brief Broadcast component synchronization request
     * @param roomId
     * @param id
     * @param componentType
     * @param componentSize
     * @param component
     */
    void syncComponent(
        size_t roomId, NetworkId id, std::type_index const &componentType, size_t componentSize, void *component);

    void endGame(size_t roomId);
    void receiveLoop();

    static bool _loop;

  private:
    void receiveGetRoomList(InfoConnection &info);
    void receiveCreateRoom(InfoConnection &info);
    void receiveQuitRoom(InfoConnection &info);
    void receiveJoinRoom(InfoConnection &info, Tram::JoinRoom &data);
    void receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data);
    void receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data);
    void receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data);
    void receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data);

  private:
    static void sig_handler(int);
    void _receiveFromChannel(NetworkManager &net);
    void _tramHandler(Tram::Serializable &header, InfoConnection &info, uint8_t *buffer);
    void _closeGameRoom(size_t roomId);
    void _removeClient(size_t roomId, std::string const &ip);

    shared_ptr<NetworkRoom> _getRoom(size_t roomId);

    void _removePlayer(shared_ptr<NetworkRoom> &room, size_t clientIndex);

  private:
    size_t _portUdp;
    size_t _portTcp;
    size_t _portUdpClient;
    NetworkManager _tcpServer;
    NetworkManager _udpServer;
    GarbageEntity _garbageEntity;
    GameRoomManager _roomManager;
    size_t _maxRoomClient;
    vector<shared_ptr<NetworkRoom>> _rooms;
    vector<size_t> _roomFreeIds;
};

#endif // SERVERNETWORKCORE_HPP