//Qiao Zhang

#include <iostream>
#include <vector>
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

typedef unsigned char byte;

int main(int argc, char* argv[]){

  byte newByte;
  ifstream in;
  ofstream out;
  BitOutputStream bitOut(out);
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
  int symbolNum = 0;
  for(int i = 0; i < 256; i++){
    freqs.push_back(0);
  }
  while(!in.eof()){
    newByte = (byte)in.get();
    if(in.eof()) break;
    symbolNum += 1;
    if(((int)newByte >= 0) && ((int)newByte < 256))
      freqs[(int)newByte] += 1;
    else
      cout<<"Error reading unsigned char from input file. \n";
  }   
  //cout<<"***"<<endl;

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
  bitOut.writeInt(symbolNum);
  for(int i = 0; i < freqs.size(); i++){
    bitOut.writeInt(freqs[i]);
  }
  //cout<<"***"<<endl;

  //Open input file again
  in.open(argv[1], ios::binary);
  if(!in.is_open()){
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }

  //translate each byte from the input file into its code
  while(!in.eof()){
    //if(in.peek() == '\n')
    //  out<<endl;
    //in>>newByte;
    newByte = (byte)in.get();
    if(in.eof()) break;
    if(((int)newByte >= 0) && ((int)newByte < 256))
      h.encode(newByte, bitOut);
    else
      cout<<"Error reading unsigned char from input file. \n";
  }
  bitOut.flush();
  //cout<<"***"<<endl;
/*
  newByte = (byte)in.get();
  while(!in.eof()){
    cout<<newByte<<endl;
    //if(((int)newByte >= 0) && ((int)newByte < 256))
    //  h.encode(newByte, bitOut);
    //else
    //  cout<<"Error reading unsigned char from input file. \n";
    newByte = (byte)in.get();
  }
  bitOut.flush();
  cout<<"***"<<endl;*/

  //close the files
  in.close();
  out.close();

  return 0;
}
