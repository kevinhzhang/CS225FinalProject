#pragma once
#include <map>
#include <vector>
#include "point.h"
#include <cmath>
using namespace std;
/**
The bucket class helps with the find all neighbors within a certain radius, what it does is divides the points into an array 
of squares with side r, so to find all neighbors within a certain radius, it just searches the current square and the surrounding 
squares. 
*/
class Bucket {
    public:

    //Constructor for the bucket class
    Bucket();
    /*
    Constructs Bucket with a radius, a vector, and a vector of latitude longitude extrmes
    */
    Bucket(double r, std::vector<Point<2>> vec, std::vector<double> extremes);
    /*
    Finds all points within radius r from the query point
    */
    std::vector<Point<2>> findRadiusNeighbors(Point<2> query);
    /*
    find distance in miles helper function
    */
    double distance(Point<2> a, Point<2> b);
    std::map<int, vector<Point<2>>> bucket;
    double getSize();
    vector<Point<2>> getVector(int key);
    
    private:
    std::vector<double> _xtr;
    double _latscale;
    double _longscale;
    int _width;
    int _height; 
    double _rad; 
};