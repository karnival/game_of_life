#ifndef GRID_H
#define GRID_H

#include <vector>

#include <cell.hpp>

class Grid {
    public:
        Grid(int rows, int cols);
        int num_rows();
        int num_cols();
        void update_grid();

        std::vector<bool> get_neighbours_state(int row, int col);

    private:
        std::vector< std::vector<Cell> > GridData;
};

#endif
