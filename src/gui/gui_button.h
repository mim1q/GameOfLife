#pragma once

#include <SFML/Graphics.hpp>

namespace mimiq {

    class GuiButton : public sf::RectangleShape {
    public:
        GuiButton();
        void init(std::string icon_filename);

    protected:
        bool wasButtonPressed();
        void handleEvents(sf::Event &event);

        bool m_mouseOver = false;
        bool m_hidden = false;

    private:
        const sf::Color NORMAL_COLOR = sf::Color(180, 180, 180, 255);
        const sf::Color HOVER_COLOR = sf::Color(255, 255, 255, 255);

        bool isMouseOver(sf::Vector2i mousepos, sf::FloatRect bounds);

        sf::Texture *m_buttonIconTexture;
        sf::Sprite m_buttonIcon;
        
        bool m_pressed = false;

    friend class Gui;
    };
} // namespace mimiq
