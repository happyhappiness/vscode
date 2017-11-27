static SList *
slist_sort_merge (SList *left, SList *right, SListCompare *compare,
		  void *userdata)
{
  SList merged, *insert;

  insert = &merged;

  while (left && right)
    {
      if ((*compare) (left, right, userdata) <= 0)
	{
	  insert = insert->next = left;
	  left = left->next;
	}
      else
	{
	  insert = insert->next = right;
	  right = right->next;
	}
    }

  insert->next = left ? left : right;

  return merged.next;
}