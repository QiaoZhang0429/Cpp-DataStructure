/**
 * UnionFind.hpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "ActorGraph.hpp"

/* UnionFind: help implement the disjoint set
 */
class UnionFind{
private:
  unordered_map<string, Node*> dSet;
  int size;

public:
  /* constructor */
  UnionFind(unordered_map<string, Node*>& s) : dSet(s) {
    size = dSet.size();
  };
  
  /* find the root of the up-tree a belongs to */
  Node* find(Node* a);
  
  /* merge two nodes into one cluster */
  void merge(Node* a1, Node* a2);
  
  /* return the number of independent set */
  int numOfSets();
  
  /* return whether the node is not connected with any others*/
  bool isSingleNodeSet(Node* a);
  
};

#endif // UNIONFIND_HPP

