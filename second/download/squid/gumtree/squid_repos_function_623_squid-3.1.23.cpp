SList *
slist_remove (SList **phead, SListCallback *find, void *matchdata)
{
  SList *stale = 0;
  void *result = 0;

  assert (find);

  if (!phead || !*phead)
    return 0;

  /* Does the head of the passed list match? */
  result = (*find) (*phead, matchdata);
  if (result)
    {
      stale = *phead;
      *phead = stale->next;
    }
  /* what about the rest of the elements? */
  else
    {
      SList *head;
      for (head = *phead; head->next; head = head->next)
	{
	  result = (*find) (head->next, matchdata);
	  if (result)
	    {
	      stale		= head->next;
	      head->next	= stale->next;
	      break;
	    }
	}
    }

  return (SList *) result;
}