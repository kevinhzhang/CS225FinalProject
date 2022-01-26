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


class MapGraph {

    public:

    struct edge {
        Point<2> first;
        Point<2> second;
        double ourWeight;
    };

    struct graphNode {
        Point<2> me;
        double degree;

        bool operator<(const graphNode p) const {
            return degree < p.degree;
        }

        bool operator>(const graphNode p) const {
            return degree > p.degree;
        }
    };


    //This is the stored head value, used for the BFSGraph traversal as a starting point
    Point<2> head;


    /**
     * This is a MapGraph constructor designed to take a vector of points
     * And built the graph so that every single node is connected to every other node
     * with the correct edge weights based on mile distance from one another
    **/
    MapGraph(std::vector<Point<2>> input);


    /**
     * This is a MapGraph constructor that allows you to initialize a single point as the head
     * and build the graph from there
    **/
    MapGraph(Point<2> head);


    /**
     * This is a MapGraph constructor that generates a completely empty graph
     * You can begin building the graph using insertVertex() and insertEdge()
     * The first vertex inserted into the empty graph will become the ehad
    **/
    MapGraph();


    /**
     * This is the destructor for the MapGraph class
    */
    ~MapGraph();


    /**
     * This function allows for the addition of nodes to an existing graph
     * In our graph implementation, nodes are represented as points
     * The input point will automatically be stored in the graph as a node
     * This function is built to handle duplicate insertions
    **/
    void insertVertex(Point<2> input);


    /**
     * This function allows for the addition of edges to an existing graph
     * In our graph implementation, the weight of an edge is the distance between its two endpoints
     * This is automatically calulating in the insertEdge() function
     * It generates the edge with the correct weight
     * And stores it into the adjacency lists of both endpoints
     * This function is build to handle duplicate insertions
     * This function is also built to handle edges with endpoints that have not been inserted into the graph
     * Via insertVertex()
    **/
    void insertEdge(Point<2> end1, Point<2> end2);


    /**
     * This function accepts a node of the graph as a point and returns a vector of pointers to all the edges
     * that are incident to that node,
     * aka all the edges with that node as an endpoint
    **/
    std::vector<edge*> incidentEdges(Point<2> vert);


    /**
     * This function accepts a node of the graph as a point and returns a vector of all the other points that are connected to that point
    **/
    std::vector<Point<2>> adjacentVertices(Point<2> vert);


    /**
     * This function uses the nodes and edges currently stored in the instance of the graph
     * and returns the n number of nodes with the highest degree in that graph
     * n depends on the input of the user
     * The point of the function is to return "hotspots" of the graph
     * It is meant to be used on a mininum spanning tree
     * But could be used with any valid instance of the MapGraph class
    **/
    std::priority_queue<graphNode, std::vector<graphNode>, std::greater<graphNode>> returnHotspots(unsigned amount);


    /**
     * This is a boolean function that signifies whether the two points inputted are adjacent to one another
     * in the current instance of the MapGraph
    **/
    bool areAdjacent(Point<2> end1, Point<2> end2);


    // This is the assignment operator for the MapGraph class
    void operator=(MapGraph G);


    // This function returns the amount of vertices currently stored in the MapGraph
    unsigned size() const;


    protected:


    // This is the data structure used to store the nodes and their associated adjacency lists
    std::map<Point<2>, std::list<edge*>> adjacencyMap;

    private:


    /**
     * This is a helper function which allows insertEdge() to accept edge insertions with verticies
     * That have not been inserted via the insertVertex() function
    **/
    void insertVertexViaEdge(Point<2> input);


    //This is a helper function used for calculating an edge's weight given its endpoints
    double distance(Point<2> a, Point<2> b);
};