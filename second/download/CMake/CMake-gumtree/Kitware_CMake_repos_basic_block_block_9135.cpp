{
        tmp.Freq = (Byte)(tmp.Freq - (tmp.Freq >> 1));
        escFreq >>= 1;
      }