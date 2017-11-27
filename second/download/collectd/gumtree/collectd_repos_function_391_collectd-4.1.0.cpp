int avl_get (avl_tree_t *t, const void *key, void **value)
{
	avl_node_t *n;

	assert (value != NULL);

	n = search (t, key);
	if (n == NULL)
		return (-1);

	*value = n->value;

	return (0);
}