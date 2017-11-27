void *
slist_foreach (SList *slist, SListCallback *foreach, void *userdata)
{
  void *result = 0;

  assert (foreach);

  while (slist)
    {
      SList *next = slist->next;
      result = (*foreach) (slist, userdata);

      if (result)
	break;

      slist = next;
    }

  return result;
}