{
      p->OrderFall++;
      if (!p->MinContext->Suffix)
        return -1;
      p->MinContext = Ppmd7_GetContext(p, p->MinContext->Suffix);
    }