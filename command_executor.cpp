#include "command_executor.h"


double CommandExecutor::executeCommand(const std::string& cmd, double value1, double value2, Logger& logger) {
    if (cmd == "add") {
        logger.log("Executing: add " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 + value2));
        return value1 + value2;
    } else if (cmd == "mult") {
        logger.log("Executing: mult " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 * value2));
        return value1 * value2;
    } else if (cmd == "add_sq") {
        logger.log("Executing: add_sq " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 * value1 + value2 * value2));
        return value1 * value1 + value2 * value2;
    } else if (cmd == "sq_add") {
        logger.log("Executing: sq_add " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string((value1 + value2) * (value1 + value2)));
        return (value1 + value2) * (value1 + value2);
    } else if (cmd == "sub") {
        logger.log("Executing: sub " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 - value2));
        return value1 - value2;
    } else if (cmd == "div") {
        if (value2 != 0) {
            logger.log("Executing: div " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 / value2));
            return value1 / value2;
        }
        throw std::invalid_argument("Division by zero");
    }
    else{
        throw std::invalid_argument("Invalid command: " + cmd);
    }
    return 0;
}