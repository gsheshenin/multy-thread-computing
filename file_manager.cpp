#include "file_manager.h"
#include <vector>
#include <thread>
#include <fstream>
#include <map>

void FileManager::processFile(const std::string& filename, Logger& logger, const std::string& output_file) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        std::ofstream outfile(output_file, std::ios::app);
        if (outfile.is_open()) {
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string cmd;
                double value1, value2;
                if (iss >> cmd >> value1 >> value2) {
                    outfile << value1 << " " << cmd << " " << value2 << " = " << CommandExecutor::executeCommand(cmd, value1, value2, logger) << std::endl;
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

void FileManager::runProcess(){
    std::map<std::string, std::string> configuration = Parser::getConfiguration("config.txt");

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