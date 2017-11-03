int mutt_thread_set_flag (HEADER *hdr, int flag, int bf, int subthread)
{
  THREAD *start, *cur = hdr->thread;
  
  if ((Sort & SORT_MASK) != SORT_THREADS)
  {
    mutt_error _("Threading is not enabled.");
    return (-1);
  }

  if (!subthread)
    while (cur->parent)
      cur = cur->parent;
  start = cur;
  
  if (cur->message)
    mutt_set_flag (Context, cur->message, flag, bf);

  if ((cur = cur->child) == NULL)
    return (0);

  FOREVER
  {
    if (cur->message)
      mutt_set_flag (Context, cur->message, flag, bf);

    if (cur->child)
      cur = cur->child;
    else if (cur->next)
      cur = cur->next;
    else 
    {
      while (!cur->next)
      {
	cur = cur->parent;
	if (cur == start)
	  return (0);
      }
      cur = cur->next;
    }
  }
  /* not reached */
}