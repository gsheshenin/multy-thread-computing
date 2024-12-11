#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
    Logger(std::ostream& os): output_stream(os) {};

    template<typename T>
    Logger& operator<<(const T& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        output_stream << message;
        return *this;
    }

    Logger& operator<<(std::ostream& (*manip)(std::ostream&)) {
        output_stream << manip;
        return *this;
    }
private:
    std::ostream& output_stream;
    std::mutex mutex_;
};


