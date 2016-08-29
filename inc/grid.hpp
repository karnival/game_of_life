#ifndef GRID_H
#define GRID_H

#include <vector>

#include <cell.hpp>

class Grid {
    public:
        Grid(int rows, int cols);
        Grid(std::vector< std::vector<bool> > init);
        bool operator==(const Grid& other);
        bool operator!=(const Grid& other);

        int num_rows();
        int num_cols();
        void set_cell_state(int row, int col, bool state);
        bool get_cell_state(int row, int col);
        void update_grid();

        std::vector<bool> get_neighbours_state(int row, int col);

    private:
        std::vector< std::vector<Cell> > GridData;
};

#endif
