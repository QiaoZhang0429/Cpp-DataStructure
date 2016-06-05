/*
 * Node.hpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <climits>
#include "Movie.hpp"

using namespace std;

/* Node: node in the ActorGraph
 * Function: represent actor 
 */
class Node {
public:

  string name;
  unordered_map<string, Edge*> adj;
  int dist;
  Node* prev;
  bool visited;

  /* constructor */
  Node();
  Node(string s, int d);

  /* deconstructor */
  ~Node();

  /* initialize arguments within each node
   * dist = INT_MAX, prev = 0
   */
  void init();

  /* ovverwrite operator less than to get min heap */
  bool operator<(const Node& other){
    return dist > other.dist;
  }
  
};

/* class used for comparing elements within a priority queue*/
class NodePtrLess{
public:
  bool operator()(Node* const & lhs, Node* const & rhs) const{
    return *lhs < *rhs;
  }
};


#endif // NODE_HPP