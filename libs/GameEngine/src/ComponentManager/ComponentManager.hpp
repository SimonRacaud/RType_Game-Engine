/*
** EPITECH PROJECT , 2021
** ComponentManager
** File description:
** simon
*/

#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include "BaseComponent.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "EntityName.hpp"
#include "global.hpp"
#include "EntityManager/EntityManager.hpp"
#include "Exception/NotRegisteredException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/FatalErrorException.hpp"
#include "EngineFactory.hpp"
#include "FactoryShortcuts.hpp"

namespace Engine
{
    using std::array;
    using std::size_t;
    using std::shared_ptr;
    using std::unique_ptr;
    using std::vector;

    class ComponentManager {
        friend class EntityManager;

      public:
        ComponentManager();
        virtual ~ComponentManager() = default;

        void allocate();
        template <typename ComponentType> void registerComponent();

        template <typename ComponentType> ComponentType &get(Entity entity);

        template <typename... ComponentTypeList>
        std::tuple<ComponentTypeList &...> getList(Entity entity);

        template <typename ComponentType, typename... Args>
        void add(Entity entity, Args &&...args);

        template <typename ComponentType> void remove(Entity entity);
        template <typename ComponentType> void remove(EntityName name);

        template <typename ComponentType>
        Entity getOwner(const ComponentType &component) const;

        template <typename ComponentType>
        void foreachComponent(ComponentBrowseFunction<ComponentType> fn);

        template <typename ComponentType>
        bool hasComponent(Entity entity);
        template <typename... ComponentTypeList>
        bool hasComponents(Entity entity);

      private:
        template <typename ComponentType> void _checkType() const;
        template <typename... ComponentTypeList> void _checkTypeList() const;

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer();

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer() const;

      private:
        array<shared_ptr<IComponentTypeRegister>, MAX_COMPONENT_TYPE>
            _componentRegisters;
        size_t _componentTypeCount{0};
    };

    template <typename ComponentType>
    bool ComponentManager::hasComponent(Entity entity)
    {
        this->_checkType<ComponentType>();
        return GET_ENTITY_M._getSignature(entity)[ComponentType::getIndex()];
    }

    template <typename... ComponentTypeList>
    bool ComponentManager::hasComponents(Entity entity)
    {
        (this->_checkTypeList<ComponentTypeList>(), ...);
        Signature requirements = Signature();
        (requirements.set(ComponentTypeList::getIndex()), ...);
        return (requirements & GET_ENTITY_M._getSignature(entity)) == requirements;
    }

    template <typename ComponentType>
    void ComponentManager::registerComponent()
    {
        this->_checkType<ComponentType>();
        // Set idx
        ComponentType::setIndex(_componentTypeCount);
        this->_componentTypeCount++;
        // Create register
        vector<Signature> &signatures =
            GET_ENTITY_M._getSignatureList();
        _componentRegisters[ComponentType::type] =
            std::make_shared<ComponentTypeRegister<ComponentType>>(signatures);
    }

    template <typename ComponentType>
    ComponentType &ComponentManager::get(Entity entity)
    {
        this->_checkType<ComponentType>();
        if (this->hasComponent<ComponentType>(entity) == false) {
            std::cerr << "ComponentManager::getComponent Entity " <<
                entity << " request " << ComponentType::type << " component."
                      << std::endl;
            throw NotFoundException(
                "ComponentManager::getComponent The entity "
                "don't have the requested component.");
        }
        return this->getComponentContainer<ComponentType>()->get(entity);
    }

    template <typename... ComponentTypeList>
    std::tuple<ComponentTypeList &...> ComponentManager::getList(Entity entity)
    {
        this->_checkTypeList<ComponentTypeList...>();
        if (this->hasComponents<ComponentTypeList...>(entity) == false) {
            ((std::cerr << "ComponentManager::getComponents Entity "
            << entity << " request " << ComponentTypeList::type << " component."
                        << std::endl), ...);
            throw NotFoundException(
                "ComponentManager::getComponents The entity "
                "don't have the requested Components.");
        }
        return std::tie(
            this->getComponentContainer<ComponentTypeList>()->get(entity)...);
    }

    template <typename ComponentType, typename... Args>
    void ComponentManager::add(Entity entity, Args &&...args)
    {
        this->_checkType<ComponentType>();
        if (_componentRegisters[ComponentType::getIndex()] == nullptr) {
            throw NotRegisteredException("Component type not registered");
        }
        if (this->hasComponent<ComponentType>(entity)) {
            std::cerr << "ComponentManager::addComponent : Entity "
                      << (uint)entity << " => Component " <<
                      ComponentType::type << std::endl;
            throw FatalErrorException("ComponentManager::addComponent, Same "
                                        "component added several time"
                                        "on an entity.");
        }
        this->getComponentContainer<ComponentType>()->add(
            entity, std::forward<Args>(args)...);
        // Send message to system
        const Signature &signature = GET_ENTITY_M._getSignature(entity);
        GET_SYS_M.onEntityUpdated(entity, signature);
    }

    template <typename ComponentType>
    void ComponentManager::remove(Entity entity)
    {
        this->_checkType<ComponentType>();
        if (this->hasComponent<ComponentType>(entity) == false) {
            throw InvalidParameterException(
                "ComponentManager::remove The "
                "entity don't have the component.");
        }
        this->getComponentContainer<ComponentType>()->remove(entity);
        // Send message to systems
        const auto &signature = GET_ENTITY_M._getSignature(entity);
        GET_SYS_M.onEntityUpdated(entity, signature);
    }

    template <typename ComponentType>
    void ComponentManager::remove(EntityName name)
    {
        Entity entity = GET_ENTITY_M.getId(name);

        this->remove<ComponentType>(entity);
    }

    template <typename ComponentType>
    Entity ComponentManager::getOwner(const ComponentType &component) const
    {
        this->_checkType<ComponentType>();
        return this->getComponentContainer<ComponentType>()->getOwner(component);
    }

    template <typename ComponentType>
    void ComponentManager::foreachComponent(
        ComponentBrowseFunction<ComponentType> fn)
    {
        this->_checkType<ComponentType>();
        vector<unique_ptr<ComponentType>> &components =
            this->getComponentContainer<ComponentType>()->getComponents();

        std::for_each(components.begin(), components.end(), fn);
    }

    template <typename ComponentType> void ComponentManager::_checkType() const
    {
        static_assert(std::is_base_of<BaseComponent<ComponentType>,
                          ComponentType>::value,
            "Invalid component type");
    }

    template <typename... ComponentTypeList>
    void ComponentManager::_checkTypeList() const
    {
        (this->_checkType<ComponentTypeList>(), ...);
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer()
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::getIndex()].get());
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer() const
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::getIndex()].get());
    }
} // namespace Engine

#endif // COMPONENTMANAGER_HPP
