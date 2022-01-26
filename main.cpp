#include <iostream>
#include "Heatmap.h"
#include "cs225/PNG.h"
#include "MapGraph.h"
#include <string>
using namespace std;
using namespace cs225;
int main(){

    //This generates the blank base map from the input png
    PNG png;       
    png.readFromFile("ILMAP.png");

    //This generates the sizing reference map from the input png
    //It is necessary for the sizing function
    PNG sizingPNG;  
    sizingPNG.readFromFile("ILMAP2.png");

    //This generates the heatmap class with all necessary inputs
    //The constructor runs several necessary helper functions needed for the visualization to work
    Heatmap heatmap(png, "FULLSET.csv",sizingPNG);

    //This is a vector storing the extreme points of IL
    //It is necessary for the helper functions used in the visualization
    std::vector<double> coordextremes;

    //This generates a graph implentation from the MapGraph class using the CSV dataset input earlier
    //The constructor is built to make the graph fully connected
    MapGraph mappidityGraphidity(heatmap.fromCSV("FULLSET.csv"));

    //This generates the mininum spanning tree by taking the graph generated above and inputing it
    //into our implementation of Prim's Algorithim
    //the produced output represents a shortest-distance traversal of all the geographical points in the dataset
    MapGraph MSTOutput;
    MSTOutput = heatmap.PrimMST(mappidityGraphidity);

    //This generates the visualized Heat Map output as a PNG
    //It does not include an MST visualization
    PNG hmap = heatmap.generateMap();
    std::cout << "Generating Heatmap" << std::endl; 
    hmap.writeToFile("Fullmap.png");
    

    //This generates the visualized Heat Map output with an overlaid rudimentary MST visualization
    //This visualization uses the returnHotspots() function, which takes the MST as input
    //And returns the nodes on the MST with the highest degree
    //They represent "hubs" in a shortest-distance traversal of the geographical points in the dataset
    //These hubs are visually represnted on the map as small pink squares
    std::priority_queue<MapGraph::graphNode, std::vector<MapGraph::graphNode>, std::greater<MapGraph::graphNode>> input = MSTOutput.returnHotspots(25);
    std::cout << "Generating Heatmap with Transit Hubs" << std::endl; 
    hmap = heatmap.generateWithHotspots(input, hmap);
    hmap.writeToFile("FullmapWithHotspots.png");
}