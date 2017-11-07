static int do_search (const pattern_t* search, int allpats)
{
  int rc = 0;
  const pattern_t* pat;

  for (pat = search; pat; pat = pat->next)
  {
    switch (pat->op)
    {
      case M_BODY:
      case M_HEADER:
      case M_WHOLE_MSG:
        if (pat->stringmatch)
          rc++;
        break;
      default:
        if (pat->child && do_search (pat->child, 1))
          rc++;
    }

    if (!allpats)
      break;
  }

  return rc;
}