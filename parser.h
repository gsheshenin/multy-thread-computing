#include <map>
#include <string>

class Parser {

public:
    static std::map<std::string, std::string> getConfiguration(const std::string& configuration_filename);
};