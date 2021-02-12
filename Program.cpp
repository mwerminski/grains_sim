//
// Created by szylkret on 17.10.2020.
//

#include <iostream>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <mpi.h>
#include "Program.h"
#include "neighbourhoods/neumann/NeumannNeighbourhood.h"
#include "neighbourhoods/moore/MooreNeighbourhood.h"
#include "methods/monte_carlo/MC.h"
#include "methods/cellular_automata/CA.h"
#include "spaces/2D/Space2D.h"
#include "spaces/3D/Space3D.h"
#include "cells/Cell.h"
#include "io_handlers/CSV/CSVWriter.h"
#include "time_logger/Logger.h"
#include "io_handlers/TXT/Stats.h"

void Program::initializeCells() {

    const auto& [dimension, xdim, ydim, zdim] = space->getDimensions();
    Logger::appendInfo("X Y Z", std::to_string(xdim) + " " + std::to_string(ydim) + " " + std::to_string(zdim));
    unsigned long int numOfCells;
    switch(dimension){
        case DimensionType::DIM3D:
            numOfCells = xdim * ydim * zdim;
            break;
        case DimensionType::DIM2D:
        default:
            numOfCells = xdim * ydim;
    }
    auto cells = std::make_shared<std::vector<Cell>>(numOfCells);
    space->setCells(cells);
    auto t1 = std::chrono::high_resolution_clock::now();
    neighbourhood->setNeighbours(cells, space->getDimensions(), isPeriodic);
    auto t2 = std::chrono::high_resolution_clock::now();
    Logger::appendMeasurement("setNeighbours()", std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ));

}

void Program::compute() {
    Logger::appendInfo("Iterations", std::to_string(iterations));
    auto cells = space->getCells(); // pointer
    auto t1 = std::chrono::high_resolution_clock::now();

    int cells_num = cells->size();

    int chunk_end = cells_num / (num_of_processes - 1) * rank;
    int chunk_start = cells_num / (num_of_processes - 1) * (rank - 1);
    int size_tag = 1;
    int ids_tag = 2;

    if(rank == num_of_processes - 1) chunk_end = cells_num;

//    int = chunk_end - chunk_start;

    if (rank != 0){
        method->start(cells, iterations, chunk_start, chunk_end);
        int array_size = chunk_end - chunk_start;
        int dest = 0; // rank 0

        MPI_Send(&array_size, 1, MPI_UNSIGNED, dest, size_tag, MPI_COMM_WORLD); //send chunk size

        int ids [array_size];

        for(int i = chunk_start; i < chunk_end; i++){
            ids[i - chunk_start] = cells->at(i).grainId;
        }
        MPI_Send(ids, array_size, MPI_INT, dest, ids_tag, MPI_COMM_WORLD); //send chunk
    }
    else if (num_of_processes != 1){
        int part_array_size = 0;
        int array_size = 0;
        MPI_Status status;
        for (int sender = 1; sender < num_of_processes; sender++) { //recv chunk size

            auto code = MPI_Recv(&part_array_size, 1, MPI_INT, sender, size_tag, MPI_COMM_WORLD, &status);
            if (code != MPI_SUCCESS) {
                MPI_Abort(MPI_COMM_WORLD, code);
            }

            array_size += part_array_size;

            int ids [part_array_size];
            code = MPI_Recv(ids, part_array_size, MPI_INT, sender, ids_tag, MPI_COMM_WORLD, &status); //recv chunk
            if (code != MPI_SUCCESS) {
                MPI_Abort(MPI_COMM_WORLD, code);
            }

            std::string size = "recv size: " + std::to_string(part_array_size) + " from " + std::to_string(sender);
            int sender_chunk_start = cells_num / (num_of_processes - 1) * (sender - 1);
            for(auto cell_id = sender_chunk_start; cell_id < sender_chunk_start + part_array_size; cell_id++){
                cells->at(cell_id).grainId = ids[cell_id - sender_chunk_start];
            }
        }
    }
    else{
        method->start(cells, iterations, chunk_start, chunk_end);
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    Logger::appendMeasurement("start()", std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ));

    // MPI

}

void Program::saveResults() {
    auto& cells = *space->getCells();
    auto [dimType, xDim, yDim, zDim] = space->getDimensions();
    char buffer[256];
    sprintf(buffer, "results_%s_%d_%d_%d_",
            method->getMethodName().c_str(), xDim, yDim, zDim);
    std::stringstream fileName;
    fileName << buffer << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S.csv");
    writer = std::make_unique<CSVWriter>();
    writer->writeToFile(space->getCells(), space->getDimensions(), fileName.str());
}

void Program::saveStatistics() {
    auto [dimType, xDim, yDim, zDim] = space->getDimensions();
    Stats statsHandler;
    auto& stats = Logger::getBuffer();
    char bufferName[256];
    sprintf(bufferName, "stats_%s_%d_%d_%d_",
            method->getMethodName().c_str(), xDim, yDim, zDim);
    std::stringstream fileName;
    fileName << bufferName << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    statsHandler.writeToFile(stats, fileName.str());
}

Program::Program(NeighbourhoodType neighbourhoodType, MethodType method, unsigned int iterations, unsigned int initialGrainNum, DimensionType dimension, unsigned int xDim, unsigned int yDim, unsigned int zDim, bool isPeriodic) {
    switch (neighbourhoodType){
        case NeighbourhoodType::NEUMANN:
            this->neighbourhood = std::make_unique<NeumannNeighbourhood>();
            break;
        case NeighbourhoodType::MOORE:
        default:
            this->neighbourhood = std::make_unique<MooreNeighbourhood>();
    }

    switch (method){
        case MethodType::MONTE_CARLO:
            this->method = std::make_unique<MC>(initialGrainNum); // need to change
            break;
        case MethodType::CELLULAR_AUTOMATA:
        default:
            this->method = std::make_unique<CA>(initialGrainNum);

    }

    switch (dimension){
        case DimensionType::DIM2D:
            this->space = std::make_unique<Space2D>(Space2D({dimension, xDim, yDim, zDim}));
        case DimensionType::DIM3D:
            this->space = std::make_unique<Space3D>(Space3D({dimension, xDim, yDim, zDim}));
    }

    this->iterations = iterations;
    this->isPath = false;
    this->isPeriodic = isPeriodic;
    if(isPeriodic) Logger::appendInfo("Periodic", "True");
    else Logger::appendInfo("Periodic", "False");
    this->t = std::time(nullptr);
    this->tm = *std::localtime(&t);
}

void Program::setMPIParams(int rank, int size) {
    this->rank = rank;
    this->num_of_processes = size;
    Logger::appendInfo("MPI Params", std::to_string(rank) + " " + std::to_string(size));
}

