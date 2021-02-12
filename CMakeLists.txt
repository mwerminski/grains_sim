cmake_minimum_required(VERSION 3.17)
project(grains)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o2 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o2 ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o2 -fopenmp")

add_executable(grains main.cpp neighbourhoods/Neighbourhood.h neighbourhoods/moore/MooreNeighbourhood.cpp neighbourhoods/moore/MooreNeighbourhood.h cells/Cell.cpp cells/Cell.h spaces/Space.h io_handlers/Reader.h io_handlers/Writer.h neighbourhoods/neumann/NeumannNeighbourhood.cpp neighbourhoods/neumann/NeumannNeighbourhood.h io_handlers/CSV/CSVWriter.cpp io_handlers/CSV/CSVWriter.h spaces/3D/Space3D.cpp spaces/3D/Space3D.h spaces/2D/Space2D.cpp spaces/2D/Space2D.h Program.cpp Program.h enums/FileType.h enums/DimensionType.h enums/NeighbourhoodType.h enums/MethodType.h methods/Method.h methods/cellular_automata/CA.cpp methods/cellular_automata/CA.h methods/monte_carlo/MC.h ArgParser.h neighbourhoods/help_funcs.h io_handlers/CFG/Config.cpp io_handlers/CFG/Config.h time_logger/Logger.cpp time_logger/Logger.h io_handlers/TXT/Stats.cpp io_handlers/TXT/Stats.h methods/monte_carlo/MC.cpp)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(grains OpenMP::OpenMP_CXX)
endif()