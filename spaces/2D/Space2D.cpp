//
// Created by szylkret on 17.10.2020.
//

#include "Space2D.h"
#include "../../time_logger/Logger.h"

Space2D::Space2D(std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions) : Space(dimensions){}

std::shared_ptr<std::vector<Cell>> Space2D::getCells() {
    return Cells;
}

void Space2D::setCells(std::shared_ptr<std::vector<Cell>> cells){
    Logger::appendInfo("Dimension", "2D");
    Cells = cells;
}
