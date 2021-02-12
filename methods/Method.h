//
// Created by szylkret on 17.10.2020.
//

#include <memory>
#include <vector>
#include "../cells/Cell.h"

#ifndef GRAINS_METHOD_H
#define GRAINS_METHOD_H


class Method {

public:
    virtual void start(std::shared_ptr<std::vector<Cell>> cells, unsigned int iterations) = 0;
    virtual std::string getMethodName() = 0;
};


#endif //GRAINS_METHOD_H
