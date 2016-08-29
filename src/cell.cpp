#include <vector>

#include <cell.hpp>

Cell::Cell() : m_alive(false) {
}

Cell::Cell(bool alive) : m_alive(alive) {
}

void Cell::die() {
    m_alive = false;
}

void Cell::live() {
    m_alive = true;
}

void Cell::set_cell_state(bool state) {
    if(state) {
        live();
    }
    else {
        die();
    }
}

bool Cell::is_alive() {
    return m_alive;
}

bool Cell::update_cell(std::vector<bool> neighbours) {
    auto neighbours_alive = std::count(neighbours.begin(), neighbours.end(), true);

    if(m_alive){
        if(neighbours_alive < 2) { // underpopulation
            return false;
        }
        else if(neighbours_alive == 2 || neighbours_alive == 3) { // healthy population
            return true;
        }
        else if(neighbours_alive > 3) { // overpopulation
            return false;
        }
    }
    else if(!m_alive) {
        if(neighbours_alive == 3) { // healthy population
            return true;
        }
        else { // unhealthy population
            return false;
        }
    }
}
