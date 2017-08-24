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