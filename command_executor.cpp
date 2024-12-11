#include "command_executor.h"
#include <stdexcept>

double CommandExecutor::add(double value1, double value2){
    return value1 + value2;
}

double CommandExecutor::mult(double value1, double value2){
    return value1 * value2;
}

double CommandExecutor::add_sq(double value1, double value2){
    return value1 * value1 + value2 * value2;
}

double CommandExecutor::sq_add(double value1, double value2){
    return (value1 + value2) * (value1 + value2);
}

double CommandExecutor::sub(double value1, double value2){
    return value1 - value2;
}

double CommandExecutor::div(double value1, double value2){
    if (value2 != 0) {
            return value1 / value2;
        }
    throw std::invalid_argument("Division by zero");
}

double CommandExecutor::executeCommand(const std::string& cmd, double value1, double value2) {
    if (cmd == "add") {
        return  add(value1, value2);
    } else if (cmd == "mult") {
        return  mult(value1, value2);
    } else if (cmd == "add_sq") {
        return  add_sq(value1, value2);
    } else if (cmd == "sq_add") {
        return  sq_add(value1, value2);
    } else if (cmd == "sub") {
        return  sub(value1, value2);
    } else if (cmd == "div") {
        return div(value1, value2);
    }
    else{
        throw std::invalid_argument("Invalid command: " + cmd);
    }
}



// logger.log("Executing: mult " + std::to_string(value1) + " " + std::to_string(value2) + " = " + std::to_string(value1 * value2));