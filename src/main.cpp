#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include <grid.hpp>
#include <util.hpp>

int main(int argc, char** argv) {
    try {
        std::string init;
        std::string out;
        int frames;

        namespace opts = boost::program_options;
        opts::options_description desc("Options");
        desc.add_options()
                ("help", "Print help message")
                ("init", opts::value<std::string> (&init), "Initial state.")
                ("frames", opts::value<int> (&frames), "Frames.")
                ("out", opts::value<std::string> (&out), "Output filename.")
        ;

        opts::positional_options_description positionalOptions;

        opts::variables_map vm;

        try {
            opts::store(opts::command_line_parser(argc, argv).options(desc)
                            .positional(positionalOptions).run(),
                        vm);
            if(vm.count("help")) {
                std::cout << "Program description." << std::endl;
                return 0;
            }

            opts::notify(vm);
        } catch(opts::required_option& e) {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 

            return 1;
        } catch(boost::program_options::error& e) { 
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;  

            return 1;                                  
        }                                                                

        std::vector< std::vector<bool> > init_data;
        if(vm.count("init")) {
            std::cout << "init was " << vm["init"].as<std::string>() << std::endl;
            init_data = load_from_file(init);
        }
        else {
            init_data.push_back({0, 0, 0});
            init_data.push_back({0, 0, 0});
            init_data.push_back({0, 0, 0});
        }

        Grid g(init_data);
          
        if(vm.count("out")) {
            std::cout << "out was " << vm["out"].as<std::string>() << std::endl;
        }
        else {
            std::cout << "Not saving output because --out was not specified." << std::endl;
        }

        if(vm.count("frames")) {
            std::cout << "number of frames was " << frames << std::endl;
        } else {
            std::cout << "defaulting to 10 frames" << std::endl;
            frames = 10;
        }

        for(int i = 0; i < frames; i++) {
            g.update_grid();

            if(vm.count("out")) {
                g.write_to_file(out + std::to_string(i));
            }
        }
      
    } catch(std::exception& e) {
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        return 2;
    }
    return 0;
}
