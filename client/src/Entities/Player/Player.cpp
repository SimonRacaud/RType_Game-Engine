/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Player
*/

#include "Player.hpp"
#include "Component/Render.hpp"
#include "Component/SyncSend.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Hitbox.hpp"
#include "Components/EntityLinkComponent.hpp"
#include "Components/ScoreComponent.hpp"
#include "Component/InputEvent.hpp"
#include "Component/Shooting.hpp"
#include "AnimationManager/AnimationManager.hpp"

#include "Entities/Explosion/Explosion.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "Event/MoveEvents/MoveEvents.hpp"
#include "Event/MoveEvents/MoveHandler/MoveHandler.hpp"
#include "Event/ShootEvents/ShootEvents.hpp"
#include "Event/ShootEvents/ShootEventsManager/ShootEventsManager.hpp"
#include <stdexcept>

using namespace Engine;

bool Player::animationPlayer(Engine::ClusterName cluster, Engine::Entity once)
{
	static auto last = std::chrono::system_clock::from_time_t(0);
	bool stat = GET_COMP_M.hasComponent<Component::EntityMask>(once) && GET_COMP_M.get<Component::EntityMask>(once)._currentMask == Component::MASK::ENEMY;

	std::cout << "HERE1 -> " << ((stat) ? "true" : "false") << std::endl;
	if (stat) {
		size_t nb_sec = std::chrono::duration<double>(std::chrono::system_clock::now() - last).count();

		std::cout << "HERE2 -> " << nb_sec << std::endl;
		if (nb_sec > std::chrono::duration<double>(1).count() && GET_COMP_M.hasComponent<Engine::Position>(once)) {
			auto &pos = GET_COMP_M.get<Engine::Position>(once);

			Explosion(cluster, vector2D(pos.x, pos.y));
            last = std::chrono::system_clock::now();
		}
	}
	return stat;
}

void Player::hit(Engine::ClusterName cluster, Engine::Entity a, Engine::Entity b)
{
	std::cout << "PLAYER HITBOX HAS BEEN HIT" << std::endl;
	Player::animationPlayer(cluster, a) || Player::animationPlayer(cluster, b);
}

Player::Player(ClusterName cluster, int playerNumber, const vector2D &position,
    const vector2D &velocity)
{
    const vector2D hitboxSize(40, 40);

    MoveHandler handler;
    ShootEventsManager shootEventsManager;
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);

    this->configAppearance(entity, position, componentManager, playerNumber);

    componentManager.add<Component::EntityMask>(entity, Component::MASK::PLAYER);
    componentManager.add<Engine::Position>(entity, position.x, position.y);
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    componentManager.add<Engine::Hitbox>(entity, hitboxSize.x, hitboxSize.y,
        [cluster](Engine::Entity a, Engine::Entity b) {
            Player::hit(cluster, a, b);
        });
    componentManager.add<Engine::ScoreComponent>(entity);
    componentManager.add<Engine::EquipmentComponent>(entity);
    componentManager.add<Component::Shooting>(entity);
    componentManager.add<Component::SyncSend>(entity, Component::MASK::PLAYER, Component::toSync::POSITION | Component::toSync::VELOCITY | Component::toSync::SCORE);
    this->configEvent(entity, componentManager);
    _entity = entity;
}

void Player::configAppearance(Entity entity, vector2D const &position, Engine::ComponentManager &componentManager,
    int playerNumber)
{
    const std::string &spriteSkin = "asset/sprites/r-typesheet42.gif";
    const std::string &sprite = "asset/sprites/r-typesheet1.gif";
    std::vector<size_t> ps;
    std::vector<Engine::DrawableObj> renderList;
    std::shared_ptr<AnimationManager> anim = std::make_shared<AnimationManager>();
    vector2D playerEntitySize = GameCore::config->getVar<vector2D>("PLAYER_SPRITE_SIZE");

    if (playerNumber > 4) {
        throw std::invalid_argument("Player::configAppearance invalid player id number");
    }
    anim->setFocus(surface(vector2D(0, playerNumber * playerEntitySize.y), playerEntitySize));
    anim->setNbMember(2);
    anim->setPosition(position);
    anim->setSrcPath(spriteSkin);

    // CHARGE SHOT START
    std::shared_ptr<AnimationManager> chargeShot = std::make_shared<AnimationManager>();
    vector2D shotEntitySize(30, 32);

    chargeShot->setFocus(surface(vector2D(1, 51), shotEntitySize));
    chargeShot->setNbMember(8);
    chargeShot->setPosition(position);
    chargeShot->setOffsetPosition(vector2D(playerEntitySize.x - shotEntitySize.x / 2, playerEntitySize.y / 2 - shotEntitySize.y / 2));
    chargeShot->setSrcPath(sprite);
    // END

    // PROPULSION START
    std::shared_ptr<AnimationManager> propulsor = std::make_shared<AnimationManager>();
    vector2D propEntitySize(34, 29);

    propulsor->setFocus(surface(vector2D(199, 18), propEntitySize));
    propulsor->setNbMember(2);
    propulsor->setPosition(position);
    propulsor-> setOffsetPosition(vector2D(-propEntitySize.x, playerEntitySize.y / 2 - propEntitySize.y / 2));
    propulsor->setSrcPath(sprite);
    // END

    renderList.push_back(anim);
    renderList.push_back(propulsor);
    renderList.push_back(chargeShot);
    ps.push_back(0);
    ps.push_back(1);
    componentManager.add<Engine::Render>(entity, renderList, ps); // apply
}

void Player::configEvent(Entity entity, Engine::ComponentManager &componentManager)
{
    const float speed = 10;
    componentManager.add<Engine::InputEvent>(entity, [speed](const Engine::Entity &local) {
        auto &shooting = GET_COMP_M.get<Component::Shooting>(local);
        auto &render = GET_COMP_M.get<Engine::Render>(local);

        /// Player move
        //TODO when adding [keybindings] change it here with GameCore setting
        if (GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_UP)) {
            GET_EVENT_REG.registerEvent<MoveUp>(local, speed);
        } else if (GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_DOWN)) {
            GET_EVENT_REG.registerEvent<MoveDown>(local, speed);
        }
        if ((GameCore::event->isKeyReleased(IEventManager::keyEvent_e::KEY_UP) && 
            (!GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_DOWN))) ||
            (GameCore::event->isKeyReleased(IEventManager::keyEvent_e::KEY_RIGHT) &&
                    (!GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_LEFT)))) {
            GET_EVENT_REG.registerEvent<NotMovingY>(local);
        }
        if (GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_LEFT)) {
            GET_EVENT_REG.registerEvent<MoveLeft>(local, speed);
        } else if (GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_RIGHT)) {
            GET_EVENT_REG.registerEvent<MoveRight>(local, speed);
        }
        if ((GameCore::event->isKeyReleased(IEventManager::keyEvent_e::KEY_LEFT) &&
            (!GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_RIGHT))) ||
                    (GameCore::event->isKeyReleased(IEventManager::keyEvent_e::KEY_RIGHT) &&
                    (!GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_LEFT)))) {
            GET_EVENT_REG.registerEvent<NotMovingX>(local);
        }
        //SHOOTING
        if (!GameCore::event->isStateChange(IEventManager::keyEvent_e::KEY_SPACE) && GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_SPACE) && !shooting._isCharging) {
            shooting._isCharging = true;
            render.setRender(2);
            GET_EVENT_REG.registerEvent<ChargeShot>(local);
        } else if (GameCore::event->isKeyReleased(IEventManager::keyEvent_e::KEY_SPACE) && shooting._isCharging) {
            shooting._isCharging = false;
            render.removeRender(2);
            GET_EVENT_REG.registerEvent<SetProgressBarValue>(Engine::EntityName::BEAM_PROGRESS, 0);
            GET_EVENT_REG.registerEvent<ReleaseChargedShot>(local);
        } else if (!GameCore::event->isStateChange(IEventManager::keyEvent_e::KEY_SPACE)
            && GameCore::event->isKeyPressed(IEventManager::keyEvent_e::KEY_SPACE) && shooting._isCharging) {
            auto now = std::chrono::steady_clock::now();
            auto &shooting = GET_COMP_M.get<Component::Shooting>(local);

            size_t nb_milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - shooting._chargeStart.time_since_epoch()).count();
            size_t value = (nb_milli * 100 / 5000);

            if (value > 100)
                value = 100;
            GET_EVENT_REG.registerEvent<SetProgressBarValue>(Engine::EntityName::BEAM_PROGRESS, value);
        }
    });
}

void Player::setNetworkId(uint32_t entityId)
{
    GameCore::engine.getEntityManager().setNetworkId(_entity, entityId);
}

