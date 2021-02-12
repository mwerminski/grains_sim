//
// Created by szylkret on 01.11.2020.
//

#include <iomanip>
#include "Logger.h"
#define SECONDS 1000000;

std::stringstream Logger::buffer;

const std::stringstream &Logger::getBuffer() {
    return Logger::buffer;
}

void Logger::appendMeasurement(std::string functionName, std::chrono::microseconds time) {
    buffer.precision(6);
    Logger::buffer << functionName << " : " << double(time.count()) /  1000000 << "s" << std::endl;
}

void Logger::appendInfo(std::string title, std::string text) {
    Logger::buffer << title << " : " << text <<  std::endl;
}

static void appendInfo(std::string info);