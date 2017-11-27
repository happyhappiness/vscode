static avl_node_t *avl_node_next (avl_tree_t *t, avl_node_t *n)
{
	avl_node_t *r; /* return node */

	if (n == NULL)
	{
		return (NULL);
	}

	/* If we can't descent any further, we have to backtrack to the first
	 * parent that's bigger than we, i. e. who's _left_ child we are. */
	if (n->right == NULL)
	{
		r = n->parent;
		while ((r != NULL) && (r->parent != NULL))
		{
			if (r->left == n)
				break;
			n = r;
			r = n->parent;
		}

		/* n->right == NULL && r == NULL => t is root and has no next
		 * r->left != n => r->right = n => r->parent == NULL */
		if ((r == NULL) || (r->left != n))
		{
			assert ((r == NULL) || (r->parent == NULL));
			return (NULL);
		}
		else
		{
			assert (r->left == n);
			return (r);
		}
	}
	else
	{
		r = n->right;
		while (r->left != NULL)
			r = r->left;
	}

	return (r);
}