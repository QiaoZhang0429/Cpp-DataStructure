/**
 * pathfinder.cpp
 * Author: Qiao Zhang
 * Date: 03/05/2016
 * Description: This file implement the function of finding a path from one actor to another.
 */

#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <fstream>
#include <sstream>
#include "ActorGraph.hpp"

using namespace std;

int main (int argc, char** argv){

  if (argc < 5) {
    cout << "Usage: ./pathfinder movie_casts.tsv u/w test_pairs.tsv out_paths_(un)weighted.tsv" << endl;
    return -1;
  }
  
  ActorGraph ag;
  ifstream in(argv[3]); 
  ofstream out(argv[4]);
  
  if (!in.is_open()){
    cout << "Cannot open file " << argv[3] << endl;
    return -1;
  } 
  if (!out.is_open()){
    cout << "Cannot open file " << argv[4] << endl;
    return -1;
  }
  
  ag.loadFromFile(argv[1], *argv[2] == 'w');

  out << "(actor)--[movie#@year]-->(actor)--..." << endl;
  bool have_header = false;
  while (in) {

    string s, fromActor, toActor;
    if (!getline(in, s)) break;
    if (!have_header) {
      have_header = true;
      continue;
    }
    istringstream ss(s);
    getline(ss, fromActor, '\t');
    getline(ss, toActor, '\t');

    ag.init();
    if (*argv[2] == 'u') 
      ag.BFS(fromActor, toActor); 
    else 
      ag.Dijkstra(fromActor, toActor);

    ag.printPath(fromActor, toActor, out);

  }

  in.close();
  out.close();

  return 0;
}
