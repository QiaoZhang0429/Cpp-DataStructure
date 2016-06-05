#include <iostream>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;

int main(int argc, char* argv[]){

  ifstream in;
  ofstream out;
  vector<int> freqs;
  BitInputStream bitIn(in);

  //Check for Arguments
  if(argc != 3){
    cout << "Invalid number of arguments.\n" 
         << "Usage: ./compress <input filename> <output filename>.\n";
    return -1;
  }

  //Open input file  
  in.open(argv[1], ios::binary);
  if(!in.is_open()){
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }
  in.seekg(0, ios_base::end); //check for empty file
  unsigned int len = in.tellg();
  if(len==0){
    cout << "The file is empty. \n";
    return -1;
  }
  in.seekg(0, ios_base::beg); 

  //read file header
  int symbolNum = bitIn.readInt();
  for(int i = 0; i < 256; i++){
    freqs.push_back(bitIn.readInt());
  }
  //for(int i = 0; i < 256; i++)
  //  cout<<i<<" "<<freqs[i]<<endl;
  //cout<<"***"<<endl;

  //reconstruct Huffman coding tree
  HCTree h;
  h.build(freqs);
  //cout<<"***"<<endl;
  //h.printTree();
  //cout<<"***"<<endl;

  //open output file
  out.open(argv[2], ios::binary);
  if(!out.is_open()){
    cout<< "Invalid output file. No file was opened. Please try again.\n";
    return -1;
  }

  //decode the bits from the input file into the appropriate sequence of bytes
  //write to output file
  int curSymbolNum = 0;
  int sym;
  while(curSymbolNum < symbolNum){
    sym = h.decode(bitIn);
    out.put((byte)sym);
    curSymbolNum += 1;
  }
  //cout<<"***"<<endl;

  //close the files
  in.close();
  out.close();

  return 0;
}
