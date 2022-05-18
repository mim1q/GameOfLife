#include "app.h"

#include "gui/file_dialog/tinyfiledialogs.h"

namespace mimiq {
    
    App::App(std::string window_title, int window_width, int window_height) {
        m_window.create(sf::VideoMode(window_width, window_height), window_title, sf::Style::Default);
        m_view.init(800, 600);
        m_window.setFramerateLimit(240);
    }

    void App::run() {

        // Filtr rozszerzeń plików (w tym przypadku użyłem rozszerzenia .gol - 
        // od "Game of Life", które jest zwykłym plikiem tekstowym zawierającym
        // informacje o żywych komórkach automatu)
        char const *filter[1] = {"*.gol"};

        // Kursory (zwykły i "z palcem")
        sf::Cursor normal_cursor;
        sf::Cursor hover_cursor;

        normal_cursor.loadFromSystem(sf::Cursor::Arrow);
        hover_cursor.loadFromSystem(sf::Cursor::Hand);

        m_window.setMouseCursor(normal_cursor);

        while(m_window.isOpen()) {

            sf::Event event;
            while(m_window.pollEvent(event)) {
                this->handleEvents(event);

                m_view.handleEvents(event);
                m_gui.handleEvents(m_window, event);
                if(m_gui.isMouseOver()) {
                    m_automaton.handleEvents(m_window, event, true);
                    m_window.setMouseCursor(hover_cursor);
                }
                else {
                    m_automaton.handleEvents(m_window, event, false);
                    m_window.setMouseCursor(normal_cursor);
                }
            }

            // Obsługa przycisków

            if(m_gui.wasButtonPressed("open")) {
                char* filepath = tinyfd_openFileDialog("Otwórz projekt", "", 1, filter, "Projekty aplikacji Game of Life", 0);
                m_gui.switchPausePlay(true);
                m_automaton.fromFile(filepath);
            }

            else if(m_gui.wasButtonPressed("save")) {
                char* filepath = tinyfd_saveFileDialog("Zapisz projekt", "", 1, filter, "Projekty aplikacji Game of Life");
                m_automaton.toFile(filepath);
            }

            else if(m_gui.wasButtonPressed("pause")) {
                m_automaton.pause();
                m_gui.switchPausePlay(true);
            }

            else if(m_gui.wasButtonPressed("play")) {
                m_automaton.play();
                m_gui.switchPausePlay(false);
            }

            else if(m_gui.wasButtonPressed("reset")) {
                m_automaton.pause();
                m_view.init(m_window.getSize().x, m_window.getSize().y);
                m_gui.switchPausePlay(true);
                m_automaton.reset();
            }

            else if(m_gui.wasButtonPressed("speed_up")) {
                m_automaton.speedUp();
            }

            else if(m_gui.wasButtonPressed("slow_down")) {
                m_automaton.slowDown();
            }

            else if(m_gui.wasButtonPressed("reset_view")) {
                m_view.init(m_window.getSize().x, m_window.getSize().y);
            }
            
            // Update, draw

            m_view.update();
            m_window.setView(m_view);

            m_window.clear(sf::Color(25, 25, 25));
            m_automaton.draw(m_window);
            m_automaton.update();
            m_gui.draw(m_window);
            m_window.display();
        }
    }

    void App::handleEvents(sf::Event &event) {
        if(event.type == sf::Event::Closed)
            this->m_window.close();
        if(event.type == sf::Event::Resized) {
            if(event.size.width < 800)
                m_window.setSize({800, m_window.getSize().y});
            if(event.size.height < 600)
                m_window.setSize({m_window.getSize().x, 600});
        }
    }

} // namespace mimiq
