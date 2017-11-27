size_t
slist_length (SList *slist)
{
  size_t n;

  for (n = 0; slist; ++n)
    slist = slist->next;

  return n;
}