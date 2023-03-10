/*
** EPITECH PROJECT , 2021
** CreateEntityReply
** File description:
** \file CreateEntityReply.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "Network/Tram/CreateEntityReply.hpp"

using namespace Tram;

CreateEntityReply::CreateEntityReply()
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply))
{
    std::memset(this->ip, 0, IP_LENGTH);
    std::memset(this->entityType, 0, ENTITY_TYPE_LEN);
}

CreateEntityReply::CreateEntityReply(size_t roomId, bool accept, uint32_t networkId, const std::string &ip, size_t port,
    Time timestamp, const std::string &entityType, netVector2f const &position, netVector2f const &velocity)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply)), roomId(roomId),
      accept(accept), entityId(-1), networkId(networkId), timestamp(timestamp), position(position), velocity(velocity),
      port(port)
{
    std::memset(this->ip, 0, IP_LENGTH);
    std::memset(this->entityType, 0, ENTITY_TYPE_LEN);
    std::strncpy(this->ip, ip.c_str(), IP_LENGTH - 1);
    std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
}

CreateEntityReply::CreateEntityReply(size_t roomId, bool accept, int64_t entityId, uint32_t networkId,
    const std::string &ip, size_t port, Time timestamp, const std::string &entityType, netVector2f const &position,
    netVector2f const &velocity)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply)), roomId(roomId),
      accept(accept), entityId(entityId), networkId(networkId), timestamp(timestamp), position(position),
      velocity(velocity), port(port)
{
    std::memset(this->ip, 0, IP_LENGTH);
    std::memset(this->entityType, 0, ENTITY_TYPE_LEN);
    std::strncpy(this->ip, ip.c_str(), IP_LENGTH - 1);
    std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
}

uint8_t *CreateEntityReply::serialize() const
{
    size_t len = sizeof(CreateEntityReply);
    auto *buffer = new uint8_t[len];

    std::memset(buffer, 0, len);
    std::memcpy(buffer, (uint8_t *) this, len);
    return buffer;
}

void CreateEntityReply::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityReply *>(buffer);

    // header
    this->size = ptr->size;
    this->type = ptr->type;
    // body
    this->roomId = ptr->roomId;
    this->accept = ptr->accept;
    this->entityId = ptr->entityId;
    this->networkId = ptr->networkId;
    this->timestamp = ptr->timestamp;
    this->position = ptr->position;
    this->velocity = ptr->velocity;
    this->port = ptr->port;
    std::strcpy(this->ip, ptr->ip);
    std::strcpy(this->entityType, ptr->entityType);
}

size_t CreateEntityReply::length() const
{
    return sizeof(CreateEntityReply);
}

CreateEntityReply::CreateEntityReply(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply))
{
    CreateEntityReply::deserialize(buffer);
}