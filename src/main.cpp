#include <iostream>
#include <boost/program_options.hpp>

#include <grid.hpp>

int main(int argc, char** argv) {
    try {
        std::string init;
        std::string out;

        namespace opts = boost::program_options;
        opts::options_description desc("Options");
        desc.add_options()
                ("help", "Print help message")
                ("init", opts::value<std::string> (&init), "Initial state.")
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

        if(vm.count("init")) {
            std::cout << "init was " << vm["init"].as<std::string>() << std::endl;
        }
          
        if(vm.count("out")) {
            std::cout << "out was " << vm["out"].as<std::string>() << std::endl;
        }
      
        if(vm.count("out")) {
        }

    } catch(std::exception& e) {
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        return 2;
    }
    return 0;
}
