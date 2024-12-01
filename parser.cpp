#include "parser.h"


double Parser::executeCommand(const std::string& cmd, double value1, double value2, Logger& logger) {
    if (cmd == "add") {
        logger.log("Executing: add " + std::to_string(value1) + " " + std::to_string(value2));
        return value1 + value2;
    } else if (cmd == "mult") {
        logger.log("Executing: mult " + std::to_string(value1) + " " + std::to_string(value2));
        return value1 * value2;
    } else if (cmd == "add_sq") {
        logger.log("Executing: add_sq " + std::to_string(value1) + " " + std::to_string(value2));
        return value1 * value1 + value2 * value2;
    } else if (cmd == "sq_add") {
        logger.log("Executing: sq_add " + std::to_string(value1) + " " + std::to_string(value2));
        return (value1 + value2) * (value1 + value2);
    } else if (cmd == "sub") {
        logger.log("Executing: sub " + std::to_string(value1) + " " + std::to_string(value2));
        return value1 - value2;
    } else if (cmd == "div") {
        if (value2 != 0) {
            logger.log("Executing: div " + std::to_string(value1) + " " + std::to_string(value2));
            return value1 / value2;
        }
        throw std::invalid_argument("Division by zero");
    }
    else{
        throw std::invalid_argument("Invalid command: " + cmd);
    }
    return 0;
}



void Parser::processFile(const std::string& filename, Logger& logger, const std::string& output_file) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        std::ofstream outfile(output_file);
        if (outfile.is_open()) {
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string cmd;
                double value1, value2;
                if (iss >> cmd >> value1 >> value2) {
                    outfile << value1 << " " << cmd << " " << value2 << " = " << executeCommand(cmd, value1, value2, logger) << std::endl;
                } else {
                    logger.log("Error processing line: " + line);
                }
            }
            outfile.close();
        }
        else {
        logger.log("Unable to open output file: " + output_file);
        }
        file.close();
    } else {
        logger.log("Unable to open file: " + filename);
    }
}

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

void Parser::runProcess(){
    std::map<std::string, std::string> configuration = getConfiguration("config.txt");

    bool logging = false; // logging
    if (configuration["logging:"] == "true") {
        logging = true;
    }
    Logger logger(std::cout, logging);

    std::string input_directory = configuration["input_directory:"]; // directory name
    std::string output_file = configuration["output_file:"]; // name of output file

    std::vector<std::thread> threads;
    for (const auto& entry : std::filesystem::directory_iterator(input_directory)) {
        if (entry.path().extension() == ".dat") {
            threads.emplace_back(&processFile, this,  entry.path().string(), std::ref(logger), std::ref(output_file));
        }
    }
    for (auto& thread : threads) {
        thread.join();
    }
}