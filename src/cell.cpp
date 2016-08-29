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

bool Cell::is_alive() {
    return m_alive;
}
