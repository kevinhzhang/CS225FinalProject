#pragma once
#include <iostream>
#include <math.h>
#include <algorithm>
#include <map> 
#include <string>
#include <iterator>
#include <iostream>
#include <utility>
#include <queue>

#include <fstream>
#include <sstream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "PointTraversal.h"
#include "BFS.h"
#include "Bucket.h"
#include "MapGraph.h"
//WE NEED TO INCLUDE OUR IMAGE TRAVERSALS
using namespace cs225;

class Heatmap {
    public:

    /**
     * This is a struct used in the PrimMST() function to generate the mininum spanning tree.
     * It allows for a weight or cost to be associated with a node instead of an edge, 
     * and allows for the storing of the source node.
    **/
    struct primNode {
        Point<2> me;
        Point<2> mySource;
        double cost;

        bool operator<(const primNode p) const {
            return cost < p.cost;
        }

        bool operator>(const primNode p) const {
            return cost > p.cost;
        }
    };


    //Default empty constructor
    Heatmap();


    /**
     * This is the proper constructor for the Heatmap Class and will call all the necessary helper functions to enable generation of the heatmap
     * This constructor must do several things:
     * 
     * First, it calls the sizing() function with the sizing PNG
     * Then, it calls the radius() helper function which currently just returns a static value
     * Then, it calls the fromCSV() function to process the CSV file and store it in data structures
     * Then, it should generate an instance of the bucket class, which allows for the use of find RadiusNeighbors() later on.
     * Finally, it should store the passed PNG as the map template we will use to generate the heatmap
    **/
    Heatmap(PNG starterpic, string filename, PNG sizing);


    /**
     * This function turns the dataset from the CSV into useable data in the heatmap object
     * It parses the CSV and pulls the data for the population, latitude, and longitude values
     * It generates a point with the latitude and longitude values
     * It stores the population within the map member variable for this class designated "cities" with the point as a key
     * It pushes the points into a vector which can be used for further data manipulation
    **/ 
    vector<Point<2>> fromCSV(string filename); 


    //This is a map we will use to associate a the location represented by a Point on the KDTree to the respective population retrived from the CSV
    std::map<Point<2>, int> cities;


    // This is a helper function designed to find the distance in miles between two points if given their latitude-longitude values, which should be stored within each point already
    double findMileDist(Point<2> a, Point<2> b) const;



     /**
     * This is the main function of Heatmap and the only one directly called outside the constructor besides fromCSV()
     * It relies on the Bucketing algorithim, (specifically findRadiusNeighbors()), ImageTraversal, and PNG map already stored within the instance
     * It returns an edited copy of the PNG map, with the hue of the pixels changed according to findWeight
     * This function requires the output of sizing() to convert the cell value to a real world value, which will be used for findDistance()
     * 
    **/
    PNG generateMap();


    /**
     * Findweight returns the resultant population density from the population of each city by distance from city center
     * assumes all cities are equally populated and follow a similar population distrubution curve, with a population density of 
     * (N/1000)^1.53 * .85^r, where N is the population of the city and r is the distance from city center. This population density
     * function was approximated using New York City
    **/
    double findWeight(vector<Point<2>> points, Point<2> origin);


    /**
     * Helper function to convert X Y coordinates on the PNG to corresponding latitude longitude coordinates
    **/
    Point<2> CoordstoLL(int x, int y);

    
    //This function takes in an exisitng Graph from the MapGraph class and returns a Mininum Spanning Tree as another MapGraph instance based upon an interpretation of Prim's Algorithim
    MapGraph PrimMST(MapGraph G);


    //This is a helper function that takes latitude-longtide values and converts them to xy coordinats on the PNG
    std::pair<int, int> LLtoCoords(Point<2> a);


    /**
     * This is a rudimentary data visualization method meant to work intandem with our heatmap and MST generation algorithim
     * It takes a priority_queue of points generated from the MapGraph member function returnHotspots and a base map png
     * It visualizes all hotspots stored within the priority_queue as pink squares on the map png based upon the location data stored within each point
     * This function ONLY works on the base map png we have provided
     * Also, this funciton is intended to be run on an MST and overlayed onto an exisitng heatmap as the base image, but it would work for a normal graph and a blank map as well
    **/
    PNG generateWithHotspots(std::priority_queue<MapGraph::graphNode, std::vector<MapGraph::graphNode>, std::greater<MapGraph::graphNode>> input, PNG png);


    protected:


    //This a double value used in the bucketing function, stored by the radius() function
    double _radius;
    

    private: 


    /** 
     * This function is a helper funciton meant to help translate the real-world latitude and longitude values to x and y values within the PNG image to the analogous real-world location those latitude and longitude values represent
     * or vice versa
     * for now, it only works for the specific map of IL provided
     * if time persists, consider adding capability for additional functionality
     * this helper function is used in findWeight() to convert the pixel/cell currently being visited into a real life lat/long location so distances can be compared
     * used in generateMapImage()
    **/
    void sizing(PNG image);


    /** 
     * This function generates a radius value that will later be used as a param in the function findRadiusNeighbors() within the KDTree class
     * essentially, it is the radial distance at which all other datapoints become negligible for a particular pixel
     * for increased modularity, this function may be changed in future iterations
     * for now the radius is a static value meant specifically for the state of IL based upon the following justification:
     * 
     * The radius function finds when the "residual impact" of the largest city becomes negligible, in this case, because our findWeight for each city
     * function has a value of (N/1000)^(3/2)/17 * .87 ^ r, where r is the radius of the city and N is the population of the city. The radius calculates
     * when the impact of population density of the largest city hits less than 10 people/square mile 
     * 
     * 
     * called upon in generateMap()
    **/
    void radius();

    
    //This is the PNG of the map we will be using to generate the image, and it will be used in sizing
    PNG heatermap; 


    /**
    Bucket 
    **/
    Bucket bucket_data;


    //This is a vector used to generate the KDTree, which is an output from fromCSV()
    std::vector<Point<2>> dataPoints;


   // Keeps track of pixel extremes in EWNS order
    std::vector<int> _pixelextremes; 


    //Map and geographical data used for the sizing() function
    double latscale; 
    double longscale; 
    std::vector<double> coordextremes; 

    
};
