/*
** EPITECH PROJECT, 2021
** testClientUDPdataWrapper.cpp
** File description:
** test network UDP connection with data wrapper client side
*/

#include <cstring>
#include "Asio/AsioConnectionUDP.hpp"
#include "Data/DataWrapping/DataWrapper.hpp"
#include "Network/Tram/JoinRoom.hpp"
#include "Test.hpp"

using namespace Network;

static int startClientSendData(uint8_t *data, const std::size_t length)
{
    const std::size_t portClient(8081);
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    AsioConnectionUDP<DataWrapper> client(portClient);
    usleep(300000); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);
    DataWrapper wrapper(data, length);

    if (!connected)
        return 84;
    client.send(wrapper, ipServer, portServer);
    usleep(300000); // wait for the server to receive

    client.disconnect(ipServer, portServer);
    return 0;
}

/**
 * @brief Test
 *  AsioConnectionUDP::connect()
 *  AsioConnectionUDP::send()
 *  AsioConnectionUDP::disconnect()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testUDPclientDataWrapperJoinRoom()
{
    Tram::JoinRoom my_data{51};

    return startClientSendData(my_data.serialize(), my_data.length());
}

int testUDPclientDataWrapperGetRoomList()
{
    std::vector<std::size_t> listOfRooms;
    listOfRooms.emplace_back(222);
    listOfRooms.emplace_back(444);

    Tram::GetRoomList my_data{listOfRooms};

    return startClientSendData(my_data.serialize(), my_data.length());
}

int testUDPclientDataWrapperCreateEntityReply()
{
    Tram::CreateEntityReply my_data(123, true, 456, 789, "ip", 8080, 321, "type", netVector2f(0, 0), netVector2f(0, 0));

    return startClientSendData(my_data.serialize(), my_data.length());
}
int testUDPclientDataWrapperCreateEntityRequest()
{
    Tram::CreateEntityRequest my_data(123, 456, "789", 321, netVector2f(0, 0), netVector2f(0, 0));

    return startClientSendData(my_data.serialize(), my_data.length());
}
int testUDPclientDataWrapperJoinCreateRoomReply()
{
    Tram::JoinCreateRoomReply my_data(true, 123456789, 987);

    return startClientSendData(my_data.serialize(), my_data.length());
}

int testUDPclientDataWrapperComponentSync()
{
    auto *ptr = new TestComponent(753951);
    Time time = (Time) 424242;
    auto type = std::type_index(typeid(TestComponent));
    const size_t compSize = sizeof(TestComponent);

    Tram::ComponentSync my_data(43, 42, time, type, compSize, (void *) ptr);

    return startClientSendData(my_data.serialize(), my_data.length());
}

int testUDPclientDataWrapperDestroyEntity()
{
    Tram::DestroyEntity my_data(987654321, 665544);

    return startClientSendData(my_data.serialize(), my_data.length());
}