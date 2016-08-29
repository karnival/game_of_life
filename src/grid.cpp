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

std::vector<bool> Grid::get_neighbours_state(int row, int col) {
    auto rows = num_rows();
    auto cols = num_cols();

    auto neighbours = std::vector<bool>(8, 0); 
    
    if(row > 0 && row < rows-1 && col > 0 && col < cols-1) {
        neighbours[0] = GridData[row-1][col-1].is_alive();
        neighbours[1] = GridData[row  ][col-1].is_alive();
        neighbours[2] = GridData[row+1][col-1].is_alive();

        neighbours[3] = GridData[row-1][col  ].is_alive();
        neighbours[4] = GridData[row+1][col  ].is_alive();

        neighbours[5] = GridData[row-1][col+1].is_alive();
        neighbours[6] = GridData[row  ][col+1].is_alive();
        neighbours[7] = GridData[row+1][col+1].is_alive();
    }
}

void Grid::update_grid() {
    auto next_grid = GridData;

    auto rows = num_rows();
    auto cols = num_cols();

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            auto neighbours = Grid::get_neighbours_state(r, c);
            auto new_state = GridData[r][c].update_cell(neighbours);
            if(new_state) {
                next_grid[r][c].live();
            }
            else {
                next_grid[r][c].die();
            }
        }
    }

    GridData = next_grid;
}
