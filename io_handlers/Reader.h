//
// Created by szylkret on 17.10.2020.
//

#ifndef GRAINS_READER_H
#define GRAINS_READER_H
#include <string>


class Reader {
public:
    virtual void readFromFile(std::string filepath) = 0;
};


#endif //GRAINS_READER_H
