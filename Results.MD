# Final Report and Results

## Conclusions 

Ultimately, we felt that we were able to achieve both the primary goals established within our proposal with profound success.

We implemented both the Heat Map visualization functionality and MST generation functionality, and ensured both worked as intended with a rigorous testing suite. This testing suite can be reproduced and ran based on the instructions in the README.MD file. The outputs of both our functionalities fit the description of the desired outputs we initially established at the outset of the project in our proposal. 

We decided to include an additional visualization functionality to integrate with our heatmap, which took the MST generated from part two and displayed the “hotspots” as pink squares, hotspots being the 15 points in the MST with the highest node degree.

These functionalities run on the biggest valid dataset we have available to us, and run in a reasonable time given the large size of the image we are using. (It is 3096 x 3096 resolution).

This functionaltiy is all encompassed in the final executable, which is located in main and can be run by following the instructions described in the README.MD. 

Our code ultimately utilizes:

A BFS image traversal,
a BFS graph traversal,
a Bucketing Algorithim,
a full implementation of a graph class,
an implementation of Prim's Algorithim,
two data visualization algorithims,
and many helper functions.

To achieve the data processing and visualization capabilities we initially set out to implement when drafting the proposal for this project.

These are screenshots of the ultimate outputs of our executable (to run it follow the instructions described in the READM.MD):
![image](https://media.github-dev.cs.illinois.edu/user/13122/files/b7f714f2-fc54-4b77-873b-feb384ddc2be)
![image](https://media.github-dev.cs.illinois.edu/user/13122/files/a9d51700-816d-4fad-8890-c821481f7262)

For comparison, this is a screenshot of the initial blank base image, before being inputted into our algorithims:
![image](https://media.github-dev.cs.illinois.edu/user/13122/files/2681ddcc-0854-42d0-af7e-3526375137f3)

This is a screenshot of the output of our test cases (to run them follow the instructions described in the README.MD):

![image](https://media.github-dev.cs.illinois.edu/user/13122/files/04687cb3-5047-47a2-9801-00ce3f3cb19b)

This is a screenshot of the runtime of our executable:

![image](https://media.github-dev.cs.illinois.edu/user/13122/files/a6d04c58-d5ca-4b8f-a563-59678dbccf23)

## Development Discoveries

The Heat Map visualization functionality turned out to be the most unexpectedly challenging aspect of our project. There were several factors that we failed to consider when we initially planned our implementation.

Initially, we planned to traverse every data point and color nearby cells accordingly. However we realized that a more accurate and time-conserving method would be to traverse every cell and color it based upon nearby data points. This was one core functionality we decided to change.

Furthermore, one major sticking point that severely impeded us was the fact that we had to translate geographic latitude-longitude information into distances in miles and into xy coordinates in terms of the actual PNG image. This required a lot of helper functions and mathematical calculations, and somewhat reduced the accuracy of our visualization, but not to a significant amount.

Finally, we initially planned to use a KDTree to locate all the relevant data points within relevant proximity of each cell, but this reduced runtime too severely, so we eventually chose to replace it with a Bucketing function instead.

Overall, our MST generation and Graph traversal implementations did not encounter as many significant challenges as the Heat Map generation.

The most significant point of confusion was making judgement calls and design decisions to translate the abstract Graph implementation into a functional codebase that integrated smoothly with what we had already written. For instance, we decided to go with an adjacency list implementation but we ended up not including an additional edge list as some implementations recommended because it would further complicate our code and we didn’t really need it. For these same reasons we did not include a removeVertex() or a removeEdge() functionality.

Also, since the graph implementation was more general, we spent a lot of time writing many test cases to ensure that everything in the graph implementation was working exactly as expected. 

More general lessons we learned from this project include the importance of good organization and communication. Since we were all independently working on very complex but interconnected parts of the project, not commenting and documenting our technical specifications as we went along slowed us down a lot. 

