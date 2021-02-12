//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_MC_H
#define GRAINS_MC_H


#include <memory>
#include <random>
#include "../Method.h"
#include "../../cells/Cell.h"

class MC : public Method{
public:
    MC(unsigned int initialNumOfGrains);

    void start(std::shared_ptr <std::vector<Cell>> cells, unsigned int iterations);

    std::string getMethodName() override;


private:
    unsigned int initialNumOfGrains;
    std::uniform_int_distribution<int> cellDist;
    std::uniform_int_distribution<int> grainDist;
    std::mt19937 mt;

};


#endif //GRAINS_MC_H
