#pragma once

#include <SFML/Graphics.hpp>

namespace mimiq
{
    
    class MovableView : public sf::View {
    public:
        void init(int initial_width, int initial_height);
        void handleEvents(sf::Event &event);
        void update();

    private:
        const float ZOOM_LEVELS[6] = {
            10.0, 5.0, 2.0, 1.0, 0.5, 0.2
        };
        int m_currentZoomLevel = 3;
    
        sf::Vector2i m_lastMousePos = {0, 0};
        sf::Vector2i m_currentMousePos = {0, 0};
    };


} // namespace mimiq
