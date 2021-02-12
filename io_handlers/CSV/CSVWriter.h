//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_CSVWRITER_H
#define GRAINS_CSVWRITER_H


#include <memory>
#include <vector>
#include "../Writer.h"
#include "../../cells/Cell.h"
#include "../../enums/DimensionType.h"

class CSVWriter : public Writer{
public:
    CSVWriter();
    void writeToFile(std::shared_ptr<std::vector<Cell>> cells,
                             std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions,
                             std::string fileName) final;

    void writeToFile(const std::stringstream &stream, std::string fileName) override;
};


#endif //GRAINS_CSVWRITER_H
