#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
    Logger(std::ostream& os, bool enabled);
    void log(const std::string& message);

private:
    std::ostream& output_stream;
    bool logging_enabled;
    std::mutex mutex_;
};


