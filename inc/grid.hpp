#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

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

        bool* get_neighbours_state(int row, int col);
        int get_num_neighbours(int row, int col);

        void write_to_file(std::string filename);
        std::vector< std::vector<bool> > get_grid_data();

    private:
        std::vector< std::vector<Cell> > GridData;
};

#endif
