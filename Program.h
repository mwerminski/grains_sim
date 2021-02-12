//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_PROGRAM_H
#define GRAINS_PROGRAM_H


#include "spaces/Space.h"
#include "neighbourhoods/Neighbourhood.h"
#include "io_handlers/Reader.h"
#include "io_handlers/Writer.h"
#include "enums/NeighbourhoodType.h"
#include "enums/MethodType.h"
#include "methods/Method.h"
#include "enums/DimensionType.h"
#include "time_logger/Logger.h"
#include <chrono>

class Program {
    std::unique_ptr<Space> space = nullptr;
    std::shared_ptr<Neighbourhood> neighbourhood = nullptr;
    std::unique_ptr<Reader> reader = nullptr;
    std::unique_ptr<Writer> writer = nullptr;
    std::unique_ptr<Method> method = nullptr;
    std::string filePath;
    unsigned int iterations;
    bool isPath;
    bool isPeriodic;
    std::time_t t;
    std::tm tm;
    int rank, num_of_processes;

public:
    Program(NeighbourhoodType neighbourhoodType, MethodType method, unsigned int iterations, unsigned int initialGrainNum,
            DimensionType dimension, unsigned int xDim, unsigned int yDim, unsigned int zDim, bool isPeriodic);

    void initializeCells();
    void compute();
    void saveResults();
    void saveStatistics();
    void setMPIParams(int localRank, int size);

};


#endif //GRAINS_PROGRAM_H
