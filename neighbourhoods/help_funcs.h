//
// Created by szylkret on 18.10.2020.
//

#ifndef GRAINS_HELP_FUNCS_H
#define GRAINS_HELP_FUNCS_H

#include <cmath>
#include <iostream>
#include "../cells/Cell.h"

auto left = [](const int& cellId, const int& xDim)
{
    return (cellId - 1) % xDim == 0 ? 0 : 1;
};

auto right = [](const int& cellId, const int& xDim)
{
    return (cellId % xDim) == 0 ? 0 : 1;
};

auto top = [](const int& cellId, const int& xDim, const int& yDim, const int& xy) // 0 = top
{
    return (cellId % ( std::lrint(cellId /  (xy + 1) ) * (xy) + xDim + 1 )) - cellId == 0 ? 0 : 1;
};

auto bottom = [](const int& cellId, const int& xDim, const int& yDim, const int& xy)
{
    int tempNum = std::lrint((cellId - 1) /  (xy)) * (xy) + (xy) - xDim;
//    std::cout << "TMP : " << tempNum << std::endl;
    return (cellId % (tempNum + 1)) == cellId ? 1 : 0;

};

auto front = [](const int& cellId, const int& xDim, const int& yDim)
{
    return (cellId % (xDim * yDim + 1) - cellId) == 0 ? 0 : 1;
};

auto back = [](const int& cellId, const int& xDim, const int& yDim, const int& zDim, const int& xy)
{
    auto zzDim = (zDim != 0) ? zDim : 1;
    auto tempNum = (cellId % (xy* zzDim -  (xy) + 1)) - cellId;
    return tempNum == 0 ? 1 : 0;
};
#endif //GRAINS_HELP_FUNCS_H
