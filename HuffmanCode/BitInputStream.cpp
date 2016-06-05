#include "BitInputStream.hpp"

/** Read the next bit from the bit buffer.
 *  Fill the buffer form the input stream first if needed
 *  Return 1 if the bit read is 1
 *  Return 0 if the bit read is 0
 */
int BitInputStream::readBit(){

  int rslt;

  // If all bits in the buffer are read, fill the buffer first
  if(nbits == 0)
    fill();

  if(isEOF)
    return -1;

  // Get the bit at the appropriate location in the bit 
  // buffer, and return the appropriate int
  rslt = (buf & (1 << (nbits-1))) >> (nbits-1);

  //Increment the index
  nbits--;

  return rslt;
}

int BitInputStream::readInt(){

  int rslt = 0;
  int tmp;

  for(int i = 0; i < 32; i++){
    tmp = readBit();
    rslt |= tmp << (31-i); 
  }

  return rslt;
}

/** Fill the buffer from the input*/
void BitInputStream::fill(){
  if(!in.get(buf))
    isEOF = true;
  else
    nbits = 8;
}

bool BitInputStream::eof(){
  return isEOF;
}