int avl_insert (avl_tree_t *t, void *key, void *value)
{
	avl_node_t *new;
	avl_node_t *nptr;
	int cmp;

	if ((new = (avl_node_t *) malloc (sizeof (avl_node_t))) == NULL)
		return (-1);

	new->key = key;
	new->value = value;
	new->height = 1;
	new->left = NULL;
	new->right = NULL;

	if (t->root == NULL)
	{
		new->parent = NULL;
		t->root = new;
		return (0);
	}

	nptr = t->root;
	while (42)
	{
		cmp = t->compare (nptr->key, new->key);
		if (cmp == 0)
		{
			free_node (new);
			return (-1);
		}
		else if (cmp < 0)
		{
			/* nptr < new */
			if (nptr->right == NULL)
			{
				nptr->right = new;
				new->parent = nptr;
				rebalance (t, nptr);
				break;
			}
			else
			{
				nptr = nptr->right;
			}
		}
		else /* if (cmp > 0) */
		{
			/* nptr > new */
			if (nptr->left == NULL)
			{
				nptr->left = new;
				new->parent = nptr;
				rebalance (t, nptr);
				break;
			}
			else
			{
				nptr = nptr->left;
			}
		}
	} /* while (42) */

	verify_tree (t->root);
	return (0);
}