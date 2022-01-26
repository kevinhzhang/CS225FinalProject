# FP0: Heinous Heatmaps

### Final Project for Phillip Hu, Franklyn Wu, and Kevin Zhang

This is a basic overview of our final project, which contains two main functionalities:

#### Part 1: Implement a data visualization method capable of taking a series of geographical points associated with some quantifiable metric as input and producing a “Heat Map” PNG as output with a reasonable runtime.

#### Part 2: Implement a graph structure and processing algorithm capable of identifying the most efficient way to travel between points by taking a graph as input and generating an MST as output

Both these functionalities are fully implemented and tested. We aimed to implement these functionalities to help process large datasets into outputs that could be easy to educate with and understand. We hope that our project can be used to better communicate geographical data in a variety of settings. 

## Executable: 

Our final deliverable is written in the main.cpp file and utilizes all of our written code. It is run directly from the repository.

#### To run the executable, enter the following commands chronologically in terminal:

make

./fp

### Executable Description:

The inputs taken by this executable are the files "FULLSET.csv", "ILMAP.png", and "ILMAP2.png". All three of these inputs can be changed to produce different results. However, if you change "ILMAP.png" and "ILMAP2.png" from the files we have already included, the executable will not produce an accurate visualization or may fail entirely. "FULLSET.csv" however, can be changed without comprising the functionality of the executable. 

"FULLSET.csv" must follow this format: A geographical latitudes values in the form of a double stored in column 7, geographical longitude values in the form of a double stored in column 8, and a quantiative metric in column 3 in the form of an int. These valuse CANNOT contain commas. 

If your csv dataset does not fulfill these requirements but does contain an address and a quantifiable metric, we have included data cleaning scripts in the file "Detailed_Proposal/Data_Processing_Procedure.md" that may help make your csv file valid. Also, it's important to note that if the input files are moved to other directories the code will no longer run. 

You can also change the files being input by going into main.cpp and changing all references to "FULLSET.csv" to your desired CSV file. However, we recommend simply renaming the two files so that your file is named "FULLSET.csv" and the original file is named something else.

The results will be written to the files "Fullmap.png" and "FullmapWithHotspots.png". Based on our own runs of the executable, this entire process should take less than 1.5 minutes. 

"Fullmap.png" will be an image of a heatmap displaying population density over the geographical area of the state of Illinois, with colors closer to purple indicating a lower population and colors closer to yellow indicating a higher population. Our color gradient is based on the "Viridis" color scheme which is intended to make the heat maps easier to interpret for color-blind indviduals.

"FullmapWithHotspots.png" will be the same heatmap except with "Hotspots" pinpointed using pink squares. Hotspots are defined as the 15 locations with the highest node degree in our generated mininum spanning tree. These points are essentially "hubs" in a shortest-distance traversal of all the geographical points in the dataset. We decided to include this extra visualization to integrate our mininum spanning tree functionality with our heatmap functionality. 

## Content Glossary:

##### In this project, the following files are our original code and used in the implementation of our final functionality:

Bucket.cpp,
Bucket.h,
GraphBFS.cpp,
GraphBFS.h,
Heatmap.cpp,
Heatmap.h,
MapGraph.cpp,
MapGraph.h,
PointTraversal.cpp,
PointTraversal.h,
main.cpp


##### We also used the following files from MP_Mosaics and MP_Traversals:

ImageTraversal.cpp,
ImageTraversal.h,
point.cpp,
point.h,
BFS.cpp,
BFS.h,
cs225 (directory)


##### Finally, we have written human-readable .MD files explaining our planning, development, and final report in the following files:

Development_Log (directory),
Detailed_Proposal (directory),
Team_Contracts (directory),
README.MD (this),
Final_Project_Presentation.MD,
Results.MD

There is also the Datasets directory, which contains csv files currently unused by our final deliverable. These were used during the development process, and may be used in further expansions of this project in the future. The data in these datasets are not fully cleaned.

#### The final written report as required for the project are located in the following files:

Goals: "Detailed_Proposal/CS 225_Project_Overview.MD"

Development: Development_Log (directory)

Results: "Results.MD"

#### The final presentation is located in the file "Final_Project_Presentation.MD.

## Testing and Verification:

Our implementation is tested via the test suites in the tests directory, all of which were written by us. They are run directly from the repository.

#### To run the full test suite, enter the following commands chronologically in terminal:

make test

./test

### Test Suite Description:

tests_part1.cpp - tests heatmap.h and all related functionalities, excluding the prim's algorithim. This test suite covers all visualizaiton capabilities

tests_part2.cpp - tests MapGraph.h and all related functionalities. This test suite makes sure the graph class works exactly as intended so it can be used in the mininum spanning tree generation

testsBFS.cpp - tests GraphBFS.h. This test ensures the graph traversal can be used to verify the MST generated by PrimMST()

testsPrim.cpp - tests functionalities for the PrimMST() function in heatmap.h. This test suite covers all MST generation capabilities

There are more detailed descriptions of each individual test case within the files themselves.

Please note that all CSV files included in the testing directory are necessary for the test cases to successfully complete. Based upon our own runs of the test cases, the full test suite should take less than three minutes to run. 

Finally, the test suite generates two png images and writes them to the files "ILMAP-changed.png" and "TestMap.png". These files were used for verification of the visualization implementations. 

## Future Applications:

There are several ways you could improve upon our implementation if given a longer timeframe. 

One feature that would be high priority is making the visualization functionality more modular to accept a wider range of datasets and maps. Right now, ouar implementation only works for datasets located in Illinois, and only for the specific base imge that we chose. However, given more time, we believe we could modify our code to accept data from other maps set in other states. 

Also, with more time we could implement more thorough visualizations of the MST, such as connecting all the “hotspots” with lines.

Finally, one mathematically tweak the sizing function to be even more accurate, as changing the spherical lat-long data into a xy coordinates on a flat plane inherently requires some approximation which reduces precision and accuracy.

### Credits:

Franklyn Wu - Contributor

Kevin Zhang - Contributor

Phillip Hu - Contributor 

Kendall Koe - Instructor/Mentor 

Code was also used from various CS225 MPs as described above, which were designed by the CS225 course staff.

### License:

GNU GPLv3
