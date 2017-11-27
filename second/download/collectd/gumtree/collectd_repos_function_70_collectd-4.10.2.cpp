SList *
slist_tail (SList *slist)
{
  return slist ? slist->next : NULL;
}