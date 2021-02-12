//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_NEUMANNNEIGHBOURHOOD_H
#define GRAINS_NEUMANNNEIGHBOURHOOD_H


#include "../Neighbourhood.h"
#include "../../enums/DimensionType.h"

class NeumannNeighbourhood : public Neighbourhood {
public:
    NeumannNeighbourhood();

    void setNeighbours(std::shared_ptr<std::vector<Cell>> cells, std::tuple<DimensionType, unsigned int, unsigned int, unsigned int>, bool isPeriodical) final;

};


#endif //GRAINS_NEUMANNNEIGHBOURHOOD_H
