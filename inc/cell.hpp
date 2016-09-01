#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
    public:
        Cell();
        Cell(bool alive);

        bool operator==(const Cell& other);

        void die();
        void live();
        void set_cell_state(bool state);
        bool is_alive();
        bool update_cell(int neighbours_alive);

    private:
        bool m_alive;
};

#endif
