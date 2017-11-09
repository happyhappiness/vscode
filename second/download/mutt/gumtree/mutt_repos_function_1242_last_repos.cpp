static void linearize_tree (CONTEXT *ctx)
{
  THREAD *tree = ctx->tree;
  HEADER **array = ctx->hdrs + (Sort & SORT_REVERSE ? ctx->msgcount - 1 : 0);

  while (tree)
  {
    while (!tree->message)
      tree = tree->child;

    *array = tree->message;
    array += Sort & SORT_REVERSE ? -1 : 1;

    if (tree->child)
      tree = tree->child;
    else
    {
      while (tree)
      {
	if (tree->next)
	{
	  tree = tree->next;
	  break;
	}
	else
	  tree = tree->parent;
      }
    }
  }
}