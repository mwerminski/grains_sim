//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_SPACE2D_H
#define GRAINS_SPACE2D_H


#include "../Space.h"

class Space2D : public Space{
public:
    explicit Space2D(std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions);

    std::shared_ptr<std::vector<Cell>> getCells() override;
    void setCells(std::shared_ptr<std::vector<Cell>> cells) override;

};


#endif //GRAINS_SPACE2D_H
