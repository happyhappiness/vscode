SList *
slist_nth (SList *slist, size_t n)
{
  for (;n > 1 && slist; n--)
    slist = slist->next;

  return slist;
}