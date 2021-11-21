/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityHitManager
*/

#include "EntityHitManager.hpp"
#include "Scene/EndGame/EndGameScene.hpp"
#include "Components/Health.hpp"
#include "Event/EntityRemove/EntityRemoveEvent.hpp"
#include "Event/AddScore/AddScoreEvent.hpp"

EntityHitManager::EntityHitManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const EntityHit *)>(entityHit));
}

void entityHit(const EntityHit *e)
{
	if (!GET_COMP_M.hasComponent<Component::Health>(e->_entity))
		throw Engine::InvalidTypeException("Trying to hit an entity without a health component");
	auto &health = GET_COMP_M.get<Component::Health>(e->_entity);

	health._health -= e->_damage;
	if (health._health <= 0) {
		if (GET_COMP_M.get<Component::EntityMask>(e->_entity)._currentMask == Component::MASK::PLAYER) {
			GET_EVENT_REG.registerEvent<AddScoreEvent>(e->_entity);
		}
		GET_EVENT_REG.registerEvent<EntityRemoveEvent>(e->_entity);
	}
}

void playerHitEquipment(const PlayerEquipmentHit *e)
{
	auto &equip = GET_COMP_M.get<Engine::EquipmentComponent>(e->_entity);

	GET_EVENT_REG.registerEvent<EntityRemoveEvent>(e->_equipment);
	equip.counter++;
}
