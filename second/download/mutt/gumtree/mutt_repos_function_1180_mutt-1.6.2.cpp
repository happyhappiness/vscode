static void pseudo_threads (CONTEXT *ctx)
{
  THREAD *tree = ctx->tree, *top = tree;
  THREAD *tmp, *cur, *parent, *curchild, *nextchild;

  if (!ctx->subj_hash)
    ctx->subj_hash = mutt_make_subj_hash (ctx);

  while (tree)
  {
    cur = tree;
    tree = tree->next;
    if ((parent = find_subject (ctx, cur)) != NULL)
    {
      cur->fake_thread = 1;
      unlink_message (&top, cur);
      insert_message (&parent->child, parent, cur);
      parent->sort_children = 1;
      tmp = cur;
      FOREVER
      {
	while (!tmp->message)
	  tmp = tmp->child;

	/* if the message we're attaching has pseudo-children, they
	 * need to be attached to its parent, so move them up a level.
	 * but only do this if they have the same real subject as the
	 * parent, since otherwise they rightly belong to the message
	 * we're attaching. */
	if (tmp == cur
	    || !mutt_strcmp (tmp->message->env->real_subj,
			     parent->message->env->real_subj))
	{
	  tmp->message->subject_changed = 0;

	  for (curchild = tmp->child; curchild; )
	  {
	    nextchild = curchild->next;
	    if (curchild->fake_thread)
	    {
	      unlink_message (&tmp->child, curchild);
	      insert_message (&parent->child, parent, curchild);
	    }
	    curchild = nextchild;
	  }
	}

	while (!tmp->next && tmp != cur)
	{
	  tmp = tmp->parent;
	}
	if (tmp == cur)
	  break;
	tmp = tmp->next;
      }
    }
  }
  ctx->tree = top;
}