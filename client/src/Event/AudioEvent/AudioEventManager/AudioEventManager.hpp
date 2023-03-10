/*
** EPITECH PROJECT, 2021
** AudioEventManager
** File description:
** AudioEventManager.hpp
*/

#ifndef AUDIOEVENTMANAGER_HPP
#define AUDIOEVENTMANAGER_HPP

#include "Event/AudioEvent/AudioEventLoad.hpp"
#include "Event/AudioEvent/AudioEventPlay.hpp"
#include "Event/AudioEvent/AudioEventStop.hpp"
#include "Event/AudioEvent/AudioEventPause.hpp"
#include "Event/AudioEvent/AudioEventVolume.hpp"
#include "Event/AudioEvent/AudioEventStopAll.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"
#include <unordered_map>

class AudioEventManager
{
	public:
        AudioEventManager();
        ~AudioEventManager() = default;

        void loadAudio(const AudioEventLoad *e);
        void playAudio(const AudioEventPlay *e);
        void stopAudio(const AudioEventStop *e);
        void pauseAudio(const AudioEventPause *e);
        void stopAudio(const AudioEventStopAll *e);
        void volumeAudio(const AudioEventVolume *e);

    private:
        static void initEvent();

    private:
        std::unordered_map<std::string, std::unique_ptr<IAudioManager>> _list;
};

#endif