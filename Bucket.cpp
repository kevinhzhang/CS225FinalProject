#include "Bucket.h"
Bucket::Bucket() {
    //does nothing, intialization purposes
}
//r is the radius, 
//vec is the vector 
//extremes is the vector of extremes
Bucket::Bucket(double r, std::vector<Point<2>> vec, std::vector<double> extremes) {
    //EWNS
    double maxEW = abs(extremes[0] - extremes[1]) * 52.6951847508;
    double maxNS = abs(extremes[2] - extremes[3]) * 68.9405307476;
    _width = std::ceil(maxEW/r);
    _height = std::ceil(maxNS/r);
    _latscale = r/68.9405307476;
    _longscale = r/52.6951847508;
    _rad = r; 
    int total = _width * _height;
    _xtr = extremes; 
    //bucketing for width
    for (int i = 0; i < _width; i++) {
        for(int j = 0; j < _height; j++) {
            for (auto it = vec.begin(); it != vec.end();) {
                if((*it)[0] <= extremes[2] - j*_latscale 
                && (*it)[0] > extremes[2]-(j+1)*_latscale 
                && (*it)[1]>=extremes[1] + i*_longscale 
                && (*it)[1] < extremes[1] + (i+1)*_longscale) {
                    bucket[j*_width + i].push_back(*it);
                    vec.erase(it);
                }
                else {
                    ++it;
                }
            }
              
        }
    } 
}
vector<Point<2>> Bucket::findRadiusNeighbors(Point<2> query) {
    vector<Point<2>> vecpoints; 
    int h = (_xtr[2] - query[0])/_latscale;
    int w = -(_xtr[1] - query[1])/_longscale; 
    int bucketnumber = h*_width + w; 
    for(int j = -1; j <= 1; j++) {
        for (int i = bucketnumber + j*_width - 1; i <= bucketnumber + j*_width + 1; i++) {
            for (auto it : bucket[i]) {
                if(distance(it, query) < _rad) {
                    vecpoints.push_back(it);
                }
            }
        }
    }
    return vecpoints; 
}
double Bucket::distance(Point<2> a, Point<2> b) {
    double ydiff = a[0] - b[0];
    double xdiff = a[1] - b[1];
    ydiff = ydiff * 68.9405307476;
    xdiff = xdiff * 52.6951847508;
    return pow((pow(ydiff, 2) + pow(xdiff, 2)), .5);
}
double Bucket::getSize() {
    return _width * _height;
}
vector<Point<2>> Bucket::getVector(int key) {
    return bucket[key];
}
