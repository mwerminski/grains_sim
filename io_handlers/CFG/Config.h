//
// Created by szylkret on 01.11.2020.
//

#ifndef GRAINS_CONFIG_H
#define GRAINS_CONFIG_H
#include "../Reader.h"
#include <string>
#include "../../enums/DimensionType.h"
#include "../../enums/MethodType.h"
#include "../../enums/NeighbourhoodType.h"

class Config : public Reader{
    std::map<std::string, std::string> params;
public:
    const std::map<std::string, std::string> &getParams() const;

public:
    void readFromFile(std::string fileName);
};


#endif //GRAINS_CONFIG_H
