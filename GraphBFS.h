#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <math.h>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <queue>
#include <fstream>
#include <sstream>

#include "point.h"
#include "MapGraph.h"


//Graph BFS class used for verification of the constructed graph

class GraphBFS {
    public:

    //Default Constructor for Graph BFS
    GraphBFS();

    //Constructor with MapGraph Input
    GraphBFS(MapGraph graph);
    
    //Function in which Graph BFS is ran
    void runBFS(Point<2> start);
    
    //Check and see if the Graph BFS is successful
    bool status();

    //Returns the visited vector
    std::vector<Point<2>> getVisited();

    private:
    MapGraph g;

    //vector of points that have already been visited
    std::vector<Point<2>> visited;

    //queue used for the BFS
    std::queue<Point<2>> q;

    //Function to check if point is visited or not
    bool isVisited(Point<2> input);
};