#include "logger.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
#include <filesystem>
#include <map>

class Parser {
public:

    void runProcess();
private:
    void processFile(const std::string& filename, Logger& logger, const std::string& output_file);
    double executeCommand(const std::string& cmd, double value1, double value2, Logger& logger);
    std::map<std::string, std::string> getConfiguration(const std::string& configuration_filename);
};