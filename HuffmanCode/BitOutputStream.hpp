#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

# include<iostream>

class BitOutputStream{
private:
  char buf;           //one byte buffer of bits
  int nbits;          //how many bits have been written to buf
  std::ostream & out; //reference to the output stream to use
public:

  /** Initialize a BitOutputStream that will use
   *  the given ostream for output
   */
  BitOutputStream(std::ostream & os): out(os), buf(0), nbits(0){
    //clear buffer and bit counter
  }

  /** Write the least significant bit of the argument to 
   *  the bit buffer, and increment the bit buffer index.
   * But flush the buffer first, if it is full.
   */
  void writeBit(int i);

  /** Write integer*/
  void writeInt(int n);

  /** Send the buffer to the output, and clear it*/
  void flush();
  
};

#endif // BITOUTPUTSTREAM_HPP
