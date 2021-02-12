//
// Created by szylkret on 01.11.2020.
//

#include <fstream>
#include "Stats.h"
#include <ctime>
#include <chrono>

void Stats::writeToFile(const std::stringstream & stream, std::string fileName) {
    std::ofstream outFile(fileName+".txt");

    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    outFile << "STATS: "<< std::ctime(&currentTime) << std::endl;
    outFile << "-------------------------------" << std::endl;
    outFile << stream.rdbuf() << std::endl;
    outFile.close();
}

void Stats::writeToFile(std::shared_ptr<std::vector<Cell>> cells,
                        std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions,
                        std::string fileName) {
}

Stats::Stats() = default;
