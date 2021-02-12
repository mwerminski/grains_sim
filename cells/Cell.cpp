//
// Created by szylkret on 14.10.2020.
//

#include <iostream>
#include "Cell.h"

unsigned int Cell::ids = 1;

const int Cell::getId() const {
    return id;
}

const std::vector<unsigned int> &Cell::getNeighbours() const {
    return neighbours;
}

void Cell::setNeighbours(std::vector<unsigned int> && neighbours) {
    Cell::neighbours = neighbours;
}

Cell::Cell() : id(ids), grainId(0), potentialGrainId(0) {ids++;}

unsigned int Cell::getGrainId() const {
    return grainId;
}

void Cell::setGrainId(unsigned int grainId) {
    Cell::grainId = grainId;
}

void Cell::setPotentialGrainId(unsigned int grainId) {
    Cell::potentialGrainId = grainId;
}

void Cell::acceptNewGrain(){
    if (potentialGrainId != 0) grainId = potentialGrainId;
}
