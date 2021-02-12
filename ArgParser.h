//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_ARGPARSER_H
#define GRAINS_ARGPARSER_H

#include <map>
#include <cstring>
#include "enums/DimensionType.h"
#include "enums/FileType.h"
#include "enums/MethodType.h"
#include "enums/NeighbourhoodType.h"
#include "io_handlers/CFG/Config.h"
#include "time_logger/Logger.h"

static std::map<std::string, DimensionType> mapOfDimensions = {
        {"DIM2D", DimensionType::DIM2D},
        {"DIM3D", DimensionType::DIM3D},
};

static std::map<std::string, FileType> mapOfFileTypes = {
        {"CSV", FileType::CSV},
        {"XLS", FileType::XLS},
};

static std::map<std::string, MethodType> mapOfMethods = {
        {"CELLULAR_AUTOMATA", MethodType::CELLULAR_AUTOMATA},
        {"MONTE_CARLO", MethodType::MONTE_CARLO},
};

static std::map<std::string, NeighbourhoodType> mapOfNeighbourhoods = {
        {"MOORE", NeighbourhoodType::MOORE},
        {"NEUMANN", NeighbourhoodType::NEUMANN},
};

static std::tuple<NeighbourhoodType, MethodType, unsigned int, unsigned int, DimensionType, unsigned int, unsigned int, unsigned int, bool> argParser(int argc, char *argv[]){
    NeighbourhoodType neighbourhood;
    MethodType method;
    unsigned int iterations;
    unsigned int initialGrainNum;
    DimensionType dimension;
    unsigned int xDim;
    unsigned int yDim;
    unsigned int zDim;
    bool isPeriodic;
    std::string fileName;
    switch(argc) {
        case 10: // params from cli
            neighbourhood = mapOfNeighbourhoods.find(argv[1])->second;
            method = mapOfMethods.find(argv[2])->second;
            iterations = atoi(argv[3]);
            initialGrainNum = atoi(argv[4]);
            dimension = mapOfDimensions.find(argv[5])->second;
            xDim = atoi(argv[6]);
            yDim = atoi(argv[7]);
            zDim = atoi(argv[8]);
            isPeriodic = strcmp("True",argv[9]) == 0 ? true : false;
            break;
        case 2: // params from file
            try {
                fileName = argv[1];
                auto config = Config();
                config.readFromFile(fileName);
                auto paramsMap = config.getParams();
                neighbourhood = mapOfNeighbourhoods.find(paramsMap.at("NEIGHBOURHOOD"))->second;
                method = mapOfMethods.find(paramsMap.at("METHOD"))->second;
                iterations = stoi(paramsMap.at("ITERATIONS"));
                initialGrainNum = stoi(paramsMap.at("INITIAL_GRAINS_NUM"));
                dimension = mapOfDimensions.find(paramsMap.at("DIMENSION"))->second;
                xDim = stoi(paramsMap.at("X_DIM"));
                yDim = stoi(paramsMap.at("Y_DIM"));
                zDim = stoi(paramsMap.at("Z_DIM"));
                isPeriodic = paramsMap.at("IS_PERIODICAL") == "True" ? true : false;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Invalid parameters from file!" << std::endl;
            }
            break;
        default:
            std::cerr << "Invalid number of parameters!" << std::endl;
    }
    return std::make_tuple(neighbourhood, method, iterations, initialGrainNum, dimension, xDim, yDim, zDim, isPeriodic);
}


static std::tuple<NeighbourhoodType, MethodType, unsigned int, std::string> argParserFromFile(int argc, char *argv[]){
    NeighbourhoodType neighbourhood = mapOfNeighbourhoods.find(argv[1])->second;
    MethodType method = mapOfMethods.find(argv[2])->second;
    unsigned int iterations = atoi(argv[3]);
    std::string path = argv[4];

    return {neighbourhood, method, iterations, path};
}

#endif //GRAINS_ARGPARSER_H
