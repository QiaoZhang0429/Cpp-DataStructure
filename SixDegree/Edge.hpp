/*
 * Edge.hpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */

#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <string>

class Node;

class Movie;

class Edge {

public: 

  Node* from;
  Node* to;
  Movie* movie;

  /* constructor */
  Edge(Node* f, Node* t, Movie* m);

  /* deconstructor */
  ~Edge();
  
};


#endif // EDGE_HPP