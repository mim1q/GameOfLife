#include "gui.h"

namespace mimiq {
    
    Gui::Gui() {
        m_guiView.reset({0.0f, 0.0f, 800.0f, 600.0f});

        m_buttons["open"].init("resources/images/open.png");

        m_buttons["save"].init("resources/images/save.png");
        m_buttons["save"].setPosition({50.0f, 0.0f});
        
        m_buttons["reset"].init("resources/images/reset.png");
        m_buttons["reset"].setPosition({100.0f, 0.0f});

        m_buttons["play"].init("resources/images/play.png");
        m_buttons["play"].setPosition({150.0f, 0.0f});

        m_buttons["pause"].init("resources/images/pause.png");
        m_buttons["pause"].setPosition({150.0f, 0.0f});
        m_buttons["pause"].m_hidden = true;

        m_buttons["slow_down"].init("resources/images/slow_down.png");
        m_buttons["slow_down"].setPosition({200.0f, 0.0f});

        m_buttons["speed_up"].init("resources/images/speed_up.png");
        m_buttons["speed_up"].setPosition({250.0f, 0.0f});

        m_buttons["reset_view"].init("resources/images/reset_view.png");
        m_buttons["reset_view"].setPosition({300.0f, 0.0f});
    }

    void Gui::handleEvents(sf::RenderWindow &window, sf::Event &event) {
        if(event.type == sf::Event::Resized) {
            m_guiView.reset({0.0f, 0.0f, (float)event.size.width, (float)event.size.height});
        }

        for(auto &b : m_buttons) {
            if(!b.second.m_hidden)
                b.second.handleEvents(event);
        }
    }

    bool Gui::switchPausePlay(bool pause) {
        if(pause) {
            m_buttons["pause"].m_hidden = true;
            m_buttons["play"].m_hidden = false;
            m_buttons["pause"].m_mouseOver = false;
            return true;
        } else {
            m_buttons["pause"].m_hidden = false;
            m_buttons["play"].m_hidden = true;
            m_buttons["play"].m_mouseOver = false;
            return false;
        }
    }

    void Gui::draw(sf::RenderWindow &window) {
        auto old_view = window.getView();
        window.setView(m_guiView);

        for(auto &b : m_buttons) {
            if(!b.second.m_hidden)
                window.draw(b.second);
        }
        window.setView(old_view);
    }

    bool Gui::isMouseOver() {
        for(auto &b : m_buttons) {
            if(b.second.m_mouseOver)
                return true;
        }
        return false;
    }
    
    bool Gui::wasButtonPressed(std::string btn_name) {
        auto it = m_buttons.find(btn_name);
        if(it != m_buttons.end())
            return m_buttons[btn_name].wasButtonPressed();
        else throw std::runtime_error("Button Not Found");
    }
} // namespace mimiq
