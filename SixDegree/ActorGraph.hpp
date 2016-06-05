/*
 * ActorGraph.hpp
 * Author: Qiao Zhang
 * Date: 03/06/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include "Node.hpp"
#include "Edge.hpp"
#include "Movie.hpp"
#include "UnionFind.hpp"

using namespace std;

class ActorGraph {
protected:
  
  bool isWeighted;
  unordered_map<string, Node*> actors;
  unordered_map<string, Movie*> movies;
  map<string, Movie*> ordered_movies;

public:
  /* constructor */
  ActorGraph(void);

  /* deconstructor */
  ~ActorGraph();

  /* initialize an empty graph to be explored */
  void init();

  /* add an edge to graph according to each line from file */
  void insertGraph(string actor_name, string movie_title, int movie_year);

  /* add an edge between two specific nodes 
   * update edge with newer movie
   */
  void updateEdge(Node* from, Node* to, Movie* mov);

  /* add an edge between two specific nodes 
   * update edge with older movie
   */
  void updateEdgeconnect(Node* from, Node* to, Movie* mov);

  /* run BFS from source */
  void BFS(string from, string to);

  /* find the shortest path from source to sink
   * update the dist within the graph
   */
  void Dijkstra(string from, string to);

  /* print path from source to sink according to dist updated in the graph */
  void printPath(string from, string to, ofstream& out);

  /* search the directly connected actors of a target actor */
  void searchTarget(string target, ofstream& out);

  /* BFS used for check the connectivity between two actors */
  int BFSconnect(string fromActor, string toActor);

  /* BFS used for check the connectivity between two actors */
  bool BFSconnectCore(string from, string to);

  /* disjoint set method used for check the connectivity between two actors */
  int UFconnect(string fromActor, string toActor);
  
  /* Load the graph from a tab-delimited file of actor->movie relationships */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);

  /* Load the graph from a tab-delimited file of actor->movie relationships without adding edges */
  bool loadEmptyFromFile(const char* in_filename);
  
};


#endif // ACTORGRAPH_HPP