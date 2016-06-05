#include "HCTree.hpp"
#include <sstream>

HCTree::~HCTree(){
    deleteAll(root);
}

void HCTree::deleteAll(HCNode* root){
    if(root == 0) return ;
    else{
      deleteAll(root->c0);
      deleteAll(root->c1);
      delete root;
      root = 0;
    }
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){

    std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* p1;
    HCNode* p2;
    HCNode* newNode;
    //cout<<"***"<<endl;

    for(int i = 0; i < freqs.size(); i++){
        if(freqs[i] > 0){
            //cout<<i<<" "<<freqs[i]<<endl;
            newNode = new HCNode(freqs[i], (byte)i);
            leaves[i] = newNode;
            pq.push(newNode);
        }
    }

    while(pq.size() > 1){
        p1 = pq.top();
        pq.pop();
        p2 = pq.top();        
        pq.pop();
        newNode = new HCNode(p1->count+p2->count, p1->symbol, p1, p2);
        p1->p = newNode;
        p2->p = newNode;
        pq.push(newNode);
    }

    root = pq.top();
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const{
    HCNode* ptr = leaves[(int)symbol];
    std::string buffer = "";
    if(ptr->count == 0)
        return ;
    if(ptr == root){
        out<<"0";
        return ;
    }
    while(ptr->p){
        if(ptr->p->c0 == ptr)
            buffer = "0" + buffer;
        else if(ptr->p->c1 == ptr)
            buffer = "1" + buffer;
        ptr = ptr->p;
    }
    out<<buffer;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const{
    HCNode* ptr = root;
    char buffer;
    while(ptr->c0 && ptr->c1){
        if(in.peek() == '\n'){
            in.seekg(1, ios_base::cur);
            return -2;
        }
        in>>buffer;
        if(in.eof())
            return -1;        
        if(buffer == '0')
            ptr = ptr->c0;
        else if(buffer == '1')
            ptr = ptr->c1;
        else
            return -1;
    }
    return (int)ptr->symbol;
}
/*
void HCTree::printCode() const{
    for(int i = 0; i < 256; i++){
        if(leaves[i]->count){
            std::cout<<leaves[i]->symbol;
        }
    }   
}*/

/* Used for debug */
void HCTree::printSubTree(HCNode* node) {
    if(node == NULL)
        return ;
    std::cout << *node << std::endl;
    if(node->c0) {
        printSubTree(node->c0);
    } 
    if(node->c1) {
        printSubTree(node->c1);
    }
}
void HCTree::printTree() {
    if(root) {
        printSubTree(root);
    }
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
 
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* ptr = leaves[(int)symbol];
    std::string buffer = "";
    std::stringstream ss;
    int int_buffer;
    if(ptr->count == 0)
        return ;
    if(ptr == root){
        out.writeBit(0);
        return ;
    }
    while(ptr->p){
        if(ptr->p->c0 == ptr)
            buffer = "0" + buffer;
        else if(ptr->p->c1 == ptr)
            buffer = "1" + buffer;
        ptr = ptr->p;
    }
    for(int i = 0; i < buffer.length(); i++){
        //cout<<i<<" "<<buffer[i]<<endl;
        ss.clear();
        ss.str("");
        ss<<buffer[i];
        ss>>int_buffer;
        if(int_buffer == 0)
            out.writeBit(0);
        else if(int_buffer == 1)
            out.writeBit(1);
        else
            std::cout<< "Warning: encoding might be wrong! \n";
    }
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
 
int HCTree::decode(BitInputStream& in) const{
    HCNode* ptr = root;
    int buffer;
    while(ptr->c0 && ptr->c1){
        if(in.eof())
            return -1;
        buffer = in.readBit();
        if(buffer == 0)
            ptr = ptr->c0;
        else if(buffer == 1)
            ptr = ptr->c1;
        else
            return -1;
    }
    return (int)ptr->symbol;
}
