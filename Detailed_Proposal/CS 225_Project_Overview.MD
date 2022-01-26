# CS 225 Final Project Proposal

Revised version- 11/14/2021



Philip Hu, Franklyn Wu, Kevin Zhang

University of Illinois at Urbana-Champaign

## Leading Question:

How can we help visualize the ideal connections between populations centers utilizing a directed graph, and the magnitude of those connections?

## Introduction:

This CS 225 Final Project cetners around the creation and manipulation of a heat-map. 

Heat-maps are a very common visualization method due to their intuitive format and striking visual characteristics, making them a powerful too to communicate and analyze population trends, demographic distributions, and geographical charactersitics. 

In this project, we hope to apply concepts learned in CS 225 in the creation of a heatmap generater for the state of IL, which will take any dataset of a certain format for the state of IL and generate a heatmap. 

We then plan to further implement an additional functionality for the heatmap is to analyze the data found within the heatmap to create a ideal-rate graph to calculate the minimum total distance of connections and the required connection size (tranportation, internet wire size, etc.) between the population centers. 

## Data Acquistion and Processing: 

A valid dataset for this project crequires a series of locations with a quantifiable characteristic of some kind (such as population), and latitude/longitude values. 

We have obtained two datasets for this purpose for the state of IL, which we have determined to be of sufficient size and specificity to serve well for demonstrating the capability of our heat-map tool. 

These are statistics for population, the sources for which are in Detailed_Proposal/Data_Gathering_Procedure.MD. These datasets are stored in the main directory as .csv files. 

To make these files valid for use, we used data cleaning scripts which are further described in Detailed_Proposal/Data_Processing_Procedure.MD. We do not consider these scripts part of our project. They were used purely as a resource for data gathering.

## Technical Specifications and Algorithms

#### 1. 
   The Constructor for Heatmap will take in three things: the CSV data files, the image to be overlaid on as a PNG, and the extreme points on a map (nothernmost, sourthernmost, etc.). The CSV data files will contain data with latitude, longitude, and weighted values. The image PNG will be a nearly blank PNG, with a black border and a single-colored markings to denote which state it is. This is to prevent bad BFS traversing that will result in a bad visualization. This constructor will call on several helper functions: a function to help read the CSV data file, a sizing function that takes in the PNG and the extreme points on the map, a KDTree constructor that takes in the coordinate data from the CSV data file and turns it into a KDTree, and a radius helper function. The Radius helper function is to determine the maximum distance one must search before the sheer distance makes the influence from any data point irrelevant. 
   The radius helper function follows on the fact that summed weights should decrease with distance. It will rely on an exponential decay function w = a*b^x, where x <1 and b represents distance. The max radius will be the radius that the function will have an insignificant amount of impact on the surroundings, typically when w is less than a calculated value that it's nearly impossible to tell from background noise. W is dependent on the type of data that we input. 
#### 2. 
   The KDTree class should remain similar to the one found in MP_Mosaics, with slight modifications. Each node struc should include a pointer to its left and right children, a n-dimentional point, and a int population to help "weigh" the data. This KDTree should include all datapoints present within the initial CSV file as points and coordinates. The partition, NearestNeighbor, quickSelect, and shouldReplace methods are key functions within the KDTree, as they are necessary for building and maintaining the tree itself. However, one additional function is necessary for the operations of the heatmap, which is the RadiusNeighbors. This function is similar to NearestNeighbor but it runs multiple times, adding all the nearest neighbors within a set distance of itself. As soon as the NearestNeighbors neighbor that isn't already added is outside of the maximum prescribed radius, the function ends. RadiusNeighbors will return a vector of all nodes which are less than K distance away from the area. 
#### 3. 
   The key function that lets the heatmap function is the findWeight O(n) function, which takes in a coordinate value and returns the resulting weight for it. The weight of the coordinate value will be the sum of all weights from all the points less than the radius distance from the initial coordinate value (utilizing radiusNeighbors). Calculation for a single point should be the same as the radius weight function, w = a*b^x. The weight function will output a double value. 
#### 4. 
   The image algorithm will involve an ImageTraversal O(n), utlizing a BFS to color in all spots within the prescribed map. As all the points on the map should be given an weight value, the BFS Image Traversal should map out all values within the borders of the prescribed map. 
   The BFS methods should input the blank PNG and output the PNG with the heatmap overlain on it. 
#### 5. 
   Implement a "hotspot" O(1)method to identify areas with higher population density, this function will take in a coordinate and then determine if the coordinate is hotter than its surroundings by checking the coordinates directly surrounding it, if the node is 10% hotter than the average of its surroudings it is counted as a hotspot. The hotspot should output a boolean. 
#### 6. 
   Implement Prim's algorithm O(Elog(V)) through a method called minPower, finding the minimum amount of power cables necessary to connect all hotspots. The algorithm will take in a vector of all hotspots and return a weighted undirected graph, with the weight of each graph edge being the Euclidean distance between the two coordinates that it connects.
#### 7. 
   Generate a visualization for Prim's algorithm through representing each connection of the graph as a single line on the resultant PNG. Run a BFS (O(V+E)) on a generated graph
  
  
     
## Expected Challenges and Obstacles


#### A. Visual Design Choices- 

To be effective at its intended purpose, a heat-map must be both visually appealing, easy to understand, and accurate. 

One primary challenge will be deciding how we choose to represent information on the map to ensure these qualities are met. 

This includes determining colors, potential color gradients, the geographical area represented by data-points, and more. 

This may require additional research and use of existing reference material.

Trial and error will most likely be necessary, as these design choices are more subjective than logistical ones. 


#### B. Time and Resource Efficiency- 

Since this dataset requires both image processing and analysis of large datasets, maintaining time and memory efficiency will be both essential and difficult.    

We will need to use at least one image traversal, if not multiple, which run in O(n) time. 

Furthermore, analyzing the dataset will probably require the building of a data-structure and traversing it as well. 

Finally, the specific search algorithims we are using to run our heat-map analysis are very time intensive.

We must take care to eliminate as many inefficiences as possible, especially since we are desining the tool to work with large datasets.



#### C. Incorporating Modularity-

Ideally, the heat-map tool will be able to process as many IL-based datasets as possible, regardless of size and specificity. 

For instance, some datasets might include 100 data points, while others might include up to multiple thousand. Some datasets might be centered around placing datapoints in counties, while others might be more interested in terms of incorporated towns. 

We plan to design our heat-map tool to be able to accept datasets regardless of these discrepancies, as long as they have valid lat/long values, and be able to merge them as well. 

Designing our data-analysis method to be able to account for these differences and still generate a sufficient heat-map across all scenarios will add an additional layer of depth and complexity to our project. 

We expect that there will be bugs that originate from usage of vastly differing datasets, and plan to address them as they arise. 

#### D. Implementation for Part 2 and 3-
Potential difficulty in implementing Prim's Algorithm due to the novelty. 

## Milestones

### I. Data Acquisition (11/7 - 11/13)

A. Aqcuire and process datasets.

### II. Heatmap development (11/18 - 11/26)

A. Finish basic heat-map generation functionality

B. Develop algorithms to evaluate point surrounding density, integrate a weight-centric calculation to visualize an accurate localized density. 

C. By the midpoint check-in we intend to be able to generate a rudimentary heat-map using a single dataset. If we make good progress, we might also have work done on finding      "hotspots".


### III. Implement modular features and graph building functionality (11/26 - Fin)

A. Integrate Prim's algorithm to build graphs between any two points. 

B. Implement visualization functionality for heat-map analysis.

C. Finish presentation and recording.
