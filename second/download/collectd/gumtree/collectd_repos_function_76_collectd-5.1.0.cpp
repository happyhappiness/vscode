SList *
slist_sort (SList *slist, SListCompare *compare, void *userdata)
{
  SList *left, *right;

  if (!slist)
    return slist;

  /* Be sure that LEFT and RIGHT never contain the same item.  */
  left = slist;
  right = slist->next;

  /* Skip two items with RIGHT and one with SLIST, until RIGHT falls off
     the end.  SLIST must be about half way along.  */
  while (right && (right = right->next))
    {
      if (!right || !(right = right->next))
	break;
      slist = slist->next;
    }
  right = slist->next;
  slist->next = 0;

  /* Sort LEFT and RIGHT, then merge the two.  */
  return slist_sort_merge (slist_sort (left, compare, userdata),
			   slist_sort (right, compare, userdata),
			   compare, userdata);
}