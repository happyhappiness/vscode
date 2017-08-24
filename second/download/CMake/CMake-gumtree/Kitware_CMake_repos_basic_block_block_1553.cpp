(*regparse == '|') {
    regparse++;
    br = regbranch(&flags);
    if (br == 0)
      return (0);
    regtail(ret, br); // BRANCH -> BRANCH.
    if (!(flags & HASWIDTH))
      *flagp &= ~HASWIDTH;
    *flagp |= flags & SPSTART;
  }