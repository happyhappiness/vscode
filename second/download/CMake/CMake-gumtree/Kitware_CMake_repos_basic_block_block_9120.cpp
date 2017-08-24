{
  CPpmd_Void_Ref successor, fSuccessor = SUCCESSOR(p->FoundState);
  CTX_PTR c;
  unsigned s0, ns;
  
  if (p->FoundState->Freq < MAX_FREQ / 4 && p->MinContext->Suffix != 0)
  {
    c = SUFFIX(p->MinContext);
    
    if (c->NumStats == 1)
    {
      CPpmd_State *s = ONE_STATE(c);
      if (s->Freq < 32)
        s->Freq++;
    }
    else
    {
      CPpmd_State *s = STATS(c);
      if (s->Symbol != p->FoundState->Symbol)
      {
        do { s++; } while (s->Symbol != p->FoundState->Symbol);
        if (s[0].Freq >= s[-1].Freq)
        {
          SwapStates(&s[0], &s[-1]);
          s--;
        }
      }
      if (s->Freq < MAX_FREQ - 9)
      {
        s->Freq += 2;
        c->SummFreq += 2;
      }
    }
  }

  if (p->OrderFall == 0)
  {
    p->MinContext = p->MaxContext = CreateSuccessors(p, True);
    if (p->MinContext == 0)
    {
      RestartModel(p);
      return;
    }
    SetSuccessor(p->FoundState, REF(p->MinContext));
    return;
  }
  
  *p->Text++ = p->FoundState->Symbol;
  successor = REF(p->Text);
  if (p->Text >= p->UnitsStart)
  {
    RestartModel(p);
    return;
  }
  
  if (fSuccessor)
  {
    if (fSuccessor <= successor)
    {
      CTX_PTR cs = CreateSuccessors(p, False);
      if (cs == NULL)
      {
        RestartModel(p);
        return;
      }
      fSuccessor = REF(cs);
    }
    if (--p->OrderFall == 0)
    {
      successor = fSuccessor;
      p->Text -= (p->MaxContext != p->MinContext);
    }
  }
  else
  {
    SetSuccessor(p->FoundState, successor);
    fSuccessor = REF(p->MinContext);
  }
  
  s0 = p->MinContext->SummFreq - (ns = p->MinContext->NumStats) - (p->FoundState->Freq - 1);
  
  for (c = p->MaxContext; c != p->MinContext; c = SUFFIX(c))
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
  p->MaxContext = p->MinContext = CTX(fSuccessor);
}