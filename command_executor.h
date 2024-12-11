#include <string>
#include <mutex>

class CommandExecutor {
public:
    static double executeCommand(const std::string& cmd, double value1, double value2);

private:
    static double add(double value1, double value2);
    static double mult(double value1, double value2);
    static double add_sq(double value1, double value2);
    static double sq_add(double value1, double value2);
    static double sub(double value1, double value2);
    static double div(double value1, double value2);
};