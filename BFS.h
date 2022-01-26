/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>

#include "cs225/PNG.h"
#include "PointTraversal.h"
#include "cs225/HSLAPixel.h"


#include "ImageTraversal.h"

using namespace cs225;
using namespace std;
/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const PointTraversal & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const PointTraversal & PointTraversal);
  PointTraversal pop();
  PointTraversal peek() const;
  bool empty() const;
  unsigned getHeight();
  unsigned getWidth();
  double getTolerance();
  PointTraversal getStart();
  HSLAPixel convert(PointTraversal p);
  bool isVisited(PointTraversal pnt);
  void markVisited(PointTraversal p);

private:
  /** @todo [Part 1] */
  /** add private members here*/
    PNG image;
    PointTraversal current;  
    PointTraversal start_;
    double tolerance_;
    queue<PointTraversal> q;
    vector<vector<bool>> visits;
    
};
