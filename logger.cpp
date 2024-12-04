#include <cmath>
#include <exception>
#include "logger.h"

Logger::Logger(std::ostream& os, bool enabled) : output_stream(os), logging_enabled(enabled) {}

void Logger::log(const std::string& message) {
    if (logging_enabled) {
        std::lock_guard<std::mutex> lock(mutex_);
        output_stream << message << std::endl;
    }
}