#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "movable_view.h"
#include "conway_automaton.h"
#include "gui/gui.h"

namespace mimiq {
    
    class App {
    public:
        App(std::string window_title, int window_width, int window_height);

        // Główna pętla aplikacji
        void run();

    private:
        void handleEvents(sf::Event &event);

        // Główne okno aplikacji
        sf::RenderWindow m_window;

        // Widok aplikacji (z opcją przemieszczania i skalowania widoku myszą)
        MovableView m_view;

        // Automat komórkowy ("Gra w Życie")
        ConwayAutomaton m_automaton;

        // Interfejs graficzny
        Gui m_gui;
    };

} // namespace mimiq