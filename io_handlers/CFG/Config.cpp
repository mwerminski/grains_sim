//
// Created by szylkret on 01.11.2020.
//

#include <fstream>
#include <iostream>
#include "Config.h"
#include "../../ArgParser.h"

void Config::readFromFile(std::string fileName) {

    std::fstream cfgFile(fileName);
    if (cfgFile.is_open())
    {
        std::string line;
        while(getline(cfgFile, line)){
            if(line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            this->params.insert({name, value});
        }
    }
    else {
        std::cerr << "Could not load provided config file." << std::endl;
    }
}

const std::map<std::string, std::string> &Config::getParams() const {
    return params;
}
