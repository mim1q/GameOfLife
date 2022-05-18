#include "movable_view.h"

#include <iostream>

namespace mimiq {
    
    void MovableView::init(int initial_width, int initial_height) {
        reset(sf::FloatRect(0.0f, 0.0f, (float)initial_width, (float)initial_height));
        m_currentZoomLevel = 3;
    }

    void MovableView::handleEvents(sf::Event &event) {

        if(event.type == sf::Event::MouseMoved)
            m_currentMousePos = {event.mouseMove.x, event.mouseMove.y};

        else if(event.type == sf::Event::Resized) {
            setSize(event.size.width, event.size.height);
            zoom(ZOOM_LEVELS[m_currentZoomLevel]);
        }

        else if(event.type == sf::Event::MouseWheelScrolled) {

            int last_zoom = m_currentZoomLevel;

            if(event.mouseWheelScroll.delta > 0)
                m_currentZoomLevel++;
            else if(event.mouseWheelScroll.delta < 0)
                m_currentZoomLevel--;

            if(m_currentZoomLevel < 0) m_currentZoomLevel = 0;
            else if(m_currentZoomLevel > 5) m_currentZoomLevel = 5;

            zoom(ZOOM_LEVELS[m_currentZoomLevel] / ZOOM_LEVELS[last_zoom]);
        }
    }

    void MovableView::update() {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
            float dx = (float)(m_currentMousePos.x - m_lastMousePos.x) * ZOOM_LEVELS[m_currentZoomLevel];
            float dy = (float)(m_currentMousePos.y - m_lastMousePos.y) * ZOOM_LEVELS[m_currentZoomLevel];

            setCenter(getCenter().x - dx, getCenter().y - dy);
        }

        m_lastMousePos = m_currentMousePos;
    }

} // namespace mimiq
