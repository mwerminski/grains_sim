//
// Created by szylkret on 17.10.2020.
//

#include <map>
#include <algorithm>
#include <iostream>
#include "CA.h"
#include "../../time_logger/Logger.h"

void CA::start(std::shared_ptr<std::vector<Cell>> cells, unsigned int iterations) {
    Logger::appendInfo("Method", "Cellular automata");
    cellDist = std::uniform_int_distribution<int>(1, cells->size());
    auto choiceDist = std::uniform_int_distribution<int>(0, 1);
    for(auto grainId = 1; grainId < initialNumOfGrains + 1; grainId++){
        auto& randomCell =  cells.get()->at(cellDist(mt) - 1);
        randomCell.setGrainId(grainId);
    }
    bool isCompleted = false;
    while(!isCompleted or iterations == 0){
        isCompleted = true;
        iterations--;
        for (int cid = 0; cid < cells->size(); cid++) {
            auto &cell = cells->at(cid);
            if (cell.grainId == 0) {
                std::map<unsigned int, unsigned int> grainsIdsMap;
                auto& neighbours = cell.getNeighbours();
                for (auto &id : cell.getNeighbours()) {
                    const auto& grainId = cells->at(id - 1).grainId;
                    const auto& mapSearchResult = grainsIdsMap.find(grainId);
                    if (grainId > 0 and mapSearchResult != grainsIdsMap.end()) {
                        mapSearchResult->second++;
                    } else if(grainId != 0) {
                        grainsIdsMap.insert(std::make_pair(grainId, 1));
                    }
                }
                if (not grainsIdsMap.empty()) { // get most frequent grain id from the map
                    cell.setPotentialGrainId(std::max_element(std::begin(grainsIdsMap), std::end(grainsIdsMap),
                                                     [&choiceDist, this](const std::pair<unsigned int, unsigned int> &p1,
                                                        const std::pair<unsigned int, unsigned int> &p2) {
                                                         if (p1.second != p2.second) return p1.second < p2.second;
                                                         else return choiceDist(mt) == 1;
                                                     })->first);
                }
                isCompleted = false;
            }
        }
        for (int cid = 0; cid < cells->size(); cid++) {
            auto &cell = cells->at(cid);
            cell.acceptNewGrain();
        }
    }

}

CA::CA(unsigned int initialNumOfGrains) : initialNumOfGrains(initialNumOfGrains) {
    std::random_device rd;
    mt = std::mt19937(rd());
}

std::string CA::getMethodName() {
    return "CA";
}
