#pragma once

#include <array>
#include <SFML/Graphics.hpp>

namespace mimiq {
    // Struktura pomocnicza, symbolizująca jedną komórkę automatu
    struct ConwayCell {
        int neighbors = 0;
        bool last_alive = true;
    };

    typedef std::map<std::pair<int, int>, ConwayCell> CellMap;

    // Klasa tworząca i aktualizująca zbiór komórek zgodnie z zasadami "Gry
    // w życie Johna Conwaya.
    class ConwayAutomaton {
    public:
        ConwayAutomaton();

        void reset();
        void draw(sf::RenderWindow &window);
        void handleEvents(sf::RenderWindow &window, sf::Event &event, bool disable_drawing);
        void update();

        void pause();
        void play();

        void speedUp();
        void slowDown();

        void fromFile(char* filepath);
        void toFile(char* filepath);

    private:

        // Rozmiar komórki w pikselach
        const int CELL_SIZE = 10;

        // Tablica przesunięć, pozwalających na ustalenie położenia sąsiadów
        // (wykorzystane w addNeighbors())
        const sf::Vector2i OFFSETS[9] {
            {-1, -1}, { 0, -1}, { 1, -1},
            {-1,  0}, { 0,  0}, { 1,  0},
            {-1,  1}, { 0,  1}, { 1,  1}
        };

        const float SPEEDS[8] {
            1.0f,
            1.0f/2.0f,
            1.0f/5.0f,
            1.0f/10.0f,
            1.0f/20.0f,
            1.0f/30.0f,
            1.0f/60.0f,
            1.0f/240.0f
        };

        int m_currentSpeed = 3;

        bool m_paused = true;

        // Mapa:
        // [{x, y}] : komórka automatu
        CellMap m_cells;

        // Tablica punktów będących reprezentacją graficzną pojedynczej komórki
        sf::VertexArray m_cellRepresentation;

        // Jak wyżej, ale reprezentuje wskaźnik położenia nowej komórki, jeżeli
        // kliknie się myszą
        sf::VertexArray m_indicator;

        // Położenie myszki (w koordynatach mapy komórek)
        sf::Vector2i m_mousePos;

        sf::Clock m_clock;

        // Dodaje wszystkich sąsiadów danej komórki do podanej mapy komórek.
        // Jeżeli sąsiad istnieje, dodaje 1 do jego liczby sąsiadów.
        void addNeighbors(std::map<std::pair<int, int>, ConwayCell> &neighbors, int x, int y);

        void drawCell(sf::RenderWindow &window, int x, int y);

        void calculateCellVertices(sf::VertexArray &verts, int x, int y);
    };

} // namespace mimiq
