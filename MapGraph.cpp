#include "MapGraph.h"

MapGraph::MapGraph(std::vector<Point<2>> input) {
    insertVertex(input[0]);
    head = input[0];

    for (unsigned j = 1; j < input.size(); j++) {
        insertVertex(input[j]);
    }

    for (unsigned i = 0; i < input.size(); i++) {
        for (unsigned k = (i + 0); k < input.size(); k++) {
            insertEdge(input[i], input[k]);
        }
    }
}

MapGraph::MapGraph() {}

MapGraph::MapGraph(Point<2> head1) {
    head = head1;
}

MapGraph::~MapGraph() {
    adjacencyMap.clear();
}

void MapGraph::insertVertex(Point<2> input)
{
    if (adjacencyMap.find(input) == adjacencyMap.end()) {
        std::list<edge*> list;
        if (adjacencyMap.empty()) {
            head = input;
        }
        adjacencyMap[input] = list;
    } else {
        return;
    }
}

void MapGraph::insertVertexViaEdge(Point<2> input) {
    std::list<edge*> list;
    if (adjacencyMap.empty()) {
        head = input;
    }
    adjacencyMap[input] = list;
}

void MapGraph::insertEdge(Point<2> end1, Point<2> end2)
{
    if (adjacencyMap.find(end1) == adjacencyMap.end()) {
        insertVertexViaEdge(end1);
    }

    if (adjacencyMap.find(end2) == adjacencyMap.end()) {
        insertVertexViaEdge(end2);
    }

    if (areAdjacent(end1, end2)) {
        return;
    }

    if (end1 == end2) {
        return;
    }

    edge* newEdge = new edge;

    newEdge->first = end1;
    newEdge->second = end2;
    newEdge->ourWeight = distance(end1, end2);
    adjacencyMap[end1].push_back(newEdge);
    adjacencyMap[end2].push_back(newEdge);
}

double MapGraph::distance(Point<2> a, Point<2> b) {
    double ydiff = a[0] - b[0];
    double xdiff = a[1] - b[1];
    ydiff = ydiff * 68.9405307476;
    xdiff = xdiff * 52.6951847508;
    return pow((pow(ydiff, 2) + pow(xdiff, 2)), .5);
}

std::vector<MapGraph::edge*> MapGraph::incidentEdges(Point<2> vert)
{
    std::list<edge*> temp = adjacencyMap[vert];
    std::vector<edge*> tempVec;
    for (auto i : temp) {
        tempVec.push_back(i);
    }
    return tempVec;
}

std::vector<Point<2>> MapGraph::adjacentVertices(Point<2> vert)
{

    std::list<edge*> temp = adjacencyMap[vert];
    std::vector<Point<2>> tempVec;
    for (auto i : temp) {
        if (i->first != vert) {
            tempVec.push_back(i->first);
        } else {
            tempVec.push_back(i->second);
        }
    }
    return tempVec;
}

std::priority_queue<MapGraph::graphNode, std::vector<MapGraph::graphNode>, std::greater<MapGraph::graphNode>> MapGraph::returnHotspots(unsigned amount)
{
    std::priority_queue<MapGraph::graphNode, std::vector<MapGraph::graphNode>, std::greater<MapGraph::graphNode>> ourQueue;
    if (adjacencyMap.empty()) {
        return ourQueue;
    }
    if (amount < 1) {
        return ourQueue;
    }
    for (std::pair<Point<2>, std::list<edge*>> x: adjacencyMap) {
        graphNode node;
        node.me = x.first;
        node.degree = x.second.size();
        ourQueue.push(node);
        if (ourQueue.size() > amount) {
            ourQueue.pop();
        }
    }
    return ourQueue;
}

bool MapGraph::areAdjacent(Point<2> end1, Point<2> end2) 
{
    std::list<edge*> temp = adjacencyMap[end1];
    bool truth = false;
    for (auto i : temp) {
        if (i->first == end2) {
            truth = true;
        } else if (i->second == end2) {
            truth = true;
        }
    }
    return truth;
    
}

unsigned MapGraph::size() const
{
    return adjacencyMap.size();
}

void MapGraph::operator=(MapGraph G) 
{
    head = G.head;
    adjacencyMap = G.adjacencyMap;
}
