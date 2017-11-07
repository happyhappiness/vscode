static int alias_SortAddress (const void *a, const void *b)
{
  ADDRESS *pa = (*(ALIAS **) a)->addr;
  ADDRESS *pb = (*(ALIAS **) b)->addr;
  int r;

  if (pa == pb)
    r = 0;
  else if (pa == NULL)
    r = -1;
  else if (pb == NULL)
    r = 1;
  else if (pa->personal)
  { 
    if (pb->personal)
      r = mutt_strcasecmp (pa->personal, pb->personal);
    else
      r = 1;
  }
  else if (pb->personal)
    r = -1;
  else
    r = ascii_strcasecmp (pa->mailbox, pb->mailbox);
  return (RSORT (r));
}