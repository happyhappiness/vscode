{
      CPpmd_See *s = &p->See[i][k];
      s->Summ = (UInt16)((5 * i + 10) << (s->Shift = PPMD_PERIOD_BITS - 4));
      s->Count = 4;
    }