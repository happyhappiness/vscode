static HEADER *find_virtual (THREAD *cur, int reverse)
{
  THREAD *top;

  if (cur->message && cur->message->virtual >= 0)
    return (cur->message);

  top = cur;
  if ((cur = cur->child) == NULL)
    return (NULL);

  while (reverse && cur->next)
    cur = cur->next;

  FOREVER
  {
    if (cur->message && cur->message->virtual >= 0)
      return (cur->message);

    if (cur->child)
    {
      cur = cur->child;

      while (reverse && cur->next)
	cur = cur->next;
    }
    else if (reverse ? cur->prev : cur->next)
      cur = reverse ? cur->prev : cur->next;
    else
    {
      while (!(reverse ? cur->prev : cur->next))
      {
	cur = cur->parent;
	if (cur == top)
	  return (NULL);
      }
      cur = reverse ? cur->prev : cur->next;
    }
    /* not reached */
  }
}