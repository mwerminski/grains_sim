//
// Created by szylkret on 01.11.2020.
//

#ifndef GRAINS_LOGGER_H
#define GRAINS_LOGGER_H


#include <sstream>
#include <chrono>

class Logger {
public:
    static std::stringstream buffer;
    static const std::stringstream &getBuffer();
    static void appendMeasurement(std::string functionName, std::chrono::microseconds time);
    static void appendInfo(std::string title, std::string text);

};


#endif //GRAINS_LOGGER_H
