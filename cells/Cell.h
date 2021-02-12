//
// Created by szylkret on 14.10.2020.
//

#ifndef GRAINS_CELL_H
#define GRAINS_CELL_H


#include <vector>
#include <set>
#include <memory>

class Cell {
private:
    const unsigned int id;
//    unsigned int grainId;
    unsigned short int potentialGrainId;
    std::vector<unsigned int> neighbours;
public:
    static unsigned int ids;
    unsigned short int grainId;

    Cell();

    const std::vector<unsigned int> &getNeighbours() const;
    const int getId() const;
    unsigned int getGrainId() const;
    void setNeighbours(std::vector<unsigned int> &&neighbours);
    void setGrainId(unsigned int grainId);
    void setPotentialGrainId(unsigned int grainId);
    void acceptNewGrain();



};


#endif //GRAINS_CELL_H
