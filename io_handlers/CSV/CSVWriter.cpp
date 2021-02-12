//
// Created by szylkret on 17.10.2020.
//

#include <fstream>
#include "CSVWriter.h"

void CSVWriter::writeToFile(std::shared_ptr<std::vector<Cell>> cells,
                            std::tuple<DimensionType, unsigned int, unsigned int, unsigned int> dimensions,
                            std::string fileName) {

    auto& [dim, xDim, yDim, zDim] = dimensions;
    std::ofstream csvFile(fileName);

    csvFile << xDim << "," << yDim << "," << zDim << std::endl; // first row - info about dimensions

    for(auto cellId = 0; cellId < cells->size(); cellId++){
        csvFile << cells->at(cellId).grainId;
        if((cellId + 1) % xDim == 0){
            csvFile << "\n";
        }
        else{
            csvFile << ",";
        }

    }

    csvFile.close();


}

void CSVWriter::writeToFile(const std::stringstream &stream,  std::string fileName) {}

CSVWriter::CSVWriter() = default;
