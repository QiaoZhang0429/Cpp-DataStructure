/*
 * Edge.cpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */
 
#include "Edge.hpp"

Edge::Edge(Node* f, Node* t, Movie* m){
	from = f;
	to = t;
	movie = m;
}

Edge::~Edge(){}