{
    UInt16 *prob = Ppmd7_GetBinSumm(p);
    if (rc->DecodeBit(rc, *prob) == 0)
    {
      Byte symbol;
      *prob = (UInt16)PPMD_UPDATE_PROB_0(*prob);
      symbol = (p->FoundState = Ppmd7Context_OneState(p->MinContext))->Symbol;
      Ppmd7_UpdateBin(p);
      return symbol;
    }
    *prob = (UInt16)PPMD_UPDATE_PROB_1(*prob);
    p->InitEsc = PPMD7_kExpEscape[*prob >> 10];
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(Ppmd7Context_OneState(p->MinContext)->Symbol) = 0;
    p->PrevSuccess = 0;
  }