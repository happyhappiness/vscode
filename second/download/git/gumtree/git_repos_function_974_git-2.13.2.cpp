static void
treedelta (register struct tree const *tree,
	   register unsigned int depth,
	   unsigned char delta[])
{
  if (!tree)
    return;
  treedelta(tree->llink, depth, delta);
  treedelta(tree->rlink, depth, delta);
  if (depth < delta[tree->label])
    delta[tree->label] = depth;
}