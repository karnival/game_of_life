#ifndef CELL_H
#define CELL_H

class Cell {
    public:
        Cell();
        Cell(bool alive);

        void die();
        void live();
        bool is_alive();

    private:
        bool m_alive;
};

#endif
