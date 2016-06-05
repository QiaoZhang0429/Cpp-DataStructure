byte bitVal(byte b, int n){
  return (b >> n) & 1;
}

byte setBit(byte b, int bit, int n){
  /*
  if(bit == 0)
    return ~ (1 << n) & b;
  else if(bit == 1){
    return b | (bit << n);
  }
  */
  b = b & ~(1 << n);
  return b | (bit << n);
}