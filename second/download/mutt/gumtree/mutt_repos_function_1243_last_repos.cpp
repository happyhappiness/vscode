static void calculate_visibility (CONTEXT *ctx, int *max_depth)
{
  THREAD *tmp, *tree = ctx->tree;
  int hide_top_missing = option (OPTHIDETOPMISSING) && !option (OPTHIDEMISSING);
  int hide_top_limited = option (OPTHIDETOPLIMITED) && !option (OPTHIDELIMITED);
  int depth = 0;

  /* we walk each level backwards to make it easier to compute next_subtree_visible */
  while (tree->next)
    tree = tree->next;
  *max_depth = 0;

  FOREVER
  {
    if (depth > *max_depth)
      *max_depth = depth;

    tree->subtree_visible = 0;
    if (tree->message)
    {
      FREE (&tree->message->tree);
      if (VISIBLE (tree->message, ctx))
      {
	tree->deep = 1;
	tree->visible = 1;
	tree->message->display_subject = need_display_subject (ctx, tree->message);
	for (tmp = tree; tmp; tmp = tmp->parent)
	{
	  if (tmp->subtree_visible)
	  {
	    tmp->deep = 1;
	    tmp->subtree_visible = 2;
	    break;
	  }
	  else
	    tmp->subtree_visible = 1;
	}
      }
      else
      {
	tree->visible = 0;
	tree->deep = !option (OPTHIDELIMITED);
      }
    }
    else
    {
      tree->visible = 0;
      tree->deep = !option (OPTHIDEMISSING);
    }
    tree->next_subtree_visible = tree->next && (tree->next->next_subtree_visible
						|| tree->next->subtree_visible);
    if (tree->child)
    {
      depth++;
      tree = tree->child;
      while (tree->next)
	tree = tree->next;
    }
    else if (tree->prev)
      tree = tree->prev;
    else
    {
      while (tree && !tree->prev)
      {
	depth--;
	tree = tree->parent;
      }
      if (!tree)
	break;
      else
	tree = tree->prev;
    }
  }
  
  /* now fix up for the OPTHIDETOP* options if necessary */
  if (hide_top_limited || hide_top_missing)
  {
    tree = ctx->tree;
    FOREVER
    {
      if (!tree->visible && tree->deep && tree->subtree_visible < 2 
	  && ((tree->message && hide_top_limited) || (!tree->message && hide_top_missing)))
	tree->deep = 0;
      if (!tree->deep && tree->child && tree->subtree_visible)
	tree = tree->child;
      else if (tree->next)
	tree = tree->next;
      else
      {
	while (tree && !tree->next)
	  tree = tree->parent;
	if (!tree)
	  break;
	else
	  tree = tree->next;
      }
    }
  }
}