/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "PointTraversal.h"


using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of PointTraversals on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, PointTraversal> {
  public:
    Iterator();
    
    Iterator & operator++();
    PointTraversal operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/
    Iterator(PNG & png, ImageTraversal * t, PointTraversal & start, double tolerance);
   

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    PointTraversal current;
    ImageTraversal * t;
    PNG image;
    PointTraversal start_;
    double tolerance_;


  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new PointTraversal to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const PointTraversal & t) = 0;
  /**
   * Remove and return the next PointTraversal of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual PointTraversal pop() = 0;
  /**
   * Return but not remove the next PointTraversal of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual PointTraversal peek() const = 0;
  /**
   * To see if the traversal has no PointTraversals left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  virtual bool isVisited(PointTraversal p) = 0;

  virtual HSLAPixel convert(PointTraversal p) = 0;

  virtual void markVisited(PointTraversal p) = 0;

  private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  

 };
