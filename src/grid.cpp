#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <omp.h>

#include <grid.hpp>

Grid::Grid(int rows, int cols) : GridData(rows, std::vector<Cell>(cols)) {
}

Grid::Grid(std::vector< std::vector<bool> > init) : GridData(init.size(), std::vector<Cell>( init[0].size() )) {
    int rows = init.size();
    int cols = init[0].size();

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            GridData[r][c].set_cell_state(init[r][c]);
        }
    }
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

std::vector< std::vector<bool> > Grid::get_grid_data() {
    int rows = GridData.size();
    int cols = GridData[0].size();

    std::vector< std::vector<bool> > bool_matrix(rows, std::vector<bool>(cols));

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            bool_matrix[r][c] = GridData[r][c].is_alive();
        }
    }

    return bool_matrix;
}

std::array<bool,8> Grid::get_neighbours_state(int row, int col) {
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

    std::array<bool,8> neighbours;

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

int Grid::get_num_neighbours(int row, int col) {
    auto neighbours = get_neighbours_state(row, col);
    auto neighbours_alive = std::count(neighbours.begin(), neighbours.end(), true);
    return neighbours_alive;

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

    #pragma omp parallel shared(next_grid)
    {
        #pragma omp for
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                auto num_neighbours = get_num_neighbours(r, c);
                auto new_state = GridData[r][c].update_cell(num_neighbours);
                next_grid[r][c].set_cell_state(new_state);
            }
        }
    }

    GridData = next_grid;
}

void Grid::write_to_file(std::string filename) {
    std::ofstream outfile;
    outfile.open(filename);
    std::ostream_iterator<bool> out_it(outfile, " ");

    auto bool_matrix = get_grid_data();

    for(int i = 0; i < bool_matrix.size(); i++) {
        copy(bool_matrix.at(i).begin(), bool_matrix.at(i).end(), out_it);
        outfile << std::endl;
    }
    outfile.close();
}
