static struct maildir* maildir_ins_sort (struct maildir* list,
					 int (*cmp) (struct maildir *,
						     struct maildir *))
{
  struct maildir *tmp, *last, *ret = NULL, *back;

  ret = list;
  list = list->next;
  ret->next = NULL;

  while (list)
  {
    last = NULL;
    back = list->next;
    for (tmp = ret; tmp && cmp (tmp, list) <= 0; tmp = tmp->next)
      last = tmp;

    list->next = tmp;
    if (last)
      last->next = list;
    else
      ret = list;

    list = back;
  }

  return ret;
}