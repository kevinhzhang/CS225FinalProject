#include "GraphBFS.h"

GraphBFS::GraphBFS(){
  //Default Constructor, nothing to do
}

GraphBFS::GraphBFS(MapGraph graph){
   g = graph;
}

void GraphBFS::runBFS(Point<2> start){
   q.push(start);
   while(visited.size() < g.size()){
       Point<2> current = q.front();
       visited.push_back(current);
       std::vector<Point<2>> adj = g.adjacentVertices(current);
       for(Point<2> p : adj){
              if(!isVisited(p)){
              q.push(p);
              }
           
       }
       q.pop();
   }

}

bool GraphBFS::status(){
    return (visited.size() == g.size());
}

bool GraphBFS::isVisited(Point<2> input){
     for(Point<2> p: visited){
        if(input == p){
            return true;
        }
     }
     return false;
}

std::vector<Point<2>> GraphBFS::getVisited(){
    return visited;
}