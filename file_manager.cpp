#include "file_manager.h"
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <map>

Result FileManager::processFile(const std::string& filename, const std::string& output_file) {
    std::mutex mutex1_;
    std::mutex mutex2_;
    std::mutex mutex3_;
    std::mutex mutex4_;
    std::ifstream file(filename);
    std::string line;
    Result result;
    if (file.is_open()) {
        std::lock_guard<std::mutex> lock(mutex1_);
        std::ofstream outfile(output_file, std::ios::app);
        if (outfile.is_open()) {
            std::lock_guard<std::mutex> lock(mutex2_);
            while (std::getline(file, line)) {
                std::lock_guard<std::mutex> lock(mutex4_);
                std::istringstream iss(line);
                std::string cmd;
                double value1, value2;
                
                if (iss >> cmd >> value1 >> value2) {
                    result.command = cmd;
                    result.value1 = value1;
                    result.value2 = value2;
                    std::lock_guard<std::mutex> lock(mutex3_);
                    result.res = CommandExecutor::executeCommand(cmd, value1, value2);
                    
                    outfile << value1 << " " << cmd << " " << value2 << " = " << result.res << std::endl;
                    
                }
            }
            
            outfile.close();
        }
        
        file.close();
    }
    return result;
}



void IFileManager::processFilesChunk(const std::vector<std::string>& files, bool logging, const std::string& output_file) {
    std::shared_ptr<IFileManager> fileManager = std::make_shared<FileManager>();
    Result res;
    std::mutex mutex_;
    if (logging) {
        Logger log(std::cout);
        LoggerDecorator loggerdec(fileManager, log);
        fileManager = std::make_shared<LoggerDecorator>(loggerdec); 
    }
    else{
        SimpleDecorator simpledec(fileManager);
        fileManager = std::make_shared<SimpleDecorator>(simpledec);
    }
    for (const auto& filename : files) {
        std::lock_guard<std::mutex> lock(mutex_);
        res = fileManager->processFile(filename, output_file);
    }
}

void IFileManager::runProcess(FileInfo configuration){
   
    std::string input_directory = configuration.dirName; // directory name
    std::string output_file = configuration.outputName; // name of output file
    std::vector<std::string> files;
    
    for (const auto& entry : std::filesystem::directory_iterator(input_directory)) {
        if (entry.path().extension() == ".dat") {
            files.push_back(entry.path().string());
        }
    }

    const size_t chunk_size = 100;
    std::vector<std::thread> threads;

    for (size_t i = 0; i <= files.size(); i += chunk_size) {
        std::vector<std::string> chunk(files.begin() + i, 
                                        files.begin() + std::min(i + chunk_size, files.size()));
        threads.emplace_back(&FileManager::processFilesChunk, this, std::move(chunk), configuration.logging, output_file);
        chunk.clear();
    }

    for (auto& thread : threads) {
        thread.join();
    }
}