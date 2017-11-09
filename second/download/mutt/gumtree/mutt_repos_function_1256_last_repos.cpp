int _mutt_aside_thread (HEADER *hdr, short dir, short subthreads)
{
  THREAD *cur;
  HEADER *tmp;

  if ((Sort & SORT_MASK) != SORT_THREADS)
  {
    mutt_error _("Threading is not enabled.");
    return (hdr->virtual);
  }

  cur = hdr->thread;

  if (!subthreads)
  {
    while (cur->parent)
      cur = cur->parent;
  }
  else
  {
    if ((dir != 0) ^ ((Sort & SORT_REVERSE) != 0))
    {
      while (!cur->next && cur->parent)
	cur = cur->parent;
    }
    else
    {
      while (!cur->prev && cur->parent)
	cur = cur->parent;
    }
  }

  if ((dir != 0) ^ ((Sort & SORT_REVERSE) != 0))
  {
    do
    { 
      cur = cur->next;
      if (!cur)
	return (-1);
      tmp = find_virtual (cur, 0);
    } while (!tmp);
  }
  else
  {
    do
    { 
      cur = cur->prev;
      if (!cur)
	return (-1);
      tmp = find_virtual (cur, 1);
    } while (!tmp);
  }

  return (tmp->virtual);
}