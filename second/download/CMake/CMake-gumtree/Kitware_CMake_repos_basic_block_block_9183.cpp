{
    CPpmd_State *s = Ppmd7_GetStats(p, p->MinContext);
    UInt32 sum;
    unsigned i;
    if (s->Symbol == symbol)
    {
      RangeEnc_Encode(rc, 0, s->Freq, p->MinContext->SummFreq);
      p->FoundState = s;
      Ppmd7_Update1_0(p);
      return;
    }
    p->PrevSuccess = 0;
    sum = s->Freq;
    i = p->MinContext->NumStats - 1;
    do
    {
      if ((++s)->Symbol == symbol)
      {
        RangeEnc_Encode(rc, sum, s->Freq, p->MinContext->SummFreq);
        p->FoundState = s;
        Ppmd7_Update1(p);
        return;
      }
      sum += s->Freq;
    }
    while (--i);
    
    p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol];
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(s->Symbol) = 0;
    i = p->MinContext->NumStats - 1;
    do { MASK((--s)->Symbol) = 0; } while (--i);
    RangeEnc_Encode(rc, sum, p->MinContext->SummFreq - sum, p->MinContext->SummFreq);
  }