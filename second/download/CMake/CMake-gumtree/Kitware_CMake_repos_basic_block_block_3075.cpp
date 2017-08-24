{
      quadrant[i] = 0;
      j = (j >> 8) | ( ((UInt16)block[i]) << 8);
      ftab[j]++;
   }