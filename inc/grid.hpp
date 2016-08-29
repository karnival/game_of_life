#ifndef GRID_H
#define GRID_H

#include <vector>

#include <cell.hpp>

class Grid {
    public:
        Grid(int rows, int cols);
        int num_rows();
        int num_cols();

    private:
        std::vector< std::vector<Cell> > GridData;
};

#endif
