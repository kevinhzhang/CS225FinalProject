# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o heatmap.o png.o
    $(CC) $(CFLAGS) -o main main.o heatmap.o png.o mapgraph.o
 
# The main.o target can be written more simply
 
main.o: main.cpp Heatmap.cpp Heatmap.h cs225/PNG.cpp cs225/PNG.h MapGraph.h
    $(CC) $(CFLAGS) -c main.cpp 
 
heatmap.o: Heatmap.cpp Heatmap.h

png.o: cs225/PNG.cpp cs225/PNG.h

mapgraph.o: MapGraph.cpp MapGraph.h
 
