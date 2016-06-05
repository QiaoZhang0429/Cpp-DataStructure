/**
 * actorconnections.cpp
 * Author: Qiao Zhang
 * Date: 03/07/2016
 * Description: This file implement the function of telling the year actor1 and actor2 become connected.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <string.h>
#include <stdio.h>
#include "ActorGraph.hpp"

using namespace std;

/* Timer class: calculate running time of program */
class Timer{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
  void begin_timer();
  long long end_timer();
};
void Timer::begin_timer() {
  start = std::chrono::high_resolution_clock::now();
}
long long Timer::end_timer() {
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  end = std::chrono::high_resolution_clock::now();
  return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
}

int main (int argc, char** argv){

  /* check arguments */
  if (argc < 5) {
    cout << "Usage: ./actorconnections movie_casts.tsv test_pairs.tsv out_actorconnection.tsv bfs/ufind" << endl;
    return -1;
  }
  
  ifstream in(argv[2]); 
  ofstream out(argv[3]);
  //Timer T;
  //long long time_duration;
  
  if(!in.is_open()){
    cout << "Cannot open file " << argv[2] << endl;
    return -1;
  } 
  if(!out.is_open()){
    cout << "Cannot open file " << argv[3] << endl;
    return -1;
  }
  
  //T.begin_timer();

  out << "Actor1\t" << "Actor2\t" << "Year" << endl;
  bool have_header = false;
  while(in){
    string s, fromActor, toActor;
    if(!getline(in, s)) break;
    if(!have_header) {
      have_header = true;
      continue;
    }
    istringstream ss(s);
    getline(ss, fromActor, '\t');
    getline(ss, toActor, '\t');

    /* check the connect year with bfs/union-find method */
    if(strcmp(argv[4], "bfs") == 0){ 
      ActorGraph* ag = new ActorGraph;
      ag->loadEmptyFromFile(argv[1]);
      out << fromActor << "\t" << toActor << "\t" << ag->BFSconnect(fromActor, toActor) << endl; 
      delete ag;
    }
    else{ 
      ActorGraph* ag = new ActorGraph;
      ag->loadEmptyFromFile(argv[1]);
      out << fromActor << "\t" << toActor << "\t" << ag->UFconnect(fromActor, toActor) << endl;
      delete ag;
    }
  }

  //time_duration = T.end_timer();
  //cout << argv[4] << "\t" << time_duration << endl;

  in.close();
  out.close();

  return 0;
}
