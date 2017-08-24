do
    {
      p->OrderFall++;
      if (!p->MinContext->Suffix)
        return; /* EndMarker (symbol = -1) */
      p->MinContext = Ppmd7_GetContext(p, p->MinContext->Suffix);
    }
    while (p->MinContext->NumStats == numMasked);