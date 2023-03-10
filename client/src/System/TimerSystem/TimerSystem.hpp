/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerSystem
*/

#ifndef TIMERSYSTEM_HPP_
#define TIMERSYSTEM_HPP_

#include "global.hpp"
#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Components/Timer.hpp"
#include "EntityManager/EntityManager.hpp"
#include <list>

namespace Engine {
	class TimerSystem : public AbstractSystem<TimerSystem> {
		public:
			TimerSystem();
			~TimerSystem();

			void run(const vector<Entity> &entities) override;
	};
}

#endif /* !TIMERSYSTEM_HPP_ */
