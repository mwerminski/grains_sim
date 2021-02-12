//
// Created by szylkret on 14.10.2020.
//

#ifndef GRAINS_MOORENEIGHBOURHOOD_H
#define GRAINS_MOORENEIGHBOURHOOD_H


#include <vector>
#include "../Neighbourhood.h"
#include "../../cells/Cell.h"
#include "../../enums/DimensionType.h"

class MooreNeighbourhood : public Neighbourhood{

    void setNeighbours(std::shared_ptr<std::vector<Cell>> cellList, std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimension, bool isPeriodical) final;
};


#endif //GRAINS_MOORENEIGHBOURHOOD_H
