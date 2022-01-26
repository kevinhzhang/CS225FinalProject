#include "Heatmap.h"


//Default constructor, unused
Heatmap::Heatmap() {}


/*
Heatmap Constructor, initializes a Heatmap object with a PNG that we are going to overlay on; a CSV file with 
Names of cities, population, and Latitude/Longitude coordinates; and a Sizing PNG with the area desired to be heatmapped colored
orange
*/
Heatmap::Heatmap(PNG starterpic, string afilename, PNG sizing1) {
    sizing(sizing1);
    radius();
    dataPoints = fromCSV(afilename);
    bucket_data = Bucket(_radius, dataPoints, coordextremes);
    heatermap = starterpic;
    
}


/*
Function to convert latitude longitude coordinates to Coordinates on a map
*/
std::pair<int, int> Heatmap::LLtoCoords(Point<2> a) {
    std::pair<int, int> blue; 
    //first should be the x value
    blue.second = _pixelextremes[3] + ((a[0] - coordextremes[3])*latscale);
    //longitude  
    blue.first = _pixelextremes[1] - ((a[1] - coordextremes[0])*longscale);
    return blue; 
}


/*
Helper function to convert X Y coordinates on the PNG to corresponding latitude longitude coordinates
*/
Point<2> Heatmap::CoordstoLL(int x, int y) {
    double xoffset = ((int)_pixelextremes[1] - x)/longscale; 
    double yoffset = ((int)_pixelextremes[2] - y)/latscale; 
    Point <2> a(-yoffset + coordextremes[2], xoffset + coordextremes[0]);
    return a; 
}


/**
 * The sizing function takes in the PNG and finds the maximum values of the the things, maximum latitude and longitude for each state
 * can be found online. Sizing function effectively finds the Borders of Illinois, and then correlates them to the Max Longitude, Latitude
 values and maps it to the image's lowest X lowest Y highest X highest Y 
 * */
void Heatmap::sizing(PNG image) {
    //East West North South, in that Order
    coordextremes.push_back(-87.4975);
    coordextremes.push_back(-91.509878);
    coordextremes.push_back(42.508);
    coordextremes.push_back(36.979496);

    vector<int> extremes; 
    bool breakflag = false; 
    //East
    for (unsigned width = 0; width < image.width() && !breakflag ; width++) {
        for (unsigned height = 0; height < image.height() && !breakflag; height++) {
            if(image.getPixel(width, height).l >  0.1 && image.getPixel(width, height).l < .9 && 22 < image.getPixel(width, height).h && image.getPixel(width, height).h< 54 ) {
                extremes.push_back(width);
                breakflag = true; 
            }
        }
    }
    breakflag = false;
    //West
    for (unsigned width = image.width() - 1; width >= 0 && !breakflag ; width--) {
        for (unsigned height = 0; height < image.height() && !breakflag; height++) {
            if(image.getPixel(width, height).l >  0.1 && image.getPixel(width, height).l < .9 && 22 < image.getPixel(width, height).h && image.getPixel(width, height).h< 54) {
                extremes.push_back(width);
                breakflag = true; 
            }
        }
    }
    //N
    breakflag = false; 
    for (unsigned height = 0; height < image.height() && !breakflag ; height++) {
        for (unsigned width = 0; width < image.width() && !breakflag; width++) {
            if(image.getPixel(width, height).l >  0.1 && image.getPixel(width, height).l < .9 && 22 < image.getPixel(width, height).h && image.getPixel(width, height).h< 54) {
                extremes.push_back(height);
                breakflag = true; 
            }
        }
    }
    breakflag = false; 
    //S
    for (unsigned height = image.height() - 1; height >= 0 && !breakflag ; height--) {
        for (unsigned width = 0; width < image.width() && !breakflag; width++) {
            if(image.getPixel(width, height).l >  0.1 && image.getPixel(width, height).l < .9 && 22 < image.getPixel(width, height).h && image.getPixel(width, height).h< 54) {
                extremes.push_back(height);
                breakflag = true; 
            }
        }
    }
   
    if(extremes.size() != 4) {
        return; 
    }
    _pixelextremes = extremes; 
    longscale =  ((int)_pixelextremes[0] - (int)_pixelextremes[1])/(coordextremes[0] - coordextremes[1]);
    latscale = ((int)_pixelextremes[2] - (int)_pixelextremes[3])/(coordextremes[2] - coordextremes[3]);

}


/*
CSV File Parser
*/
vector<Point<2>> Heatmap::fromCSV(string filename) {

    //return vector, to be used for KDTRee and Test cases
    std::vector<Point<2>> finalVec;

    //generate the input filstream
    
   
    std::ifstream ourFile{filename};
    //throw an error if unopenable
    if(!ourFile.is_open()) {
        throw std::runtime_error("File Error: Unopenable");
    }

    //check if file is valid, then parseX
    if(ourFile.good()) {

        //helper variable for current line as CSV is parsed
        std::string line;

        //parses through every single line in the CSV
        while (std::getline(ourFile, line)) {

            //creates a stringstream and temporary vector to store words in each line
            std::stringstream curr(line);
            std::vector<std::string> row;
            std::string currWord;

            //helper variable for population value stored in current line
            std::string pop;


            //splits the string up by commas and stores individual strings in temporary vector
            while (std::getline(curr, currWord, ',')) {
                row.push_back(currWord);
            }

            //converts latitude value from a string into a double and stores it
            double lat = std::stod(row[6]);

            //converts longitude value from a string into a double and stores it
            double longi = std::stod(row[7]);

            //creates a point using latitude and longitude values
            Point<2> newPoint(lat, longi);

            //retrives population value as a string from csv
            pop = row[2];

            //removes double quotation marks
            //make this an if statement later for modularity (check if double quotation marks exist)

            //converts population value from string to integer
            int population = std::stoi(pop);

            //stores the population into the map with the new point as key
            //not required functionality, but it would be nice to have an if statement that exludes out of bounds points
            cities[newPoint] = population;

            //not required functionality, but it would be nice to have an if statement that exludes out of bounds points
            //pushes back new point into vector of points used to generate KDTree            
            finalVec.push_back(newPoint);

        }
    }

    return finalVec;
}



/*
Radius sets the radius at which the search function yields a negliglible difference in the weight function, 
the weight function is ((N/1000)*1.6)/17 * .87^r, the radius is the r at which the resultant population density becomes < 10 ppl/square mile
*/
void Heatmap::radius()
{
    //KDTree Find the Max, and then go from there, for now it's radius = 47.128, when the weight funciton ((N/1000)^(3/2))/20 * .87^r reaches 
    //less than 10 people/square mile, 
    _radius = 47.128; 
}


//Fully modular
/*
Findweight, the resultant population density from the population of each city by distance from city center
assumes all cities are equally populated and follow a similar population distrubution curve, with a population density of 
(N/1000)^1.53 * .85^r, where N is the population of the city and r is the distance from city center. This population density
function was approximate using New York City
*/
double Heatmap::findWeight(vector<Point<2>> points,Point<2> origin) {
    double sum = 0; 
    for(unsigned i = 0; i < points.size(); i++) {
        sum += pow((cities[points[i]]/1000) , (1.53))* pow(.85 , findMileDist(origin, points[i]));
    }
    return sum/17; 
}


/*
Finds the distance in miles between two latitude/longitude points
*/
double Heatmap::findMileDist(Point<2> a, Point<2> b) const {
    double ydiff = a[0] - b[0];
    double xdiff = a[1] - b[1];
    ydiff = ydiff * 68.9405307476;
    xdiff = xdiff * 52.6951847508;
    return pow((pow(ydiff, 2) + pow(xdiff, 2)), .5);
}


/*
Generates a Heatmap with transit hotspots
*/
PNG Heatmap::generateWithHotspots(std::priority_queue<MapGraph::graphNode, std::vector<MapGraph::graphNode>, std::greater<MapGraph::graphNode>> input, PNG png) {
    PNG returnImage = png;
    while (!(input.empty())) {
        MapGraph::graphNode node;
        node = input.top();
        input.pop();
        Point<2> temp = node.me;
        std::pair<int, int> xy = LLtoCoords(temp);
        for(int i = xy.first - 15; i <= xy.first + 15; i++) {
            for(int j = xy.second - 15; j <= xy.second + 15; j++) {
                returnImage.getPixel(i,j) = HSLAPixel(320, 1, .5, 1);
            }
        }

    }
    return returnImage;

}


/*
Generates the heatmap using an imagetraversal
*/
PNG Heatmap::generateMap() {

    
    PointTraversal startPoint(1800, 1800);
    double tol = 0.2;
    PNG finalMap = heatermap;
    std::vector<Point<2>> nearestR;
    BFS t(heatermap, startPoint, tol);
    ImageTraversal::Iterator i;
    for (i = t.begin(); i != t.end(); ++i) {

       
        
        PointTraversal temp = *i;
        Point<2> curr_LL = CoordstoLL(temp.x,temp.y);
        nearestR = bucket_data.findRadiusNeighbors(curr_LL);
        double currWeight = findWeight(nearestR, curr_LL);
    
        HSLAPixel & currentPixel = finalMap.getPixel(temp.x, temp.y);
        
        if(currWeight < 4500){
        currentPixel.l = .17 + .047552*log(currWeight + 1);
        currentPixel.h = 288 - 27.81795*log(currWeight + 1);
        }
        else{
            currentPixel.l = .57;
            currentPixel.h = 54;
        }
        currentPixel.s = 1;
        currentPixel.a = 1;
        }

    
    return finalMap;
}

/**
 *  Our implementation of Prim's algorithim, takes a graph from the MapGraph class as input 
 * and returns a mininum spanning tree also represented as an instance of the MapGraph class
**/
MapGraph Heatmap::PrimMST(MapGraph G)
{
    std::priority_queue<primNode, vector<primNode>, greater<primNode>> ourQueue;
    std::map<Point<2>, bool> hasVisited;
    std::vector<MapGraph::edge*> temp;
    MapGraph ourMST;
    Point<2> first = G.head;

    primNode primera;
    primera.me = first;
    primera.mySource = first;
    primera.cost = 0;
    ourQueue.push(primera);

    while (!(ourQueue.empty())) {
        primNode p1 = ourQueue.top();
        ourQueue.pop();

        double laCosta = p1.cost;

        if (hasVisited[p1.me] != true) {
            hasVisited[p1.me] = true;
            ourMST.insertVertex(p1.me);
            ourMST.insertEdge(p1.mySource, p1.me);
            temp = G.incidentEdges(p1.me);
            for (auto i : temp) {
               primNode segundo;
                if (i->first == p1.me) {
                    segundo.me = i->second;
                } else {
                    segundo.me = i->first;
                }
                segundo.mySource = p1.me;
                segundo.cost = findMileDist(segundo.me, segundo.mySource);
                ourQueue.push(segundo);
            }
        }
    }
    return ourMST;
}




