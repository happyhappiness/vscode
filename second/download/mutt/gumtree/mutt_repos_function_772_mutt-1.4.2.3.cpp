void mutt_draw_tree (CONTEXT *ctx)
{
  char *pfx = NULL, *mypfx = NULL, *arrow = NULL, *myarrow = NULL;
  char corner = (Sort & SORT_REVERSE) ? M_TREE_ULCORNER : M_TREE_LLCORNER;
  char vtee = (Sort & SORT_REVERSE) ? M_TREE_BTEE : M_TREE_TTEE;
  int depth = 0, start_depth = 0, max_depth = 0, max_width = 0;
  THREAD *nextdisp = NULL, *pseudo = NULL, *parent = NULL, *tree = ctx->tree;
  HEADER *hdr;

  /* Do the visibility calculations and free the old thread chars.
   * From now on we can simply ignore invisible subtrees
   */
  calculate_visibility (ctx);
  while (tree)
  {
    if (depth >= max_depth)
      safe_realloc ((void **) &pfx,
		    (max_depth += 32) * 2 * sizeof (char));
    if (depth - start_depth >= max_width)
      safe_realloc ((void **) &arrow,
		    (max_width += 16) * 2 * sizeof (char));
    hdr = tree->message;
    if (depth)
    {
      myarrow = arrow + (depth - start_depth - (start_depth ? 0 : 1)) * 2;
      if (depth && start_depth == depth)
	myarrow[0] = nextdisp ? M_TREE_LTEE : corner;
      else if (parent->message && !option (OPTHIDELIMITED))
	myarrow[0] = M_TREE_HIDDEN;
      else if (!parent->message && !option (OPTHIDEMISSING))
	myarrow[0] = M_TREE_MISSING;
      else
	myarrow[0] = vtee;
      myarrow[1] = pseudo ?  M_TREE_STAR
		    : (tree->duplicate_thread ? M_TREE_EQUALS : M_TREE_HLINE);
      if (tree->visible)
      {
	myarrow[2] = M_TREE_RARROW;
	myarrow[3] = 0;
	hdr->tree = safe_malloc ((2 + depth * 2) * sizeof (char));
	if (start_depth > 1)
	{
	  strncpy (hdr->tree, pfx, (start_depth - 1) * 2);
	  strfcpy (hdr->tree + (start_depth - 1) * 2,
		   arrow, (2 + depth - start_depth) * 2);
	}
	else
	  strfcpy (hdr->tree, arrow, 2 + depth * 2);
      }
    }
    if (tree->child && depth)
    {
      mypfx = pfx + (depth - 1) * 2;
      mypfx[0] = nextdisp ? M_TREE_VLINE : M_TREE_SPACE;
      mypfx[1] = M_TREE_SPACE;
    }
    parent = tree;
    nextdisp = NULL;
    pseudo = NULL;
    do
    {
      if (tree->child && tree->subtree_visible)
      {
	if (tree->deep)
	  depth++;
	if (tree->visible)
	  start_depth = depth;
	tree = tree->child;

	/* we do this here because we need to make sure that the first child thread
	 * of the old tree that we deal with is actually displayed if any are,
	 * or we might set the parent variable wrong while going through it. */
	while (!tree->subtree_visible && tree->next)
	  tree = tree->next;
      }
      else
      {
	while (!tree->next && tree->parent)
	{
	  if (tree == pseudo)
	    pseudo = NULL;
	  if (tree == nextdisp)
	    nextdisp = NULL;
	  if (tree->visible)
	    start_depth = depth;
	  tree = tree->parent;
	  if (tree->deep)
	  {
	    if (start_depth == depth)
	      start_depth--;
	    depth--;
	  }
	}
	if (tree == pseudo)
	  pseudo = NULL;
	if (tree == nextdisp)
	  nextdisp = NULL;
	if (tree->visible)
	  start_depth = depth;
	tree = tree->next;
	if (!tree)
	  break;
      }
      hdr = tree->message;
      if (!pseudo && tree->fake_thread)
	pseudo = tree;
      if (!nextdisp && tree->next_subtree_visible)
	nextdisp = tree;
    }
    while (!tree->deep);
  }

  safe_free ((void **) &pfx);
  safe_free ((void **) &arrow);
}