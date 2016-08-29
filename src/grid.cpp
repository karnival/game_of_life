#include <vector>
#include <exception>
#include <iostream>

#include <grid.hpp>

Grid::Grid(int rows, int cols) : GridData(rows, std::vector<Cell>(cols)) {
}

bool Grid::operator==(const Grid& other) {
    // Check equality element by element.
    bool equal = true;
    for(int r = 0; r < num_rows(); r++) {
        for(int c = 0; c < num_cols(); c++) {
             equal = equal && (GridData[r][c] == other.GridData[r][c]);
        }
    }

    return equal;
}

bool Grid::operator!=(const Grid& other) {
    return !(*this == other);
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

    // Compute the row offsets and col offsets -- handles edge/corner cases.
    int row_dec;
    int row_inc; 
    if(row > 0 && row < rows-1) {
         row_dec = row-1;
         row_inc = row+1;
    }
    else if(row == 0) {
         row_dec = rows-1;
         row_inc = row+1;
    }
    else if(row == rows-1) {
         row_dec = row-1;
         row_inc = 0;
    }
    else {
        std::cerr << "Bad row coordinate in neighbour lookup." << std::endl;
        throw std::exception();
    }

    int col_dec;
    int col_inc;
    if(col > 0 && col < cols-1) {
         col_dec = col-1;
         col_inc = col+1;
    }
    else if(col == 0) {
         col_dec = cols-1;
         col_inc = col+1;
    }
    else if(col == cols-1) {
         col_dec = col-1;
         col_inc = 0;
    }
    else {
        std::cerr << "Bad col coordinate in neighbour lookup." << std::endl;
        throw std::exception();
    }

    auto neighbours = std::vector<bool>(8, 0); 
    neighbours[0] = GridData[row_dec][col_dec].is_alive();
    neighbours[1] = GridData[row  ][col_dec].is_alive();
    neighbours[2] = GridData[row_inc][col_dec].is_alive();

    neighbours[3] = GridData[row_dec][col].is_alive();
    neighbours[4] = GridData[row_inc][col].is_alive();

    neighbours[5] = GridData[row_dec][col_inc].is_alive();
    neighbours[6] = GridData[row  ][col_inc].is_alive();
    neighbours[7] = GridData[row_inc][col_inc].is_alive();


    return neighbours;
}

void Grid::set_cell_state(int row, int col, bool state) {
    GridData[row][col].set_cell_state(state);
}

bool Grid::get_cell_state(int row, int col) {
    return GridData[row][col].is_alive();
}

void Grid::update_grid() {
    auto next_grid = GridData;

    auto rows = num_rows();
    auto cols = num_cols();

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            auto neighbours = Grid::get_neighbours_state(r, c);
            auto new_state = GridData[r][c].update_cell(neighbours);
            next_grid[r][c].set_cell_state(new_state);
        }
    }

    GridData = next_grid;
}
