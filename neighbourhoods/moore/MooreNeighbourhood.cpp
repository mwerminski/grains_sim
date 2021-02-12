//
// Created by szylkret on 14.10.2020.
//

#include <algorithm>
#include "MooreNeighbourhood.h"
#include "../help_funcs.h"
#include "../../time_logger/Logger.h"

void MooreNeighbourhood::setNeighbours(std::shared_ptr<std::vector<Cell>> cells, std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimension, bool isPeriodical) {
    Logger::appendInfo("Neighbourhood", "Moore");
    auto& [dimType, xDim, yDim, zDim] = dimension;
    const unsigned int& numOfCells = (xDim + pow(0, xDim)) * (yDim + pow(0, yDim)) * (zDim + pow(0, zDim));
    auto xy = xDim * yDim;

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
            ((cellId - 1 - xDim) * hasLeft * hasTop),
            ((cellId + 1 - xDim) * hasRight * hasTop),
            ((cellId - 1 + xDim) * hasLeft * hasBottom),
            ((cellId + 1 + xDim) * hasRight * hasBottom),

            ((cellId - xDim * yDim) * hasFront),
            ((cellId - 1 - (xDim * yDim)) * hasLeft * hasFront),
            ((cellId + 1 - (xDim * yDim)) * hasRight * hasFront),
            ((cellId - xDim - (xDim * yDim)) * hasTop * hasFront),
            ((cellId + xDim - (xDim * yDim)) * hasBottom * hasFront),
            ((cellId - 1 - xDim - (xDim * yDim)) * hasLeft * hasTop * hasFront),
            ((cellId + 1 - xDim - (xDim * yDim)) * hasRight * hasTop * hasFront),
            ((cellId - 1 + xDim - (xDim * yDim)) * hasLeft * hasBottom * hasFront),
            ((cellId + 1 + xDim - (xDim * yDim)) * hasRight * hasBottom * hasFront),

            ((cellId + xDim * yDim) * hasBack),
            ((cellId - 1 + (xDim * yDim)) * hasLeft * hasBack),
            ((cellId + 1 + (xDim * yDim)) * hasRight * hasBack),
            ((cellId - xDim + (xDim * yDim)) * hasTop * hasBack),
            ((cellId + xDim + (xDim * yDim)) * hasBottom * hasBack),
            ((cellId - 1 - xDim + (xDim * yDim)) * hasLeft * hasTop * hasBack),
            ((cellId + 1 - xDim + (xDim * yDim)) * hasRight * hasTop * hasBack),
            ((cellId - 1 + xDim + (xDim * yDim)) * hasLeft * hasBottom * hasBack),
            ((cellId + 1 + xDim + (xDim * yDim)) * hasRight * hasBottom * hasBack),

        };

        if(isPeriodical) {
            std::vector<unsigned int> perNeighbours = {
                    (cellId - 1 + xDim) * (1 - hasLeft),
                    (cellId - xDim + 1) * (1 - hasRight),
                    (cellId + (xDim * yDim) - xDim) * (1 - hasTop),
                    (cellId - (xDim * yDim) + xDim) * (1 - hasBottom),
                    (cellId + (xDim * yDim * zDim) - (xDim * yDim)) * (1 - hasFront) * hasBack,
                    (cellId - (xDim * yDim * zDim) + (xDim * yDim)) * (1 - hasBack) * hasFront,

                    (cellId + (xDim * yDim) - 1) * (1 - hasLeft) * (1 - hasTop),
                    (cellId - (xDim * yDim) + xDim + xDim - 1) * (1 - hasLeft) * (1 - hasBottom),
                    (cellId + (xDim * yDim) - xDim - xDim + 1) * (1 - hasRight) * (1 - hasTop),
                    (cellId - (xDim * yDim) + 1) * (1 - hasRight) * (1 - hasBottom),

                    (cellId + (xDim * yDim * zDim) - 1 - (xDim * yDim - xDim)) * (1 - hasLeft) * (1 - hasFront) * hasBack,
                    (cellId + (xDim * yDim * zDim) - 1 - (xDim * yDim + xDim)) * (1 - hasRight) * (1 - hasFront) * hasBack,
                    (cellId - (xDim * yDim * zDim) - 1 + (xDim * yDim + xDim)) * (1 - hasLeft) * (1 - hasBack) * hasFront,
                    (cellId - (xDim * yDim * zDim) + 1 + (xDim * yDim - xDim)) * (1 - hasRight) * (1 - hasBack) * hasFront,

                    (cellId + (xDim * yDim * zDim) - xDim) * (1 - hasTop) * (1 - hasFront) * hasBack,
                    (cellId + (xDim * yDim * zDim) - (xDim * yDim) - xDim - xDim + 1) * (1 - hasBottom) * (1 - hasFront) * hasBack,
                    (cellId - (xDim * yDim * zDim) + (2 * xDim * yDim - xDim )) * (1 - hasTop) * (1 - hasBack) * hasFront,
                    (cellId - (xDim * yDim * zDim) - 1 + (xDim * yDim - xDim)) * (1 - hasBottom) * (1 - hasBack) * hasFront,

            };
            neighbours.insert( neighbours.end(), perNeighbours.begin(), perNeighbours.end());
        }
//        std::cout << " ID : " << cellId << std::endl;
//        for(auto& cc : neighbours){
//            std::cout << cc << ", ";
//        }
//        std::cout << std::endl;
        neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(), [&](const auto id)->bool {return id < 1;}), neighbours.end());
        neighbours.erase(std::unique(neighbours.begin(), neighbours.end()), neighbours.end());
        cell.setNeighbours(std::move(neighbours));



    }



}
