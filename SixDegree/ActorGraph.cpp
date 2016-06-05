/*
 * ActorGraph.cpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include "ActorGraph.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}

ActorGraph::~ActorGraph() {
  for(auto it = actors.begin(); it != actors.end(); it++){
    delete it->second;
  }
  for(auto it = movies.begin(); it != movies.end(); it++){
    delete it->second;
  }
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){
  
  // Initialize the file stream
  ifstream infile(in_filename);
  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile){
    string s;   
    // get the next line
    if (!getline( infile, s )) break;    
    if (!have_header){
      // skip the header
      have_header = true;
      continue;
    }
    istringstream ss( s );
    vector <string> record;
    while (ss){
      string next;      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;      
      record.push_back( next );
    }    
    if (record.size() != 3){
      continue;
    }
    
    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);    
    insertGraph(actor_name, movie_title, movie_year);
  }
  
  if (!infile.eof()) {
    cout << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();  
  return true;

}

bool ActorGraph::loadEmptyFromFile(const char* in_filename){
  
  // Initialize the file stream
  ifstream infile(in_filename);
  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile){
    string s;   
    // get the next line
    if (!getline( infile, s )) break;    
    if (!have_header){
      // skip the header
      have_header = true;
      continue;
    }
    istringstream ss( s );
    vector <string> record;
    while (ss){
      string next;      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;      
      record.push_back( next );
    }    
    if (record.size() != 3){
      continue;
    }
    
    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]); 

    if(actors.find(actor_name) == actors.end()){
      Node* v = new Node(actor_name, -1);
      actors[actor_name] = v;
    }   

    if(ordered_movies.find(to_string(movie_year) + movie_title) == ordered_movies.end()){
      Movie* m = new Movie(movie_title, movie_year);
      ordered_movies[to_string(movie_year) + movie_title] = m;
    }

    ordered_movies[to_string(movie_year) + movie_title]->crew.push_back(actors[actor_name]);

  }
  
  /*
  for(auto it = actors.begin(); it != actors.end(); it++){
    cout << it->first << " " << it->second << endl;
  }

  for(auto it = ordered_movies.begin(); it != ordered_movies.end(); it++){
    cout << it->first << " " << it->second << endl;
  }
  */

  if (!infile.eof()) {
    cout << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();  
  return true;

}

void ActorGraph::insertGraph(string actor_name, string movie_title, int movie_year){
  if(actors.find(actor_name) == actors.end()){
    Node* v = new Node(actor_name, -1);
    actors[actor_name] = v;
  }
  Node* currActor = actors[actor_name];
  if(movies.find(movie_title) == movies.end()){
    Movie* m = new Movie(movie_title, movie_year);
    movies[movie_title] = m;
  }
  Movie* currMovie = movies[movie_title];
  for(auto it = currMovie->crew.begin(); it != currMovie->crew.end(); it++){
    updateEdge(currActor, *it, currMovie);
    updateEdge(*it, currActor, currMovie);
  }
  currMovie->crew.push_back(currActor);
}

void ActorGraph::updateEdge(Node* from, Node* to, Movie* mov){
  if(from->adj.find(from->name + to->name) == from->adj.end()){
    Edge* e = new Edge(from, to, mov);
    from->adj[from->name + to->name] = e;
  }
  Edge* currEdge = from->adj[from->name + to->name];
  if(currEdge->movie->year < mov->year)
    currEdge->movie = mov;
}

void ActorGraph::updateEdgeconnect(Node* from, Node* to, Movie* mov){
  if(from->adj.find(from->name + to->name) == from->adj.end()){
    Edge* e = new Edge(from, to, mov);
    from->adj[from->name + to->name] = e;
  }
  Edge* currEdge = from->adj[from->name + to->name];
  if(currEdge->movie->year > mov->year)
    currEdge->movie = mov;
}

void ActorGraph::init(){
  for(auto it = actors.begin(); it != actors.end(); it++)
    it->second->init();
}

void ActorGraph::BFS(string from, string to){
  init();
  Node* start = actors[from];
  start->dist = 0;
  queue<Node*> q;
  q.push(start);
  while(!q.empty()){
    Node* tmp = q.front();
    q.pop();
    for(auto it = tmp->adj.begin(); it != tmp->adj.end(); it++){
      if(it->second->to->dist == INT_MAX){
        it->second->to->dist = tmp->dist + 1;
        it->second->to->prev = tmp;
        q.push(it->second->to);
      }
    }
  }
}

bool ActorGraph::BFSconnectCore(string from, string to){
  init();
  Node* start = actors[from];
  start->dist = 0;
  queue<Node*> q;
  q.push(start);
  while(!q.empty()){
    Node* tmp = q.front();
    q.pop();
    if(tmp->name == to){
      return true;
    }
    for(auto it = tmp->adj.begin(); it != tmp->adj.end(); it++){
      if(it->second->to->dist == INT_MAX){
        it->second->to->dist = tmp->dist + 1;
        it->second->to->prev = tmp;
        q.push(it->second->to);
      }
    }
  }
  return false;
}

void ActorGraph::Dijkstra(string from, string to){
  Node* start = actors[from];
  start->dist = 0;
  priority_queue<Node*, vector<Node*>, NodePtrLess> pq;
  pq.push(start);
  while(!pq.empty()){
    Node* tmp = pq.top();
    pq.pop();
    if(tmp->visited)
      continue;
    tmp->visited = true;
    for(auto it = tmp->adj.begin(); it != tmp->adj.end(); it++){
      if(it->second->to->dist > tmp->dist + it->second->movie->weight){
        it->second->to->dist = tmp->dist + it->second->movie->weight;
        it->second->to->prev = tmp;
        pq.push(it->second->to);
      }
    }
  }
}

void ActorGraph::printPath(string from, string to, ofstream& out){
  stack<Node*> stk;
  Node* curr = actors[to];  
  while(curr->name != from){
    stk.push(curr);
    curr = curr->prev;
  }
  while(!stk.empty()){
    Node* next = stk.top();
    stk.pop();
    Edge* e = curr->adj[curr->name + next->name];
    Movie* m = e->movie;
    out << "(" + curr->name + ")" + "--[" + m->name + "#@" + to_string(m->year) + "]-->";
    curr = next;
  }
  out << "(" + curr->name + ")" << endl;
}

void ActorGraph::searchTarget(string target, ofstream& out){
  out << "Target actor: " << target << endl;
  out << "(actor)--[movie#@year]" << endl;
  if(actors.find(target) == actors.end()){
    out << endl;
    return ;
  }
  Node* n = actors[target];
  for(auto it = n->adj.begin(); it != n->adj.end(); it++){
    out << "(" + it->second->to->name + ")" + "--[" + it->second->movie->name + "#@" + to_string(it->second->movie->year) << endl;
  }
}


int ActorGraph::BFSconnect(string fromActor, string toActor){
  for(auto it = ordered_movies.begin(); it != ordered_movies.end(); it++){
    Movie* m = it->second;
    for(int i = 0; i < m->crew.size(); i++){
      for(int j = i+1; j < m->crew.size(); j++){
        updateEdgeconnect(m->crew[i], m->crew[j], m);
        updateEdgeconnect(m->crew[j], m->crew[i], m);
      }
    }
    if(BFSconnectCore(fromActor, toActor)){
      return m->year;
    }
  }
  return 9999;
}

int ActorGraph::UFconnect(string fromActor, string toActor){
  UnionFind uf(actors);
  for(auto it = ordered_movies.begin(); it != ordered_movies.end(); it++){
    Movie* m = it->second;
    for(int i = 1; i < m->crew.size(); i++){
      uf.merge(m->crew[0], m->crew[i]);
    }
    if(uf.find(actors[fromActor]) == uf.find(actors[toActor])){
      return m->year;
    }
  }
  return 9999;
}