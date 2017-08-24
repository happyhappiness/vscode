{
      RangeEnc_EncodeBit_0(rc, *prob);
      *prob = (UInt16)PPMD_UPDATE_PROB_0(*prob);
      p->FoundState = s;
      Ppmd7_UpdateBin(p);
      return;
    }