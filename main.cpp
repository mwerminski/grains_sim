#include <iostream>
#include "Program.h"
#include "ArgParser.h"
#include "time_logger/Logger.h"

int main(int argc, char *argv[]) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto program = std::make_from_tuple<Program>(argParser(argc, argv));
    program.initializeCells();
    program.compute();
    program.saveResults();
    auto t2 = std::chrono::high_resolution_clock::now();
    Logger::appendMeasurement("main()", std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ));
    program.saveStatistics();
    return 0;
}

