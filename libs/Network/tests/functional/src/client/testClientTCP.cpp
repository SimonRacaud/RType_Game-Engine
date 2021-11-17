/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"

using namespace Network;

class intWrapperTCP {
  public:
    intWrapperTCP() = default;
    explicit intWrapperTCP(int val) : _val(val){};
    ~intWrapperTCP() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapperTCP);
    }

    [[nodiscard]] int getVal() const
    {
        return _val + _otherVal;
    }

    [[nodiscard]] uint8_t *serialize() const
    {
        auto data(new uint8_t[sizeof(intWrapperTCP)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }
    intWrapperTCP(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapperTCP))
            return;
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{111};
    int _otherVal{333};
};

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 * @return 0 if test succeeded
 */
int testTCPclientConnectSendDisconnect()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    intWrapperTCP myData(888);
    AsioClientTCP<intWrapperTCP> client;
    usleep(300000); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}