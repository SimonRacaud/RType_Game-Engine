/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 EntityManager.hpp.h
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include "EntityRegister/EntityRegister.hpp"
#include "global.hpp"
#include "ClusterName.hpp"
#include "EntityName.hpp"
#include "IEntityManager.hpp"
#include "FactoryShortcuts.hpp"
#include "Engine/EngineFactory.hpp"
#include "ComponentManager/ComponentManager.hpp"

namespace Engine
{
    #define GET_COMP_M   Engine::EngineFactory::getInstance().getComponentManager()

    /**
     * @brief Management of the entities
     */
    class EntityManager : public IEntityManager {
      public:
        friend class ComponentManager;

        explicit EntityManager();
        virtual ~EntityManager() noexcept;

        /**
         * @brief Create a new entity
         * @param destructor : callback
         * @param cluster : cluster name
         * @param name : entity name (optional)
         * @param setNetworkId : unique id for the network (optional)
         * @return
         */
        Entity create(EntityDestructor destructor = nullptr, ClusterName cluster = ClusterName::GLOBAL,
            EntityName name = EntityName::EMPTY,
            bool setNetworkId = false);

        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(Entity entity);
        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(EntityName name);
        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(ClusterName cluster);

        /**
         * @brief Do the entity exist?
         * @param entity
         * @return
         */
        bool exist(Entity entity);
        /**
         * @brief Do the named entity in that cluster exist?
         * @param name
         * @param cluster
         * @return
         */
        bool exist(EntityName name);

        /**
         * @brief Get the entity id linked to that name
         * @throws NotFoundException
         * @param name
         * @return
         */
        Entity getId(EntityName name);
        /**
         * @brief Get the number of entity in a cluster
         * @param cluster
         * @return
         */
        std::size_t getClusterSize(ClusterName cluster);
        /**
         * @brief Get the entity id linked to that network id
         * @throws NotFoundException
         * @throws FatalErrorException
         * @param id
         * @return
         */
        Entity getId(NetworkId id);
        /**
         * @brief Set a network id to an entity
         * @throws InvalidParameterException : entity not found
         * @throws FatalErrorException : network id already reserved
         * @param entity
         * @param networkId
         */
        void setNetworkId(Entity entity);

        /**
         * @brief Force apply a network id
         * @param entity
         */
        void forceApplyId(Entity entity, NetworkId networkId);
        /**
         * @brief Generate a new network id
         * @return
         */
        NetworkId getNetworkId();

        /**
         * @brief The network id of an entity. NotfoundException if it doesn't have one
         * @param entity
         * @return
         */
        NetworkId getNetworkId(Entity entity);

        /**
         * @brief Get the cluster of an entity
         * @param entity
         * @return
         */
        ClusterName getCluster(Entity entity);

      private:
        void _allocate(std::size_t size);

        std::vector<Signature> &_getSignatureList();
        /**
         * @throws NotFoundException
         */
        const Signature &_getSignature(Entity entity);

        EntityRegister &_getEntityRegister();

        void _removeEntityComponents(Entity entity, Signature const &signature);

      private:
        EntityRegister _entities;
    };
} // namespace Engine

#endif // ENTITYMANAGER_HPP