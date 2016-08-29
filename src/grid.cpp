#include <vector>

#include <grid.hpp>

Grid::Grid(int rows, int cols) : GridData(rows, std::vector<Cell>(cols)) {
}

int Grid::num_rows() {
    return GridData.size();
}

int Grid::num_cols() {
    return GridData[0].size();
}
