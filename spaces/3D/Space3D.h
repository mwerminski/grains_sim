//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_SPACE3D_H
#define GRAINS_SPACE3D_H


#include "../Space.h"

class Space3D : public Space{
public:
    explicit Space3D(std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions);

    std::shared_ptr<std::vector<Cell>> getCells() override;
    void setCells(std::shared_ptr<std::vector<Cell>> cells) override;
};


#endif //GRAINS_SPACE3D_H
