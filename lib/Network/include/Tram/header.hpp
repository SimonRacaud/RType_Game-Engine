/*
** EPITECH PROJECT , 2021
** header
** File description:
** \file header.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef HEADER_HPP
#define HEADER_HPP

#include <inttypes.h>
#include <stddef.h>
#include <string>
#include <stdexcept>
#include <cstring>
#include "ISerializable.hpp"

#define MAGIC 4242424242

namespace Network
{
    namespace Tram
    {
        enum class TramType {
            NONE,
            GET_ROOM_LIST,
            ROOM_LIST,
            CREATE_ROOM,
            JOIN_ROOM,
            JOIN_ROOM_REPLY,
            QUIT_ROOM,
            CREATE_ENTITY,
            CREATE_ENTITY_REPLY,
            DESTROY_ENTITY,
            SYNC_COMPONENT
        };

        class header : public ISerializable<TramType> {
          public:
            header(TramType type, size_t size = 0);

            /**
             * @brief magic number to check the data type
             */
            size_t magic{MAGIC};
            /**
             * @brief Tram total size
             */
            size_t size{0};
            /**
             * @brief Tram type
             */
            TramType type;

            virtual uint8_t *deserialize();
            /**
             * @throws InvalidArgument : invalid magic number
             * @param buffer
             */
            virtual void serialize(uint8_t *buffer);
            virtual size_t length() const;
        };

        header::header(TramType type, size_t size)
            : size(size), type(type)
        {}

        uint8_t *header::deserialize()
        {
            size_t length = this->length();
            uint8_t *buffer = new uint8_t[length];

            std::memcpy(buffer, (void*)this, length);
            return buffer;
        }

        void header::serialize(uint8_t *buffer)
        {
            header *ptr = reinterpret_cast<header *>(buffer);

            if (this->magic != ptr->magic) {
                throw std::invalid_argument("header::serialize invalid magic number");
            }
            this->size = ptr->size;
            this->type = ptr->type;
        }

        size_t header::length() const
        {
            return sizeof(header);
        }
    } // namespace Tram
}

#endif // HEADER_HPP
