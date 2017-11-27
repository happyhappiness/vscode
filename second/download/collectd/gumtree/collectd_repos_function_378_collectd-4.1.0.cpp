static avl_node_t *search (avl_tree_t *t, const void *key)
{
	avl_node_t *n;
	int cmp;

	n = t->root;
	while (n != NULL)
	{
		cmp = t->compare (key, n->key);
		if (cmp == 0)
			return (n);
		else if (cmp < 0)
			n = n->left;
		else
			n = n->right;
	}

	return (NULL);
}