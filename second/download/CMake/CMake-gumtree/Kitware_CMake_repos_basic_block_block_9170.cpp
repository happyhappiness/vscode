{
    CPpmd_State *s = Ppmd7_GetStats(p, p->MinContext);
    unsigned i;
    UInt32 count, hiCnt;
    if ((count = rc->GetThreshold(rc, p->MinContext->SummFreq)) < (hiCnt = s->Freq))
    {
      Byte symbol;
      rc->Decode(rc, 0, s->Freq);
      p->FoundState = s;
      symbol = s->Symbol;
      Ppmd7_Update1_0(p);
      return symbol;
    }
    p->PrevSuccess = 0;
    i = p->MinContext->NumStats - 1;
    do
    {
      if ((hiCnt += (++s)->Freq) > count)
      {
        Byte symbol;
        rc->Decode(rc, hiCnt - s->Freq, s->Freq);
        p->FoundState = s;
        symbol = s->Symbol;
        Ppmd7_Update1(p);
        return symbol;
      }
    }
    while (--i);
    if (count >= p->MinContext->SummFreq)
      return -2;
    p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol];
    rc->Decode(rc, hiCnt, p->MinContext->SummFreq - hiCnt);
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(s->Symbol) = 0;
    i = p->MinContext->NumStats - 1;
    do { MASK((--s)->Symbol) = 0; } while (--i);
  }