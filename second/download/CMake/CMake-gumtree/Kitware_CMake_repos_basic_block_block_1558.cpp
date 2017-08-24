{
    latest = regpiece(&flags);
    if (latest == 0)
      return (0);
    *flagp |= flags & HASWIDTH;
    if (chain == 0) // First piece.
      *flagp |= flags & SPSTART;
    else
      regtail(chain, latest);
    chain = latest;
  }