//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_CA_H
#define GRAINS_CA_H


#include <random>
#include "../Method.h"

class CA : public Method{
private:
    unsigned int initialNumOfGrains;
    std::uniform_int_distribution<int> cellDist;
    std::mt19937 mt;
public:
    CA(unsigned int initialNumOfGrains);

    void start(std::shared_ptr<std::vector<Cell>> cells, unsigned int iterations);

    std::string getMethodName() override;

};


#endif //GRAINS_CA_H
