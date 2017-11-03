static void unlink_message (THREAD **old, THREAD *cur)
{
  THREAD *tmp;

  if (cur->prev)
    cur->prev->next = cur->next;
  else
    *old = cur->next;

  if (cur->next)
    cur->next->prev = cur->prev;

  if (cur->sort_key)
  {
    for (tmp = cur->parent; tmp && tmp->sort_key == cur->sort_key;
	 tmp = tmp->parent)
      tmp->sort_key = NULL;
  }
}