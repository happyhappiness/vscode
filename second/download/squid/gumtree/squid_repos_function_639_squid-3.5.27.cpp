SList *
slist_reverse (SList *slist)
{
  SList *result = 0;
  SList *next;

  while (slist)
    {
      next		= slist->next;
      slist->next	= result;
      result		= slist;
      slist		= next;
    }

  return result;
}