#include "BitOutputStream.hpp"

/** Write the least significant bit of the argument to 
 *  the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i){
  //check i
  if((i != 0) && (i != 1))
    std::cout<<"Warning: the bit is neither 0 nor 1. \n";
  //flush the bit buffer when full
  if(nbits == 8)
    flush();
  //Write the least significant bit of i into the buffer at the current index
  buf |= i << (7-nbits);
  //Increment the index;
  nbits++;
}

void BitOutputStream::writeInt(int num){
  int tmp;
  for(int i = 31; i >= 0; i--){
    tmp = 1 & (num >> i);
    writeBit(tmp);
  }
}

/** Send the buffer to the output, and clear it*/
void BitOutputStream::flush(){
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}