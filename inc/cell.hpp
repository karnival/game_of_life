#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
    public:
        Cell();
        Cell(bool alive);

        void die();
        void live();
        bool is_alive();
        bool update_cell(std::vector<bool> neighbours);

    private:
        bool m_alive;
};

#endif
