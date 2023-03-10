/*
** PERSONAL PROJECT, 2021
** TextManager
** File description:
** TextManager.hpp
*/

#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP

#include <unordered_map>
#include "ColorLink/ColorLink.hpp"
#include "Interface/ITextManager.hpp"

class TextManager: public ITextManager
{
    public:
        TextManager();
        TextManager(vector2D pos, vector2D size, color_e color, std::string content, std::string fontPath);
        TextManager(const TextManager &);
        ~TextManager();

        const vector2D &getSize();
        const vector2D &getPosition();
        void setColor(const color_e &);
        void setSize(const vector2D &);
        void setPosition(const vector2D &);
        void setContent(const std::string &);
        void setFont(const std::string &);
        void draw();
        void refresh();

    private:
        vector2D _pos;
        vector2D _size;
        color_e _color;
        std::string _content;
        std::string _fontPath;
        std::shared_ptr<sf::Font> _font;
        std::shared_ptr<sf::Text> _text;
};

#endif