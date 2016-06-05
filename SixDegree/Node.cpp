/*
 * Node.cpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include "Node.hpp"

Node::Node(){}

Node::Node(string s, int d){
  name = s;
  dist = d;
  visited = false;
  prev = NULL;
}

Node::~Node(){
  for(auto it = adj.begin(); it != adj.end(); it++){
  	delete it->second;
  }
}

void Node::init(){
  prev = NULL;
  dist = INT_MAX;
  visited = false;
}