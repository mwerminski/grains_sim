//
// Created by szylkret on 17.10.2020.
//

#include <iostream>
#include <algorithm>
#include "MC.h"
#include "../../cells/Cell.h"
#include "../../time_logger/Logger.h"


void MC::start(std::shared_ptr<std::vector<Cell>> cells, unsigned int iterations) {

    Logger::appendInfo("Method", "Monte carlo");

    grainDist = std::uniform_int_distribution<int>(1, initialNumOfGrains);
    auto probabilityDist = std::uniform_int_distribution<int>(0, 100);

    for(auto& cell : *cells){
        cell.setGrainId(grainDist(mt));
    }

    std::vector<int> cellDist(cells->size());

    for(unsigned int it = 0; it < iterations; it++) { // MCS

        std::iota(cellDist.begin(), cellDist.end(), 0);
        std::shuffle(cellDist.begin(), cellDist.end(), mt);

        float randomCellEnergy = 0;
        float randomCellNewEnergy = 0;
        unsigned int randomGrainId;
        for (unsigned int cid = 0; cid < cells->size(); cid++) {

            auto randomCell = cells->at(cellDist[cid]);
            randomCellEnergy = 0;
            randomCellNewEnergy = 0;
            randomGrainId = grainDist(mt);

            for (auto &id : randomCell.getNeighbours()) {
                const auto& neighbourGrainId = cells->at(id - 1).grainId;
                if (neighbourGrainId != randomCell.grainId) randomCellEnergy++;
                if (neighbourGrainId != randomGrainId) randomCellNewEnergy++;
            }

            auto deltaEnergy = randomCellNewEnergy - randomCellEnergy;
            if (deltaEnergy <= 0 or probabilityDist(mt) < exp(-1 * deltaEnergy / 0.6))
                randomCell.setGrainId(randomGrainId);
        }
    }
}

MC::MC(unsigned int initialNumOfGrains) : initialNumOfGrains(initialNumOfGrains) {
    std::random_device rd;
    mt = std::mt19937(rd());
}

std::string MC::getMethodName() {
    return "MC";
}