#include <chrono>
#include <iostream>
#include <iomanip>
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
            auto start = std::chrono::steady_clock::now();
            init_data = load_from_file(init);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            std::cout << "init took " << std::chrono::duration<double,std::milli> (diff).count() << " ms" << std::endl;
        }
        else {
            init_data.push_back({0, 0, 0});
            init_data.push_back({0, 0, 0});
            init_data.push_back({0, 0, 0});
        }

        auto start = std::chrono::steady_clock::now();
        Grid g(init_data);
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << "constructor took " << std::chrono::duration<double,std::milli> (diff).count() << " ms" << std::endl;
          
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

        // Find out necessary padding width -- i.e. max number of digits used.
        std::stringstream counting_stream;
        counting_stream << frames-1;
        auto padding_width = counting_stream.str().size();

        for(int i = 0; i < frames; i++) {
            g.update_grid();

            if(vm.count("out")) {
                // Pad number
                std::stringstream out_string;
                out_string << std::setw(padding_width) << std::setfill('0') << std::to_string(i);

                auto start_fw = std::chrono::steady_clock::now();
                g.write_to_file(out + out_string.str());
                auto end_fw = std::chrono::steady_clock::now();
                auto diff_fw = end_fw - start_fw;
                std::cout << "file write took " << std::chrono::duration<double,std::milli> (diff_fw).count() << " ms" << std::endl;
            }
        }
      
    } catch(std::exception& e) {
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        return 2;
    }
    return 0;
}
