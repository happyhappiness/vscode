const char *
kwsprep (kwset_t kws)
{
  register struct kwset *kwset;
  register int i;
  register struct trie *curr;
  register unsigned char const *trans;
  unsigned char delta[NCHAR];

  kwset = (struct kwset *) kws;

  /* Initial values for the delta table; will be changed later.  The
     delta entry for a given character is the smallest depth of any
     node at which an outgoing edge is labeled by that character. */
  memset(delta, kwset->mind < UCHAR_MAX ? kwset->mind : UCHAR_MAX, NCHAR);

  /* Check if we can use the simple boyer-moore algorithm, instead
     of the hairy commentz-walter algorithm. */
  if (kwset->words == 1 && kwset->trans == NULL)
    {
      char c;

      /* Looking for just one string.  Extract it from the trie. */
      kwset->target = obstack_alloc(&kwset->obstack, kwset->mind);
      if (!kwset->target)
	return "memory exhausted";
      for (i = kwset->mind - 1, curr = kwset->trie; i >= 0; --i)
	{
	  kwset->target[i] = curr->links->label;
	  curr = curr->links->trie;
	}
      /* Build the Boyer Moore delta.  Boy that's easy compared to CW. */
      for (i = 0; i < kwset->mind; ++i)
	delta[U(kwset->target[i])] = kwset->mind - (i + 1);
      /* Find the minimal delta2 shift that we might make after
	 a backwards match has failed. */
      c = kwset->target[kwset->mind - 1];
      for (i = kwset->mind - 2; i >= 0; --i)
	if (kwset->target[i] == c)
	  break;
      kwset->mind2 = kwset->mind - (i + 1);
    }
  else
    {
      register struct trie *fail;
      struct trie *last, *next[NCHAR];

      /* Traverse the nodes of the trie in level order, simultaneously
	 computing the delta table, failure function, and shift function. */
      for (curr = last = kwset->trie; curr; curr = curr->next)
	{
	  /* Enqueue the immediate descendants in the level order queue. */
	  enqueue(curr->links, &last);

	  curr->shift = kwset->mind;
	  curr->maxshift = kwset->mind;

	  /* Update the delta table for the descendants of this node. */
	  treedelta(curr->links, curr->depth, delta);

	  /* Compute the failure function for the descendants of this node. */
	  treefails(curr->links, curr->fail, kwset->trie);

	  /* Update the shifts at each node in the current node's chain
	     of fails back to the root. */
	  for (fail = curr->fail; fail; fail = fail->fail)
	    {
	      /* If the current node has some outgoing edge that the fail
		 doesn't, then the shift at the fail should be no larger
		 than the difference of their depths. */
	      if (!hasevery(fail->links, curr->links))
		if (curr->depth - fail->depth < fail->shift)
		  fail->shift = curr->depth - fail->depth;

	      /* If the current node is accepting then the shift at the
		 fail and its descendants should be no larger than the
		 difference of their depths. */
	      if (curr->accepting && fail->maxshift > curr->depth - fail->depth)
		fail->maxshift = curr->depth - fail->depth;
	    }
	}

      /* Traverse the trie in level order again, fixing up all nodes whose
	 shift exceeds their inherited maxshift. */
      for (curr = kwset->trie->next; curr; curr = curr->next)
	{
	  if (curr->maxshift > curr->parent->maxshift)
	    curr->maxshift = curr->parent->maxshift;
	  if (curr->shift > curr->maxshift)
	    curr->shift = curr->maxshift;
	}

      /* Create a vector, indexed by character code, of the outgoing links
	 from the root node. */
      for (i = 0; i < NCHAR; ++i)
	next[i] = NULL;
      treenext(kwset->trie->links, next);

      if ((trans = kwset->trans) != NULL)
	for (i = 0; i < NCHAR; ++i)
	  kwset->next[i] = next[U(trans[i])];
      else
	memcpy(kwset->next, next, NCHAR * sizeof(struct trie *));
    }

  /* Fix things up for any translation table. */
  if ((trans = kwset->trans) != NULL)
    for (i = 0; i < NCHAR; ++i)
      kwset->delta[i] = delta[U(trans[i])];
  else
    memcpy(kwset->delta, delta, NCHAR);

  return NULL;
}