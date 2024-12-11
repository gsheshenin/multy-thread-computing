#include "command_executor.h"
#include "parser.h"
#include "logger.h"
#include <vector>
#include <filesystem>


struct Result{
    std::string command;
    double res;
    double value1;
    double value2;
};

class IFileManager {
public:
    void runProcess(FileInfo configuration);
    void processFilesChunk(const std::vector<std::string>& files, bool logging, const std::string& output_file);
    virtual Result processFile(const std::string& filename, const std::string& output_file) = 0;
    virtual ~IFileManager() = default;
};

class FileManager : public IFileManager {
public:

    virtual Result processFile(const std::string& filename, const std::string& output_file) override;

private:
    std::shared_ptr<IFileManager> wrappedFileManager;
};

class SimpleDecorator : public IFileManager {
public:
    SimpleDecorator(std::shared_ptr<IFileManager> wrapped)
        : wrappedFileManager(wrapped) {}
    
    Result processFile(const std::string& filename, const std::string& output_file) override {
        Result res;
        res = wrappedFileManager->processFile(filename, output_file);
        return res;
    }

private:
    std::shared_ptr<IFileManager> wrappedFileManager;
};


class LoggerDecorator : public IFileManager {
public:
    LoggerDecorator(std::shared_ptr<IFileManager> wrapped, Logger& log)
        : wrappedFileManager(wrapped), logger(log) {}
    
    Result processFile(const std::string& filename, const std::string& output_file) override {
        Result res;
        logger << "Processing " << filename << std::endl;
        res = wrappedFileManager->processFile(filename, output_file);
        logger << "Executing: " << res.command << " " << res.value1 << " " << res.value2 << " = " << res.res << std::endl;
        logger << "Finished processing file: " << filename << std::endl;
        return res;
    }
    Logger& logger;

private:
    std::shared_ptr<IFileManager> wrappedFileManager;
};