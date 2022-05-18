#include "conway_automaton.h"
#include "util/hsv_to_rgb.h"
#include <fstream>

namespace mimiq {
    ConwayAutomaton::ConwayAutomaton() {

        // Zainicjuj graficzną reprezentację komórek
        m_cellRepresentation.resize(4);
        m_indicator.resize(4);
        m_cellRepresentation.setPrimitiveType(sf::Quads);
        m_indicator.setPrimitiveType(sf::Quads);

        for(int i = 0; i < 4; i++) {
            m_cellRepresentation[i].color = sf::Color::White;
            m_indicator[i].color = sf::Color(255,255,255,127);
        }
    }

    void ConwayAutomaton::update() {

        if(m_clock.getElapsedTime().asSeconds() > SPEEDS[m_currentSpeed]) {
            m_clock.restart();
            if(m_paused) return;
            
            // Mapa w następnym kroku
            CellMap new_cells;

            // Utwórz mapę wszystkich sąsiadów obecnych komórek
            for(auto c : m_cells) {
                addNeighbors(new_cells, c.first.first, c.first.second);
            }

            m_cells.clear();

            // Warunkowo przenieś komórki do obecnej mapy, jeżeli:
            // komórka ma 3 sąsiadów
            // lub
            // komórka była żywa w poprzednim kroku i ma 2 sąsiadów
            for(auto c : new_cells) {
                if(c.second.neighbors == 3
                ||(c.second.last_alive && c.second.neighbors == 2)) {
                    m_cells[c.first] = c.second;
                    m_cells[c.first].last_alive = true;
                }
            }
        }
    }

    void ConwayAutomaton::reset() {
        m_cells.clear();
    }

    void ConwayAutomaton::pause() {
        m_paused = true;
    }
    
    void ConwayAutomaton::play() {
        m_paused = false;
    }

    void ConwayAutomaton::addNeighbors(std::map<std::pair<int, int>, ConwayCell> &neighbors, int x, int y) {
        for(int i = 0; i < 9; i++) {
            int new_x = OFFSETS[i].x + x;
            int new_y = OFFSETS[i].y + y;

            // Sprawdź, czy komórka już istnieje
            auto it = neighbors.find({new_x, new_y});

            // Jeżeli istnieje:
            if(it != neighbors.end()) {
                if(i != 4) // (OFFSET[4] == {0, 0})
                    it->second.neighbors++;
                else
                    it->second.last_alive = true;
            } else {
                if(i != 4) // (OFFSET[4] == {0, 0})
                    neighbors[{new_x, new_y}] = {1, false};
                else
                    neighbors[{new_x, new_y}] = {0, true};
            }
        }
    }

    void ConwayAutomaton::draw(sf::RenderWindow &window) {

        calculateCellVertices(m_indicator, m_mousePos.x, m_mousePos.y);
        window.draw(m_indicator);

        for(auto c : m_cells) {
            this->drawCell(window, c.first.first, c.first.second);
        }
    }

    void ConwayAutomaton::calculateCellVertices(sf::VertexArray &verts, int x, int y) {

        verts[0].position = {(float)(x * CELL_SIZE),        (float)(y * CELL_SIZE)};
        verts[1].position = {(float)((x + 1) * CELL_SIZE),  (float)(y * CELL_SIZE)};
        verts[2].position = {(float)((x + 1) * CELL_SIZE),  (float)((y + 1) * CELL_SIZE)};
        verts[3].position = {(float)(x * CELL_SIZE),        (float)((y + 1) * CELL_SIZE)};
    }

    void ConwayAutomaton::drawCell(sf::RenderWindow &window, int x, int y) {
        
        // Oblicz pozycje wierzchołków komórki
        calculateCellVertices(m_cellRepresentation, x, y);

        sf::Color color = util::HSVtoRGB(abs(x+y) * 10, 0.75, 1.0);

        for(int i = 0; i < 4; i++) {
            m_cellRepresentation[i].color = color;
        }

        window.draw(m_cellRepresentation);
    }

    void ConwayAutomaton::handleEvents(sf::RenderWindow &window, sf::Event &event, bool disable_drawing) {

        sf::Vector2i mouse_global = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world = window.mapPixelToCoords(mouse_global);
        sf::Vector2<bool> negative = {mouse_world.x < 0, mouse_world.y < 0};
        
        if(!disable_drawing 
         && mouse_global.x >= 0
         && mouse_global.x < window.getSize().x
         && mouse_global.y >= 0
         && mouse_global.y < window.getSize().y
        ) {
            // Dodawanie nowych komórek
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_cells[{(int)(mouse_world.x / 10 - negative.x), (int)(mouse_world.y / 10 - negative.y)}] = {0, true};
            }
            // Usuwanie komórek
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                m_cells.erase({(int)(mouse_world.x / 10 - negative.x), (int)(mouse_world.y / 10 - negative.y)});
            }
        }

        if(event.type == sf::Event::MouseMoved) {
            m_mousePos = {(int)(mouse_world.x / 10 - negative.x), (int)(mouse_world.y / 10 - negative.y)};
        }
    }

    void ConwayAutomaton::speedUp() {
        m_currentSpeed++;
        if(m_currentSpeed > 7)
            m_currentSpeed = 7;
    }

    void ConwayAutomaton::slowDown() {
        m_currentSpeed--;
        if(m_currentSpeed < 0)
            m_currentSpeed = 0;
    }

    void ConwayAutomaton::fromFile(char* filepath) {
        std::ifstream fin;
        fin.open(filepath);
        if(fin.is_open()) {
            reset();
            pause();

            int x, y;
            while(fin >> x >> y) {
                m_cells[{x, y}] = {0, true};
            }

            fin.close();
        }
    }

    void ConwayAutomaton::toFile(char* filepath) {
        std::ofstream fout;
        fout.open(filepath);
        if(fout.is_open()) {

            for(auto c : m_cells) {
                fout << c.first.first << " " << c.first.second << std::endl;
            }
            fout.close();
        }
    }

} // namespace mimiq
