//
// Created by szylkret on 14.10.2020.
//

#ifndef GRAINS_NEIGHBOURHOODTYPE_H
#define GRAINS_NEIGHBOURHOOD_H


#include <memory>
#include "../cells/Cell.h"
#include "../enums/DimensionType.h"

class Neighbourhood {
protected:
    bool isPeriodical = false;
public:
    virtual void setNeighbours(std::shared_ptr<std::vector<Cell>> cells, std::tuple<DimensionType, unsigned int, unsigned int, unsigned int>, bool isPeriodical) = 0;
};


#endif //GRAINS_NEIGHBOURHOODTYPE_H
