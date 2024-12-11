#include "parser.h"
#include <fstream>
#include <sstream>



FileInfo Parser::getConfiguration(const std::string& configuration_filename){
    std::ifstream config_stream(configuration_filename);
    std::string line;
    FileInfo config;
    if (config_stream.is_open()) {
        while (std::getline(config_stream, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (iss >> key >> value) {
                value = value.substr(1, value.rfind("\"") - 1);
                if(key == "input_directory:"){
                    config.dirName = value;
                }
                else if (key == "output_file:"){
                    config.outputName = value;
                }
                else if (key == "logging:"){
                    config.logging = false;
                    if(value == "true"){
                        config.logging = true;
                    }

                }
            }
        }
        config_stream.close();
    } else {
        throw std::runtime_error("Unable to open configuration file: " + configuration_filename);
    }
    return config;
}