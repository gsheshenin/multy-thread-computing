#include "parser.h"
#include <fstream>
#include <sstream>



std::map<std::string, std::string> Parser::getConfiguration(const std::string& configuration_filename){
    std::ifstream config_stream(configuration_filename);
    std::string line;
    std::map<std::string, std::string> config;
    if (config_stream.is_open()) {
        while (std::getline(config_stream, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (iss >> key >> value) {
                value = value.substr(1, value.rfind("\"") - 1);
                config[key] = value;
            }
        }
        config_stream.close();
    } else {
        throw std::runtime_error("Unable to open configuration file: " + configuration_filename);
    }
    return config;
}