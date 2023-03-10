/*
** EPITECH PROJECT , 2021
** GameScene
** File description:
** \file GameScene.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "utils/timeDef.hpp"

namespace Scene
{
    class GameScene : public Engine::AbstractScene<GameScene> {
      public:
        GameScene();
        virtual ~GameScene() = default;

        virtual void open();

        void setTimeStart(Time timestamp);
        Time getTimeStart() const;
        void setPlayerNumber(int playerNumber);

      private:
        void initGame();
        void createWaitingScreen();

      private:
        static size_t countown;

      private:
        std::string _audio;
        Time _timestampStart;
        int _playerNumber;
    };
}

#endif // GAMESCENE_HPP
