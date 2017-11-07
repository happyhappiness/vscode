static struct q_class_t *
classify_quote (struct q_class_t **QuoteList, const char *qptr,
		int length, int *force_redraw, int *q_level)
{
  struct q_class_t *q_list = *QuoteList;
  struct q_class_t *class = NULL, *tmp = NULL, *ptr, *save;
  char *tail_qptr;
  int offset, tail_lng;
  int index = -1;

  if (ColorQuoteUsed <= 1)
  {
    /* not much point in classifying quotes... */

    if (*QuoteList == NULL)
    {
      class = (struct q_class_t *) safe_calloc (1, sizeof (struct q_class_t));
      class->color = ColorQuote[0];
      *QuoteList = class;
    }
    return (*QuoteList);
  }

  /* Did I mention how much I like emulating Lisp in C? */

  /* classify quoting prefix */
  while (q_list)
  {
    if (length <= q_list->length)
    {
      /* case 1: check the top level nodes */

      if (mutt_strncmp (qptr, q_list->prefix, length) == 0)
      {
	if (length == q_list->length)
	  return q_list;	/* same prefix: return the current class */

	/* found shorter prefix */
	if (tmp == NULL)
	{
	  /* add a node above q_list */
	  tmp = (struct q_class_t *) safe_calloc (1, sizeof (struct q_class_t));
	  tmp->prefix = (char *) safe_calloc (1, length + 1);
	  strncpy (tmp->prefix, qptr, length);
	  tmp->length = length;

	  /* replace q_list by tmp in the top level list */
	  if (q_list->next)
	  {
	    tmp->next = q_list->next;
	    q_list->next->prev = tmp;
	  }
	  if (q_list->prev)
	  {
	    tmp->prev = q_list->prev;
	    q_list->prev->next = tmp;
	  }

	  /* make q_list a child of tmp */
	  tmp->down = q_list;
	  q_list->up = tmp;

	  /* q_list has no siblings for now */
	  q_list->next = NULL;
	  q_list->prev = NULL;

	  /* update the root if necessary */
	  if (q_list == *QuoteList)
	    *QuoteList = tmp;

	  index = q_list->index;

	  /* tmp should be the return class too */
	  class = tmp;

	  /* next class to test; if tmp is a shorter prefix for another
	   * node, that node can only be in the top level list, so don't
	   * go down after this point
	   */
	  q_list = tmp->next;
	}
	else
	{
	  /* found another branch for which tmp is a shorter prefix */

	  /* save the next sibling for later */
	  save = q_list->next;

	  /* unlink q_list from the top level list */
	  if (q_list->next)
	    q_list->next->prev = q_list->prev;
	  if (q_list->prev)
	    q_list->prev->next = q_list->next;

	  /* at this point, we have a tmp->down; link q_list to it */
	  ptr = tmp->down;
	  /* sibling order is important here, q_list should be linked last */
	  while (ptr->next)
	    ptr = ptr->next;
	  ptr->next = q_list;
	  q_list->next = NULL;
	  q_list->prev = ptr;
	  q_list->up = tmp;

	  index = q_list->index;

	  /* next class to test; as above, we shouldn't go down */
	  q_list = save;
	}

	/* we found a shorter prefix, so certain quotes have changed classes */
	*force_redraw = 1;
	continue;
      }
      else
      {
	/* shorter, but not a substring of the current class: try next */
	q_list = q_list->next;
	continue;
      }
    }
    else
    {
      /* case 2: try subclassing the current top level node */
      
      /* tmp != NULL means we already found a shorter prefix at case 1 */
      if (tmp == NULL && mutt_strncmp (qptr, q_list->prefix, q_list->length) == 0)
      {
	/* ok, it's a subclass somewhere on this branch */

	ptr = q_list;
	offset = q_list->length;

	q_list = q_list->down;
	tail_lng = length - offset;
	tail_qptr = (char *) qptr + offset;

	while (q_list)
	{
	  if (length <= q_list->length)
	  {
	    if (mutt_strncmp (tail_qptr, (q_list->prefix) + offset, tail_lng) == 0)
	    {
	      /* same prefix: return the current class */
	      if (length == q_list->length)
		return q_list;

	      /* found shorter common prefix */
	      if (tmp == NULL)
	      {
		/* add a node above q_list */
		tmp = (struct q_class_t *) safe_calloc (1, 
					    sizeof (struct q_class_t));
		tmp->prefix = (char *) safe_calloc (1, length + 1);
		strncpy (tmp->prefix, qptr, length);
		tmp->length = length;
			
		/* replace q_list by tmp */
		if (q_list->next)
		{
		  tmp->next = q_list->next;
		  q_list->next->prev = tmp;
		}
		if (q_list->prev)
		{
		  tmp->prev = q_list->prev;
		  q_list->prev->next = tmp;
		}

		/* make q_list a child of tmp */
		tmp->down = q_list;
		tmp->up = q_list->up;
		q_list->up = tmp;
		if (tmp->up->down == q_list)
		  tmp->up->down = tmp;

		/* q_list has no siblings */
		q_list->next = NULL;
		q_list->prev = NULL;
                              
		index = q_list->index;

		/* tmp should be the return class too */
		class = tmp;

		/* next class to test */
		q_list = tmp->next;
	      }
	      else
	      {
		/* found another branch for which tmp is a shorter prefix */

		/* save the next sibling for later */
		save = q_list->next;

		/* unlink q_list from the top level list */
		if (q_list->next)
		  q_list->next->prev = q_list->prev;
		if (q_list->prev)
		  q_list->prev->next = q_list->next;

		/* at this point, we have a tmp->down; link q_list to it */
		ptr = tmp->down;
		while (ptr->next)
		  ptr = ptr->next;
		ptr->next = q_list;
		q_list->next = NULL;
		q_list->prev = ptr;
		q_list->up = tmp;

		index = q_list->index;

		/* next class to test */
		q_list = save;
	      }

	      /* we found a shorter prefix, so we need a redraw */
	      *force_redraw = 1;
	      continue;
	    }
	    else
	    {
	      q_list = q_list->next;
	      continue;
	    }
	  }
	  else
	  {
	    /* longer than the current prefix: try subclassing it */
	    if (tmp == NULL && mutt_strncmp (tail_qptr, (q_list->prefix) + offset,
			  q_list->length - offset) == 0)
	    {
	      /* still a subclass: go down one level */
	      ptr = q_list;
	      offset = q_list->length;

	      q_list = q_list->down;
	      tail_lng = length - offset;
	      tail_qptr = (char *) qptr + offset;

	      continue;
	    }
	    else
	    {
	      /* nope, try the next prefix */
	      q_list = q_list->next;
	      continue;
	    }
	  }
	}

	/* still not found so far: add it as a sibling to the current node */
	if (class == NULL)
	{
	  tmp = (struct q_class_t *) safe_calloc (1, sizeof (struct q_class_t));
	  tmp->prefix = (char *) safe_calloc (1, length + 1);
	  strncpy (tmp->prefix, qptr, length);
	  tmp->length = length;

	  if (ptr->down)
	  {
	    tmp->next = ptr->down;
	    ptr->down->prev = tmp;
	  }
	  ptr->down = tmp;
	  tmp->up = ptr;

	  new_class_color (tmp, q_level);

	  return tmp;
	}
	else
	{
	  if (index != -1)
	    shift_class_colors (*QuoteList, tmp, index, q_level);

	  return class;
	}
      }
      else
      {
	/* nope, try the next prefix */
	q_list = q_list->next;
	continue;
      }
    }
  }

  if (class == NULL)
  {
    /* not found so far: add it as a top level class */
    class = (struct q_class_t *) safe_calloc (1, sizeof (struct q_class_t));
    class->prefix = (char *) safe_calloc (1, length + 1);
    strncpy (class->prefix, qptr, length);
    class->length = length;
    new_class_color (class, q_level);

    if (*QuoteList)
    {
      class->next = *QuoteList;
      (*QuoteList)->prev = class;
    }
    *QuoteList = class;
  }

  if (index != -1)
    shift_class_colors (*QuoteList, tmp, index, q_level);

  return class;
}