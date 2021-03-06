uint8_t iPixelMap[][siStripLedCount * 2] = {
  //0: No remap at all
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61},
  
  //1: Clockwise
  {0, 31, 1, 32, 2, 33, 3, 34, 4, 35, 5, 36, 6, 37, 7, 38, 8, 39, 9, 40, 10, 41, 11, 42, 12, 43, 13, 44, 14, 45, 15, 46, 16, 47, 17, 48, 18, 49, 19, 50, 20, 51, 21, 52, 22, 53, 23, 54, 24, 55, 25, 56, 26, 57, 27, 58, 28, 59, 29, 60, 30, 61},

  //2: Counterclockwise
  {30, 61, 29, 60, 28, 59, 27, 58, 26, 57, 25, 56, 24, 55, 23, 54, 22, 53, 21, 52, 20, 51, 19, 50, 18, 49, 17, 48, 16, 47, 15, 46, 14, 45, 13, 44, 12, 43, 11, 42, 10, 41, 9, 40, 8, 39, 7, 38, 6, 37, 5, 36, 4, 35, 3, 34, 2, 33, 1, 32, 0, 31},

  //3: Random 1
  {36, 52, 16, 23, 12, 24, 47, 3, 45, 14, 6, 54, 57, 41, 25, 13, 38, 44, 55, 7, 32, 39, 58, 42, 43, 11, 56, 35, 61, 30, 60, 9, 0, 2, 27, 34, 29, 19, 5, 51, 28, 15, 46, 26, 37, 4, 40, 53, 48, 17, 31, 10, 22, 59, 49, 1, 18, 33, 21, 50, 20, 8},
  
  //4: Random 2
  {27, 49, 50, 45, 33, 37, 43, 1, 23, 24, 20, 2, 4, 19, 29, 22, 17, 36, 14, 55, 7, 16, 52, 54, 60, 57, 51, 3, 48, 58, 9, 18, 26, 21, 25, 46, 5, 0, 34, 53, 40, 15, 39, 13, 42, 56, 30, 44, 59, 10, 41, 6, 32, 38, 35, 61, 31, 8, 11, 12, 47, 28},

  //5: Left to right
  {31, 0, 30, 32, 1, 61, 33, 2, 34, 29, 3, 35, 4, 60, 28, 59, 27, 36, 58, 26, 57, 5, 25, 35, 56, 37, 24, 6, 55, 38, 23, 7, 54, 39, 22, 8, 53, 40, 21, 52, 9, 20, 41, 51, 10, 19, 50, 42, 18, 11, 43, 12, 44, 17, 48, 16, 13, 45, 14, 47, 46, 15},

  //6: Sweep along W, left to right
  {29, 30, 61, 31, 60, 0, 32, 28, 1, 59, 33, 27, 2, 58, 26, 34, 3, 57, 35, 4, 36, 25, 5, 37, 36, 6, 24, 55, 38, 23, 7, 54, 22, 53, 39, 21, 8, 40, 9, 52, 41, 20, 10, 42, 11, 51, 43, 19, 12, 50, 44, 18, 13, 49, 45, 17, 14, 48, 46, 15, 16, 47},

  //7: Pannels
  {30, 61, 9, 41, 10, 37, 5, 36, 47, 16, 54, 23, 55, 24, 56, 40, 8, 39, 22, 53, 21, 52, 6, 38, 7, 48, 17, 49, 18, 50, 19, 51, 20, 4, 35, 3, 34, 2, 33, 1, 32, 0, 31, 15, 46, 14, 45, 13, 44, 12, 43, 11, 42, 25, 57, 26, 58, 27, 59, 28, 60, 29},

  //8: Top to bottom
  {30, 61, 29, 48, 16, 47, 31, 60, 17, 46, 0, 28, 49, 14, 32, 59, 18, 45, 1, 27, 23, 54, 22, 50, 13, 33, 58, 19, 44, 2, 26, 55, 53, 51, 12, 34, 57, 21, 51, 3, 25, 56, 14, 52, 20, 43, 35, 38, 7, 39, 8, 11, 4, 6, 40, 42, 36, 5, 37, 9, 41, 10},
  
  //x: Test
  {0, 31}
};

