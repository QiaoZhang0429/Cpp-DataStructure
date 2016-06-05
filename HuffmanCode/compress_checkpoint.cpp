//Qiao Zhang

#include <iostream>
#include <vector>
#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;

typedef unsigned char byte;

int main(int argc, char* argv[]){
//int main(){

  //int argc = 3;
  //char* argv[] = {"./compress", "/Users/zq/repo_st_632_3786_10674_pa2_huffman/input.dat", "/Users/zq/repo_st_632_3786_10674_pa2_huffman/output.dat"};

  byte newByte;
  ifstream in;
  ofstream out;
  vector<int> freqs;

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

  //read bytes from input file
  //count the occurences of each byte
  for(int i = 0; i < 256; i++){
    freqs.push_back(0);
  }
  while(!in.eof()){
    in>>newByte;
    if(in.eof()) break;
    if(((int)newByte >= 0) && ((int)newByte < 256))
      freqs[(int)newByte] += 1;
    else
      cout<<"Error reading unsigned char from input file. \n";
  } 

  //close the input file
  in.close();

  //construct a Huffman coding tree
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

  //write file header
  for(int i = 0; i < freqs.size(); i++){
    out<<freqs[i]<<endl;
  }

  //Open input file again
  in.open(argv[1], ios::binary);
  if(!in.is_open()){
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }

  //translate each byte from the input file into its code
  while(!in.eof()){
    if(in.peek() == '\n')
      out<<endl;
    in>>newByte;
    if(in.eof()) break;
    //cout<<newByte<<" "<<(int)newByte<<endl;
    if(((int)newByte >= 0) && ((int)newByte < 256))
      h.encode(newByte, out);
    else
      cout<<"Error reading unsigned char from input file. \n";
  }
  //cout<<"***"<<endl;

  //close the files
  in.close();
  out.close();

  return 0;
}
