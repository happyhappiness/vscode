SList *
slist_cons (SList *item, SList *slist)
{
  if (!item)
    {
      return slist;
    }

  assert (!item->next);

  item->next = slist;
  return item;
}