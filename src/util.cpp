#include <util.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector< std::vector<bool> > load_from_file(std::string filename) {
    std::vector< std::vector<bool> > data;

    std::ifstream file(filename);

    std::string curr_line;

    while(std::getline(file, curr_line)) {
        std::vector<bool> line_data;
        std::stringstream  line_stream(curr_line);

        bool value;
        while(line_stream >> value)
        {
            line_data.push_back(value);
        }
        data.push_back(line_data);
    }

    return data;
}

