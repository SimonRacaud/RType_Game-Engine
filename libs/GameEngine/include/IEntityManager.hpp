/*
** EPITECH PROJECT , 2021
** IEntityManager
** File description:
** \file IEntityManager.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef IENTITYMANAGER_HPP
#define IENTITYMANAGER_HPP

#include "global.hpp"
#include "EntityRegister/EntityRegister.hpp"
#include <vector>
#include <cstddef>

namespace Engine {
    class IEntityManager {
        /**
         * \brief Access to the signatures of the entities
         */
        friend class ComponentManager;
      public:
        virtual ~IEntityManager() = default;

        virtual Entity create(EntityDestructor destructor, ClusterName cluster,
            EntityName name, bool setNetworkId = false) = 0;

        virtual void remove(Entity entity) = 0;
        virtual void remove(EntityName name) = 0;
        virtual void remove(ClusterName cluster) = 0;

        virtual bool exist(Entity entity) = 0;
        virtual bool exist(EntityName name) = 0;

        virtual Entity getId(EntityName name) = 0;
        virtual std::size_t getClusterSize(ClusterName cluster) = 0;

        virtual Entity getId(NetworkId id) = 0;
        virtual void setNetworkId(Entity entity) = 0;
        virtual NetworkId getNetworkId() = 0;
        virtual void forceApplyId(Entity entity, NetworkId networkId) = 0;


        /**
         * @brief The network id of an entity. NotfoundException if it doesn't have one
         * @param entity
         * @return
         */
        virtual NetworkId getNetworkId(Entity entity) = 0;

        /**
         * @brief Get the cluster of an entity
         * @param entity
         * @return
         */
        virtual ClusterName getCluster(Entity entity) = 0;

      private:
        virtual std::vector<Signature> &_getSignatureList() = 0;
        virtual const Signature &_getSignature(Entity entity) = 0;

        virtual EntityRegister &_getEntityRegister() = 0;
    };
}

#endif // IENTITYMANAGER_HPP
