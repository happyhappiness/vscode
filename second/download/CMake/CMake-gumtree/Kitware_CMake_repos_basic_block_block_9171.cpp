{
      p->Stream->Write(p->Stream, (Byte)(temp + (Byte)(p->Low >> 32)));
      temp = 0xFF;
    }