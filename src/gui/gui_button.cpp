#include "gui_button.h"
#include <iostream>

namespace mimiq {

    GuiButton::GuiButton() {
        setSize({50.0f, 50.0f});
    }

    void GuiButton::init(std::string icon_filename) {
        m_buttonIconTexture = new sf::Texture();
        m_buttonIconTexture->loadFromFile(icon_filename);
        this->setTexture(m_buttonIconTexture);
    }

    void GuiButton::handleEvents(sf::Event &event) {
        if(event.type == sf::Event::MouseMoved) {
            if(isMouseOver({event.mouseMove.x, event.mouseMove.y}, getGlobalBounds())) {
                setFillColor(HOVER_COLOR);
            }
            else {
                setFillColor(NORMAL_COLOR);
            }
        }
        if(event.type == sf::Event::MouseButtonReleased) {
            if(m_mouseOver) {
                m_pressed = true;
            }
        }
    }

    bool GuiButton::wasButtonPressed() {
        if(m_pressed) {
            m_pressed = false;
            return true;
        } else return false;
    }

    bool GuiButton::isMouseOver(sf::Vector2i mousepos, sf::FloatRect bounds) {
        m_mouseOver
        = (mousepos.x >= bounds.left 
        && mousepos.x <= bounds.left + bounds.width
        && mousepos.y >= bounds.top
        && mousepos.y <= bounds.top + bounds.height);
        return m_mouseOver;
    }
} // namespace mimiq
