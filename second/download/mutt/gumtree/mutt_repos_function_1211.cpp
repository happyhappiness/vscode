int _mutt_traverse_thread (CONTEXT *ctx, HEADER *cur, int flag)
{
  THREAD *thread, *top;
  HEADER *roothdr = NULL;
  int final, reverse = (Sort & SORT_REVERSE), minmsgno;
  int num_hidden = 0, new = 0, old = 0;
  int min_unread_msgno = INT_MAX, min_unread = cur->virtual;
#define CHECK_LIMIT (!ctx->pattern || cur->limited)

  if ((Sort & SORT_MASK) != SORT_THREADS && !(flag & MUTT_THREAD_GET_HIDDEN))
  {
    mutt_error (_("Threading is not enabled."));
    return (cur->virtual);
  }

  final = cur->virtual;
  thread = cur->thread;
  while (thread->parent)
    thread = thread->parent;
  top = thread;
  while (!thread->message)
    thread = thread->child;
  cur = thread->message;
  minmsgno = cur->msgno;

  if (!cur->read && CHECK_LIMIT)
  {
    if (cur->old)
      old = 2;
    else
      new = 1;
    if (cur->msgno < min_unread_msgno)
    {
      min_unread = cur->virtual;
      min_unread_msgno = cur->msgno;
    }
  }

  if (cur->virtual == -1 && CHECK_LIMIT)
    num_hidden++;

  if (flag & (MUTT_THREAD_COLLAPSE | MUTT_THREAD_UNCOLLAPSE))
  {
    cur->pair = 0; /* force index entry's color to be re-evaluated */
    cur->collapsed = flag & MUTT_THREAD_COLLAPSE;
    if (cur->virtual != -1)
    {
      roothdr = cur;
      if (flag & MUTT_THREAD_COLLAPSE)
	final = roothdr->virtual;
    }
  }

  if (thread == top && (thread = thread->child) == NULL)
  {
    /* return value depends on action requested */
    if (flag & (MUTT_THREAD_COLLAPSE | MUTT_THREAD_UNCOLLAPSE))
      return (final);
    else if (flag & MUTT_THREAD_UNREAD)
      return ((old && new) ? new : (old ? old : new));
    else if (flag & MUTT_THREAD_GET_HIDDEN)
      return (num_hidden);
    else if (flag & MUTT_THREAD_NEXT_UNREAD)
      return (min_unread);
  }
  
  FOREVER
  {
    cur = thread->message;

    if (cur)
    {
      if (flag & (MUTT_THREAD_COLLAPSE | MUTT_THREAD_UNCOLLAPSE))
      {
	cur->pair = 0; /* force index entry's color to be re-evaluated */
	cur->collapsed = flag & MUTT_THREAD_COLLAPSE;
	if (!roothdr && CHECK_LIMIT)
	{
	  roothdr = cur;
	  if (flag & MUTT_THREAD_COLLAPSE)
	    final = roothdr->virtual;
	}

	if (reverse && (flag & MUTT_THREAD_COLLAPSE) && (cur->msgno < minmsgno) && CHECK_LIMIT)
	{
	  minmsgno = cur->msgno;
	  final = cur->virtual;
	}

	if (flag & MUTT_THREAD_COLLAPSE)
	{
	  if (cur != roothdr)
	    cur->virtual = -1;
	}
	else 
	{
	  if (CHECK_LIMIT)
	    cur->virtual = cur->msgno;
	}
      }


      if (!cur->read && CHECK_LIMIT)
      {
	if (cur->old)
	  old = 2;
	else
	  new = 1;
	if (cur->msgno < min_unread_msgno)
	{
	  min_unread = cur->virtual;
	  min_unread_msgno = cur->msgno;
	}
      }

      if (cur->virtual == -1 && CHECK_LIMIT)
	num_hidden++;
    }

    if (thread->child)
      thread = thread->child;
    else if (thread->next)
      thread = thread->next;
    else
    {
      int done = 0;
      while (!thread->next)
      {
	thread = thread->parent;
	if (thread == top)
	{
	  done = 1;
	  break;
	}
      }
      if (done)
	break;
      thread = thread->next;
    }
  }

  /* return value depends on action requested */
  if (flag & (MUTT_THREAD_COLLAPSE | MUTT_THREAD_UNCOLLAPSE))
    return (final);
  else if (flag & MUTT_THREAD_UNREAD)
    return ((old && new) ? new : (old ? old : new));
  else if (flag & MUTT_THREAD_GET_HIDDEN)
    return (num_hidden+1);
  else if (flag & MUTT_THREAD_NEXT_UNREAD)
    return (min_unread);

  return (0);
#undef CHECK_LIMIT
}