#include "command_executor.h"
#include "parser.h"
#include <filesystem>


class FileManager{
public:
    void runProcess();

private:
    void processFile(const std::string& filename, Logger& logger, const std::string& output_file);
};