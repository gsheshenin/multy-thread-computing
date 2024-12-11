#include <map>
#include <string>


struct FileInfo{
    bool logging;
    std::string outputName;
    std::string dirName;
};

class Parser{

public:
    static FileInfo getConfiguration(const std::string& configuration_filename);
};