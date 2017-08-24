{
    UInt16 *prob = Ppmd7_GetBinSumm(p);
    CPpmd_State *s = Ppmd7Context_OneState(p->MinContext);
    if (s->Symbol == symbol)
    {
      RangeEnc_EncodeBit_0(rc, *prob);
      *prob = (UInt16)PPMD_UPDATE_PROB_0(*prob);
      p->FoundState = s;
      Ppmd7_UpdateBin(p);
      return;
    }
    else
    {
      RangeEnc_EncodeBit_1(rc, *prob);
      *prob = (UInt16)PPMD_UPDATE_PROB_1(*prob);
      p->InitEsc = PPMD7_kExpEscape[*prob >> 10];
      PPMD_SetAllBitsIn256Bytes(charMask);
      MASK(s->Symbol) = 0;
      p->PrevSuccess = 0;
    }
  }