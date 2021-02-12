//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_WRITER_H
#define GRAINS_WRITER_H
#include "../cells/Cell.h"
#include "../enums/DimensionType.h"
#include <sstream>

class Writer {
protected:
public:
    Writer() {}
    virtual void writeToFile(std::shared_ptr<std::vector<Cell>> cells,
                             std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions,
                             std::string fileName) = 0;
    virtual void writeToFile(const std::stringstream & stream, std::string fileName) = 0;
};


#endif //GRAINS_WRITER_H
