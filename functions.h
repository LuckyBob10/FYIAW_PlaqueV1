uint8_t Advance8BitVal(uint8_t iCurVal, uint8_t iUpperLimit = 255, uint8_t iAdvanceBy = 1) {
  if (iCurVal >= iUpperLimit) {
    return 0;
  }
  else {
    return iCurVal + iAdvanceBy;
  }
}

uint8_t LimitPixel(int iPixel) {
  if (iPixel < 0) {
    return iPixels + iPixel;
  }
  if (iPixel <= iPixels) {
    return iPixel;
  }
  else {
    return iPixel - iPixels;
  }
}

void scrambleArray(int * array, int lower, int upper)
{
  int last = lower;
  int temp = array[last];
  for (int i = 0; i < (upper-lower); ++i)
  {
    int index = random(lower, upper);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}

uint8_t GetUniqueRandom8Bit(uint8_t iCur, uint8_t iLow = 0, uint8_t iHigh = 255) {
  uint8_t iOld = iCur;
  for (uint8_t i=0; i<20; i++) {
    iCur = random(iLow, iHigh + 1);
    if (iCur != iOld) {
      break;
    }
  }
  return iCur;
}

