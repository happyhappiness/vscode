(1)
  {
    if((p->Low ^ (p->Low + p->Range)) >= kTopValue)
    {
      if(p->Range >= p->Bottom)
        break;
      else
        p->Range = ((uint32_t)(-(int32_t)p->Low)) & (p->Bottom - 1);
    }
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
    p->Range <<= 8;
    p->Low <<= 8;
  }