#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other){
  if(count != other.count) return count > other.count;
  return symbol < other.symbol;
}

/** Compare the content of two nodes
 *  If it's a tie, compare symbol of node, the larger has a higher priority
 *  If HCNode* other has a higher priority, return true
 */
bool comp(HCNode* one, HCNode* other){
  if(one->count != other->count) return one->count > other->count;
  return one->symbol < other->symbol;
}

