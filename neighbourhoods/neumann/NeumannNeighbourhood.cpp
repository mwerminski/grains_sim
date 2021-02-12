//
// Created by szylkret on 17.10.2020.
//

#include <algorithm>
#include <iostream>
#include <cmath>
#include "NeumannNeighbourhood.h"
#include "../help_funcs.h"
#include "../../time_logger/Logger.h"

NeumannNeighbourhood::NeumannNeighbourhood() = default;

void NeumannNeighbourhood::setNeighbours(std::shared_ptr<std::vector<Cell>> cells, std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimension, bool isPeriodical) {
    Logger::appendInfo("Neighbourhood", "Neumann");
    auto& [dimType, xDim, yDim, zDim] = dimension;
    const unsigned int& numOfCells = (xDim + pow(0, xDim)) * (yDim + pow(0, yDim)) * (zDim + pow(0, zDim));
    auto xy = xDim*yDim;

    for (auto& cell : *cells){
        const auto& cellId = cell.getId();
        const unsigned int hasTop = top(cellId, xDim, yDim, xy);
        const unsigned int hasBottom = bottom(cellId, xDim, yDim, xy);
        const unsigned int hasLeft = left(cellId, xDim);
        const unsigned int hasRight = right(cellId, xDim);
        const unsigned int hasFront = front(cellId, xDim, yDim);
        const unsigned int hasBack = back(cellId, xDim, yDim, zDim, xy);

        std::vector<unsigned int> neighbours = {
                    ((cellId - 1) * hasLeft),
                    ((cellId + 1) * hasRight),
                    ((cellId - xDim) * hasTop),
                    ((cellId + xDim) * hasBottom),
                    ((cellId - xy) * hasFront),
                    ((cellId + xy) * hasBack)
           };

        std::vector<unsigned int> perNeighbours;
        if(isPeriodical) {
            perNeighbours = {
                    (cellId - 1 + xDim) * (1 - hasLeft),
                    (cellId - xDim + 1) * (1 - hasRight),
                    (cellId + (xy) - xDim) * (1 - hasTop),
                    (cellId - (xy) + xDim) * (1 - hasBottom),
                    (cellId + (xy * zDim) - (xy)) * (1 - hasFront) * hasBack,
                    ((cellId - 1) % (xy) + 1) * (1 - hasBack) * hasFront
            };
            neighbours.insert(neighbours.end(), perNeighbours.begin(), perNeighbours.end());
        }
            neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(), [&](const auto& id)->bool {return id < 1;}), neighbours.end());
            neighbours.erase(std::unique(neighbours.begin(), neighbours.end()), neighbours.end());

        cell.setNeighbours(std::move(neighbours));


    }
}
