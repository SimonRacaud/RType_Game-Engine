/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include "BaseComponent/BaseComponent.hpp"

namespace Engine {
	class Hitbox : public Engine::BaseComponent<Hitbox> {
		public:
			Hitbox(float x, float y, const std::function<void(Engine::Entity, Engine::Entity)> factory) 
				: x(x), y(y), _eventFactory(factory) {}
			virtual ~Hitbox() = default;

			float x{0};
			float y{0};
			std::function<void(Engine::Entity, Engine::Entity)> _eventFactory;
	};
}

#endif /* !HITBOX_HPP_ */
