//
// Created by szylkret on 17.10.2020.
//

#include "Space3D.h"
#include "../../time_logger/Logger.h"

Space3D::Space3D(std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions) : Space(dimensions) {

}

std::shared_ptr<std::vector<Cell>> Space3D::getCells() {
    return Cells;
}

void Space3D::setCells(std::shared_ptr<std::vector<Cell>> cells) {
    Logger::appendInfo("Dimension", "3D");
    Cells = cells;
}
