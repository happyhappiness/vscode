(c = p->MaxContext; c != p->MinContext; c = SUFFIX(c))
  {
    unsigned ns1;
    UInt32 cf, sf;
    if ((ns1 = c->NumStats) != 1)
    {
      if ((ns1 & 1) == 0)
      {
        /* Expand for one UNIT */
        unsigned oldNU = ns1 >> 1;
        unsigned i = U2I(oldNU);
        if (i != U2I(oldNU + 1))
        {
          void *ptr = AllocUnits(p, i + 1);
          void *oldPtr;
          if (!ptr)
          {
            RestartModel(p);
            return;
          }
          oldPtr = STATS(c);
          MyMem12Cpy(ptr, oldPtr, oldNU);
          InsertNode(p, oldPtr, i);
          c->Stats = STATS_REF(ptr);
        }
      }
      c->SummFreq = (UInt16)(c->SummFreq + (2 * ns1 < ns) + 2 * ((4 * ns1 <= ns) & (c->SummFreq <= 8 * ns1)));
    }
    else
    {
      CPpmd_State *s = (CPpmd_State*)AllocUnits(p, 0);
      if (!s)
      {
        RestartModel(p);
        return;
      }
      *s = *ONE_STATE(c);
      c->Stats = REF(s);
      if (s->Freq < MAX_FREQ / 4 - 1)
        s->Freq <<= 1;
      else
        s->Freq = MAX_FREQ - 4;
      c->SummFreq = (UInt16)(s->Freq + p->InitEsc + (ns > 3));
    }
    cf = 2 * (UInt32)p->FoundState->Freq * (c->SummFreq + 6);
    sf = (UInt32)s0 + c->SummFreq;
    if (cf < 6 * sf)
    {
      cf = 1 + (cf > sf) + (cf >= 4 * sf);
      c->SummFreq += 3;
    }
    else
    {
      cf = 4 + (cf >= 9 * sf) + (cf >= 12 * sf) + (cf >= 15 * sf);
      c->SummFreq = (UInt16)(c->SummFreq + cf);
    }
    {
      CPpmd_State *s = STATS(c) + ns1;
      SetSuccessor(s, successor);
      s->Symbol = p->FoundState->Symbol;
      s->Freq = (Byte)cf;
      c->NumStats = (UInt16)(ns1 + 1);
    }
  }