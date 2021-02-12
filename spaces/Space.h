//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_SPACE_H
#define GRAINS_SPACE_H


#include <utility>
#include <vector>
#include <memory>
#include "../cells/Cell.h"
#include "../enums/DimensionType.h"

class Space {
protected:
    std::shared_ptr<std::vector<Cell>> Cells = nullptr;
    std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions;
public:
    const std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> &getDimensions() const {
        return dimensions;
    }

    Space(std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions) : dimensions(std::move(
            dimensions)) {}

    virtual std::shared_ptr<std::vector<Cell>> getCells() = 0;
    virtual void setCells(std::shared_ptr<std::vector<Cell>> cells) = 0;
};


#endif //GRAINS_SPACE_H
