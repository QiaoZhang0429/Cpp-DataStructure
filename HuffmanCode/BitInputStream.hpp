#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

class BitInputStream{
private:
  char buf;           //one byte buffer of bits
  int nbits;          //how many bits have been written to buf
  std::istream & in;  //reference to the output stream to use
  bool isEOF;           //end of file
public:

  /** Initialize a BitInputStream that will use
   *  the given istream for output
   */
  BitInputStream(std::istream & is): in(is), buf(0), nbits(0), isEOF(false) { }

  /** Read the next bit from the bit buffer.
   *  Fill the buffer form the input stream first if needed
   *  Return 1 if the bit read is 1
   *  Return 0 if the bit read is 0
   */
  int readBit();

  /** Read the next integer from the bit buffer.
   */
  int readInt();

  /** Fill the buffer from the input*/
  void fill();

  /** Check whether the file reaching the end*/
  bool eof();

};

#endif // BITINPUTSTREAM_HPP
