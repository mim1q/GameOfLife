#pragma once

#include <SFML/Graphics.hpp>
#include "gui_button.h"

namespace mimiq {

    class Gui {
    public:
        Gui();

        bool isMouseOver();

        void handleEvents(sf::RenderWindow &window, sf::Event &event);

        void draw(sf::RenderWindow &window);

        // Zmienia przycisk play na pause i na odwrót po ich kliknięciu
        bool switchPausePlay(bool pause);

        bool wasButtonPressed(std::string btn_name);

    private:
        std::map<std::string, GuiButton> m_buttons;
        sf::View m_guiView;

    };
} // namespace mimiq
