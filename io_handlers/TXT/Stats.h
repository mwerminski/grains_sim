//
// Created by szylkret on 01.11.2020.
//

#ifndef GRAINS_STATS_H
#define GRAINS_STATS_H


#include "../Writer.h"

class Stats : public Writer{
public:
    Stats();
    void writeToFile(const std::stringstream & stream, std::string fileName) final;
    void writeToFile(std::shared_ptr<std::vector<Cell>> cells,
                             std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions,
                             std::string fileName) override;

};


#endif //GRAINS_STATS_H
