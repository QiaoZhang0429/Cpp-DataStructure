/**
 * UnionFind.cpp
 * Author: Qiao Zhang
 * Date: 03/07/2016
 */
#include <cstdlib>
#include "UnionFind.hpp"

using namespace std;

Node* UnionFind::find(Node* a){
  if(!a->prev) 
    return a;
  Node* curr = a;
  while(curr->prev){
    curr = curr->prev;
  }
  a->prev = curr; //path compression
  return curr;
}

void UnionFind::merge(Node* a1, Node* a2){
  Node* root1 = find(a1);
  Node* root2 = find(a2);
  if(root1 == root2) 
    return ; 
  root2->prev = root1;
  /*
  if(abs(root1->dist) > abs(root2->dist)){
    root2->prev = root1;
    root1->dist += root2->dist;
  } 
  else{
    root1->prev = root2;
    root2->dist += root1->dist;
  }
  */
  size -= 1;
}

int UnionFind::numOfSets(){
  return size;
}

bool UnionFind::isSingleNodeSet(Node* a){
  return a->prev == 0;
}