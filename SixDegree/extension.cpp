/**
 * extension.cpp
 * Author: Qiao Zhang
 * Date: 03/07/2016
 * Description: This file implement the extension of telling the directly connected actors of target actor, in other words, level 1 nodes.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "ActorGraph.hpp"

using namespace std;

int main (int argc, char** argv){

  /* check arguments */
  if (argc < 3) {
    cout << "Usage: ./extension movie_casts.tsv target.tsv out_ext.tsv" << endl;
    return -1;
  }
  
  ActorGraph ag;
  ifstream in(argv[2]); 
  ofstream out(argv[3]);
  
  if (!out.is_open()){
    cout << "Cannot open file " << argv[4] << endl;
    return -1;
  }

  ag.loadFromFile(argv[1], 'w');

  bool have_header = false;
  while(in){
    string s;
    if(!getline(in, s)) break;
    if(!have_header) {
      have_header = true;
      continue;
    }
    ag.searchTarget(s, out);
  }
  
  in.close();  
  out.close();

  return 0;
}