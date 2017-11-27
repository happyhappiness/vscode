int avl_iterator_prev (avl_iterator_t *iter, void **key, void **value)
{
	avl_node_t *n;

	if ((iter == NULL) || (key == NULL) || (value == NULL))
		return (-1);

	if (iter->node == NULL)
	{
		for (n = iter->tree->root; n != NULL; n = n->left)
			if (n->right == NULL)
				break;
		iter->node = n;
	}
	else
	{
		n = avl_node_prev (iter->tree, iter->node);
	}

	if (n == NULL)
		return (-1);

	iter->node = n;
	*key = n->key;
	*value = n->value;

	return (0);
}