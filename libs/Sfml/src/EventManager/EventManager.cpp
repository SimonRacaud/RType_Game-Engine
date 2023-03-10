/*
** PERSONAL PROJECT, 2021
** EventManager
** File description:
** EventManager.cpp
*/

#include <algorithm>
#include "EventManager/EventManager.hpp"
#include "WindowManager/WindowManager.hpp"

EventManager::EventManager(): _mouse(), _keyStackPressed()
{
}

EventManager::EventManager(const EventManager &src): _mouse(src._mouse), _keyStackPressed(src._keyStackPressed)
{
}

EventManager::~EventManager()
{
    this->_keyStackPressed.clear();
    this->_keyStackReleased.clear();
}

void EventManager::refresh()
{
    this->_prevKeyStackPressed = this->_keyStackPressed;
    this->_prevKeyStackReleased = this->_keyStackReleased;
    this->_keyStackPressed.clear();
    this->_keyStackReleased.clear();
    this->fetchEvent();
}

bool EventManager::isKeyPressed(const IEventManager::keyEvent_e &key) const
{
    if (!this->isValideEnum(key))
        throw std::invalid_argument("Invalid key type");

    auto pos = std::find(this->_keyStackPressed.begin(), this->_keyStackPressed.end(), key);

    return pos != this->_keyStackPressed.end();
}

bool EventManager::isKeyReleased(const keyEvent_e &key) const
{
    if (!this->isValideEnum(key))
        throw std::invalid_argument("Invalid key type");

    auto pos = std::find(this->_keyStackReleased.begin(), this->_keyStackReleased.end(), key);

    return pos != this->_keyStackReleased.end();
}

bool EventManager::isStateChange(const keyEvent_e &key) const
{
    bool pressed = this->isKeyPressed(key);
    bool released = this->isKeyReleased(key);
    bool status = false;

    if (pressed) {
        auto pos = std::find(this->_prevKeyStackReleased.begin(), this->_prevKeyStackReleased.end(), key);

        status = pos != this->_prevKeyStackReleased.end();
    } else if (released) {
        auto pos = std::find(this->_prevKeyStackPressed.begin(), this->_prevKeyStackPressed.end(), key);

        status = pos != this->_prevKeyStackPressed.end();
    }
    return status;
}

vector2D EventManager::getMousePos() const
{
    return this->_mouse;
}

bool EventManager::mouseIsOn(const surface &selected) const
{
    bool x = this->_mouse.x > selected.pos.x && this->_mouse.x < selected.pos.x + selected.size.x;
    bool y = this->_mouse.y > selected.pos.y && this->_mouse.y < selected.pos.y + selected.size.y;

    return x && y;
}

bool EventManager::mouseIsOnClick(const surface &selected, const IEventManager::keyEvent_e &key) const
{
    bool click = this->isKeyPressed(key);
    bool on = this->mouseIsOn(selected);

    return on && click;
}

bool EventManager::isValideEnum(const IEventManager::keyEvent_e &key) const
{
    bool active = key != IEventManager::keyEvent_e::MAX_VALUE && key != IEventManager::keyEvent_e::MOUSE_EVENT_GAME && key != IEventManager::keyEvent_e::KEY_EVENT_GAME;
    bool invalid = key < static_cast<IEventManager::keyEvent_e>(0) || key >= IEventManager::keyEvent_e::MAX_VALUE;

    return active && !invalid;
}

void EventManager::fetchEvent()
{
    sf::Event event;
    
    while (WindowManager::_window->pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Event::Closed: WindowManager::_window->close(); break;
            case sf::Event::MouseMoved: this->mouseFetch(event); break;
            case sf::Event::EventType::KeyPressed: this->keyboardPressedFetch(event); break;
            case sf::Event::EventType::KeyReleased: this->keyboardReleasedFetch(event); break;
            case sf::Event::EventType::MouseButtonPressed: this->mouseKeyFetch(event); break;
            default: break;
        }
        if (event.type == sf::Event::Event::Closed)
            break;
    }
}

void EventManager::mouseFetch(const sf::Event &event)
{
    this->_mouse = vector2D(event.mouseMove.x, event.mouseMove.y);
}

void EventManager::mouseKeyFetch(const sf::Event &event)
{
    try {
        this->_keyStackPressed.push_back(this->_mouseLink.at(event.mouseButton.button));
    } catch(...) {
    }
}

void EventManager::keyboardPressedFetch(const sf::Event &event)
{
    try {
        this->_keyStackPressed.push_back(this->_keyLink.at(event.key.code));
    } catch(...) {
    }
}

void EventManager::keyboardReleasedFetch(const sf::Event &event)
{
    try {
        this->_keyStackReleased.push_back(this->_keyLink.at(event.key.code));
    } catch(...) {
    }
}