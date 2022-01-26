/**
 * @file PointTraversal.h
 * every 2D PointTraversal of the image is represented by a PointTraversal class
 * you need to trverse all the PointTraversals of the image
 */
#pragma once

#include <iostream>
#include <sstream>

/**
 * Simple PointTraversal class containing a public unsigned `x` and `y` for representing 2D PointTraversals on an image.
 */
struct PointTraversal {
  unsigned x;
  unsigned y;


  /**
   * Default constructor, set the PointTraversalTraversal to (0, 0)
   */
  PointTraversal() : PointTraversal(0, 0) { }


  /**
   * Constructor
   * @param x coordinate of a PointTraversal
   * @param y coordinate of a PointTraversal
   */
  PointTraversal(unsigned x, unsigned y) : x(x), y(y) { }


  /**
   * overload operator <
   * @param other The other PointTraversal
   * @return True for smaller, false for otherwise
   */
  bool operator<(const PointTraversal &other) const {
    return (x < other.x || y < other.y);
  }


  /**
   * overload operator ==
   * @param other The other PointTraversal
   * @return True for smaller, false for otherwise
   */
  bool operator==(const PointTraversal &other) const {
    return (x == other.x && y == other.y);
  }
};

