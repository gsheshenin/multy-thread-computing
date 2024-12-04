#include "logger.h"

class CommandExecutor{
public:
    static double executeCommand(const std::string& cmd, double value1, double value2, Logger& logger);
};