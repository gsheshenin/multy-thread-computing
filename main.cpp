#include "parser.h"
#include <chrono>


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Parser parser;
    parser.runProcess();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "time duration " << duration.count() << " msec" << std::endl;
    
    return 0;
}