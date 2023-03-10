/*
** EPITECH PROJECT , 2021
** ClientNetworkCore
** File description:
** \file ClientNetworkCore.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef CLIENTNETWORKCORE_HPP
#define CLIENTNETWORKCORE_HPP

#include "CustomCluster.hpp"

#include "../../../common/include/Network/NetworkManager.hpp"
#include "Asio/AsioConnectionTCP.hpp"
#include "Asio/AsioConnectionUDP.hpp"
#include "EngineCore.hpp"
#include "EntityFactory/EntityFactory.hpp"
#include "InfoConnection.hpp"
#include "Network/Serializable.hpp"
#include "Network/Tram/ComponentSync.hpp"
#include "Network/Tram/CreateEntityReply.hpp"
#include "Network/Tram/CreateEntityRequest.hpp"
#include "Network/Tram/DestroyEntity.hpp"
#include "Network/Tram/EndGame.hpp"
#include "Network/Tram/GetRoomList.hpp"
#include "Network/Tram/JoinCreateRoomReply.hpp"
#include "Network/Tram/JoinRoom.hpp"
#include "utils/netVector2f.hpp"

#include "Network.hpp"

#define NO_ROOM -1

using Network::InfoConnection;
using Network::netVector2f;
using IConnection = Network::IConnection<DataWrapper>;
using AsioClientTCP = Network::AsioConnectionTCP<DataWrapper>;
using AsioClientUDP = Network::AsioConnectionUDP<DataWrapper>;

using std::make_shared;
using std::shared_ptr;
using std::to_string;

#define MAX_CONNECT_TRY 5

class ClientNetworkCore {
  public:
    ClientNetworkCore(Engine::IGameEngine &engine);
    virtual ~ClientNetworkCore();

    void connect();

    void getRoomList();
    void createRoom();
    void joinRoom(size_t id);
    void quitRoom();
    void createEntity(
        Engine::Entity entity, std::string type, netVector2f const &position, netVector2f const &velocity);
    void destroyEntity(Engine::NetworkId id);
    void syncComponent(
        Engine::NetworkId id, std::type_index const &componentType, size_t componentSize, void *component);
    /**
     * @brief Stop receive loop
     */
    void quit() noexcept;

    bool isMaster() const;

    void receiveLoop();
    void receive();

  protected:
    void receiveRoomList(InfoConnection &info, Tram::GetRoomList &data);
    void receiveJoinRoomReply(InfoConnection &info, Tram::JoinCreateRoomReply &data);
    void receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data);
    void receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data);
    void receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data);
    void receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data);
    void receiveEndGame(InfoConnection &, Tram::EndGame &data);
    void receiveQuitRoom(InfoConnection &);

  private:
    void _receiveTcp();
    void _receiveUdp();
    void _tramExtractor(uint8_t *buffer, std::pair<std::string, std::size_t> &client);
    void _tramHandler(Tram::Serializable &header, InfoConnection &info, uint8_t *buffer);

    void _checkRoom();

  private:
    std::string _serverIp;
    size_t _serverPortTcp;
    size_t _serverPortUdp;
    Engine::IGameEngine &_engine;
    NetworkManager _tcpClient;
    NetworkManager _udpClient;
    bool _loop{true};
    bool _isMaster{false};
    int _roomId{NO_ROOM};
};

#endif // CLIENTNETWORKCORE_HPP