void *
slist_find (SList *slist, SListCallback *find, void *matchdata)
{
  void *result = 0;

  assert (find);

  for (; slist; slist = slist->next)
    {
      result = (*find) (slist, matchdata);
      if (result)
	break;
    }

  return result;
}