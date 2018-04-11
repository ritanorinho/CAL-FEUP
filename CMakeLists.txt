cmake_minimum_required(VERSION 3.9)
project(CAL C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(CAL
        src/GraphViewer/connection.cpp
        src/GraphViewer/edgetype.h
        src/GraphViewer/graphviewer.cpp

        src/main.cpp
        src/Client.cpp
        src/Application.cpp
        src/Graph.h
        src/Menus.cpp
        src/MutablePriorityQueue.h
        src/SharePoint.cpp src/VertexData.cpp)