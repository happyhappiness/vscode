void mutt_sort_threads (CONTEXT *ctx, int init)
{
  HEADER *cur;
  int i, oldsort, using_refs = 0;
  THREAD *thread, *new, *tmp, top;
  LIST *ref = NULL;
  
  /* set Sort to the secondary method to support the set sort_aux=reverse-*
   * settings.  The sorting functions just look at the value of
   * SORT_REVERSE
   */
  oldsort = Sort;
  Sort = SortAux;
  
  if (!ctx->thread_hash)
    init = 1;

  if (init)
    ctx->thread_hash = hash_create (ctx->msgcount * 2, 0);

  /* we want a quick way to see if things are actually attached to the top of the
   * thread tree or if they're just dangling, so we attach everything to a top
   * node temporarily */
  top.parent = top.next = top.prev = NULL;
  top.child = ctx->tree;
  for (thread = ctx->tree; thread; thread = thread->next)
    thread->parent = &top;

  /* put each new message together with the matching messageless THREAD if it
   * exists.  otherwise, if there is a THREAD that already has a message, thread
   * new message as an identical child.  if we didn't attach the message to a
   * THREAD, make a new one for it. */
  for (i = 0; i < ctx->msgcount; i++)
  {
    cur = ctx->hdrs[i];

    if (!cur->thread)
    {
      if ((!init || option (OPTDUPTHREADS)) && cur->env->message_id)
	thread = hash_find (ctx->thread_hash, cur->env->message_id);
      else
	thread = NULL;

      if (thread && !thread->message)
      {
	/* this is a message which was missing before */
	thread->message = cur;
	cur->thread = thread;
	thread->check_subject = 1;

	/* mark descendants as needing subject_changed checked */
	for (tmp = (thread->child ? thread->child : thread); tmp != thread; )
	{
	  while (!tmp->message)
	    tmp = tmp->child;
	  tmp->check_subject = 1;
	  while (!tmp->next && tmp != thread)
	    tmp = tmp->parent;
	  if (tmp != thread)
	    tmp = tmp->next;
	}

	if (thread->parent)
	{
	  /* remove threading info above it based on its children, which we'll
	   * recalculate based on its headers.  make sure not to leave
	   * dangling missing messages.  note that we haven't kept track
	   * of what info came from its children and what from its siblings'
	   * children, so we just remove the stuff that's definitely from it */
	  do
	  {
	    tmp = thread->parent;
	    unlink_message (&tmp->child, thread);
	    thread->parent = NULL;
	    thread->sort_key = NULL;
	    thread->fake_thread = 0;
	    thread = tmp;
	  } while (thread != &top && !thread->child && !thread->message);
	}
      }
      else
      {
	new = (option (OPTDUPTHREADS) ? thread : NULL);

	thread = safe_calloc (1, sizeof (THREAD));
	thread->message = cur;
	thread->check_subject = 1;
	cur->thread = thread;
	hash_insert (ctx->thread_hash,
		     cur->env->message_id ? cur->env->message_id : "",
		     thread, 1);

	if (new)
	{
	  if (new->duplicate_thread)
	    new = new->parent;

	  thread = cur->thread;

	  insert_message (&new->child, new, thread);
	  thread->duplicate_thread = 1;
	  thread->message->threaded = 1;
	}
      }
    }
    else
    {
      /* unlink pseudo-threads because they might be children of newly
       * arrived messages */
      thread = cur->thread;
      for (new = thread->child; new; )
      {
	tmp = new->next;
	if (new->fake_thread)
	{
	  unlink_message (&thread->child, new);
	  insert_message (&top.child, &top, new);
	  new->fake_thread = 0;
	}
	new = tmp;
      }
    }
  }

  /* thread by references */
  for (i = 0; i < ctx->msgcount; i++)
  {
    cur = ctx->hdrs[i];
    if (cur->threaded)
      continue;
    cur->threaded = 1;

    thread = cur->thread;
    using_refs = 0;

    while (1)
    {
      if (using_refs == 0)
      {
	/* look at the beginning of in-reply-to: */
	if ((ref = cur->env->in_reply_to) != NULL)
	  using_refs = 1;
	else
	{
	  ref = cur->env->references;
	  using_refs = 2;
	}
      }
      else if (using_refs == 1)
      {
	/* if there's no references header, use all the in-reply-to:
	 * data that we have.  otherwise, use the first reference
	 * if it's different than the first in-reply-to, otherwise use
	 * the second reference (since at least eudora puts the most
	 * recent reference in in-reply-to and the rest in references)
	 */
	if (!cur->env->references)
	  ref = ref->next;
	else
	{
	  if (mutt_strcmp (ref->data, cur->env->references->data))
	    ref = cur->env->references;
	  else
	    ref = cur->env->references->next;
	  
	  using_refs = 2;
	}
      }
      else
	ref = ref->next; /* go on with references */
      
      if (!ref)
	break;

      if ((new = hash_find (ctx->thread_hash, ref->data)) == NULL)
      {
	new = safe_calloc (1, sizeof (THREAD));
	hash_insert (ctx->thread_hash, ref->data, new, 1);
      }
      else
      {
	if (new->duplicate_thread)
	  new = new->parent;
	if (is_descendant (new, thread)) /* no loops! */
	  continue;
      }

      if (thread->parent)
	unlink_message (&top.child, thread);
      insert_message (&new->child, new, thread);
      thread = new;
      if (thread->message || (thread->parent && thread->parent != &top))
	break;
    }

    if (!thread->parent)
      insert_message (&top.child, &top, thread);
  }

  /* detach everything from the temporary top node */
  for (thread = top.child; thread; thread = thread->next)
  {
    thread->parent = NULL;
  }
  ctx->tree = top.child;

  check_subjects (ctx, init);

  if (!option (OPTSTRICTTHREADS))
    pseudo_threads (ctx);

  if (ctx->tree)
  {
    ctx->tree = mutt_sort_subthreads (ctx->tree, init);

    /* restore the oldsort order. */
    Sort = oldsort;
    
    /* Put the list into an array. */
    linearize_tree (ctx);

    /* Draw the thread tree. */
    mutt_draw_tree (ctx);
  }
}