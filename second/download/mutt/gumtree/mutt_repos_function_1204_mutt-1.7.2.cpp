THREAD *mutt_sort_subthreads (THREAD *thread, int init)
{
  THREAD **array, *sort_key, *top, *tmp;
  HEADER *oldsort_key;
  int i, array_size, sort_top = 0;
  
  /* we put things into the array backwards to save some cycles,
   * but we want to have to move less stuff around if we're 
   * resorting, so we sort backwards and then put them back
   * in reverse order so they're forwards
   */
  Sort ^= SORT_REVERSE;
  if (!compare_threads (NULL, NULL))
    return (thread);

  top = thread;

  array = safe_calloc ((array_size = 256), sizeof (THREAD *));
  while (1)
  {
    if (init || !thread->sort_key)
    {
      thread->sort_key = NULL;

      if (thread->parent)
        thread->parent->sort_children = 1;
      else
	sort_top = 1;
    }

    if (thread->child)
    {
      thread = thread->child;
      continue;
    }
    else
    {
      /* if it has no children, it must be real. sort it on its own merits */
      thread->sort_key = thread->message;

      if (thread->next)
      {
	thread = thread->next;
	continue;
      }
    }

    while (!thread->next)
    {
      /* if it has siblings and needs to be sorted, sort it... */
      if (thread->prev && (thread->parent ? thread->parent->sort_children : sort_top))
      {
	/* put them into the array */
	for (i = 0; thread; i++, thread = thread->prev)
	{
	  if (i >= array_size)
	    safe_realloc (&array, (array_size *= 2) * sizeof (THREAD *));

	  array[i] = thread;
	}

	qsort ((void *) array, i, sizeof (THREAD *), *compare_threads);

	/* attach them back together.  make thread the last sibling. */
	thread = array[0];
	thread->next = NULL;
	array[i - 1]->prev = NULL;

	if (thread->parent)
	  thread->parent->child = array[i - 1];
	else
	  top = array[i - 1];

	while (--i)
	{
	  array[i - 1]->prev = array[i];
	  array[i]->next = array[i - 1];
	}
      }

      if (thread->parent)
      {
	tmp = thread;
	thread = thread->parent;

	if (!thread->sort_key || thread->sort_children)
	{
	  /* make sort_key the first or last sibling, as appropriate */
	  sort_key = (!(Sort & SORT_LAST) ^ !(Sort & SORT_REVERSE)) ? thread->child : tmp;

	  /* we just sorted its children */
	  thread->sort_children = 0;

	  oldsort_key = thread->sort_key;
	  thread->sort_key = thread->message;

	  if (Sort & SORT_LAST)
	  {
	    if (!thread->sort_key
		|| ((((Sort & SORT_REVERSE) ? 1 : -1)
		     * compare_threads ((void *) &thread,
					(void *) &sort_key))
		    > 0))
	      thread->sort_key = sort_key->sort_key;
	  }
	  else if (!thread->sort_key)
	    thread->sort_key = sort_key->sort_key;

	  /* if its sort_key has changed, we need to resort it and siblings */
	  if (oldsort_key != thread->sort_key)
	  {
	    if (thread->parent)
	      thread->parent->sort_children = 1;
	    else
	      sort_top = 1;
	  }
	}
      }
      else
      {
	Sort ^= SORT_REVERSE;
	FREE (&array);
	return (top);
      }
    }

    thread = thread->next;
  }
}