#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "PointTraversal.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;


/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start PointTraversal of this BFS
 * @param tolerance If the current PointTraversal is too different (difference larger than tolerance) with the start PointTraversal,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const PointTraversal & start, double tolerance) {  
  /** @todo [Part 1] */
  image = png;
  current = start;
  start_ = start;
  tolerance_ = tolerance;
  //visited.push_back(current);
  const size_t x = image.width();
  const size_t y = image.height();
  visits.resize(image.height(), vector<bool>(image.width()));
  visits[start.y][start.x] = true;
  q.push(current);
}

/**
 * Returns an iterator for the traversal starting at the first PointTraversal.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(image, this, start_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a PointTraversal for the traversal to visit at some PointTraversal in the future.
 */
void BFS::add(const PointTraversal & PointTraversal) {
  /** @todo [Part 1] */
  q.push(PointTraversal);
}

/**
 * Removes and returns the current PointTraversal in the traversal.
 */
PointTraversal BFS::pop() {
  /** @todo [Part 1] */
  PointTraversal toReturn = q.front();
  q.pop();
  return toReturn;
}

/**
 * Returns the current PointTraversal in the traversal.
 */
PointTraversal BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}
unsigned BFS::getWidth(){
  return image.width();
}
unsigned BFS::getHeight(){
  return image.height();
}
double BFS::getTolerance(){
  return tolerance_;
}
PointTraversal BFS::getStart(){
  return start_;
}
HSLAPixel BFS::convert(PointTraversal p){
  HSLAPixel result = image.getPixel(p.x,p.y);
  return result;
}
bool BFS::isVisited(PointTraversal pnt){
  return visits[pnt.y][pnt.x];
}
void BFS::markVisited(PointTraversal p){
  visits[p.y][p.x] = true;
}