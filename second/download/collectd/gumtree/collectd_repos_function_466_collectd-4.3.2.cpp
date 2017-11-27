int c_avl_get (c_avl_tree_t *t, const void *key, void **value)
{
	c_avl_node_t *n;

	n = search (t, key);
	if (n == NULL)
		return (-1);

	if (value != NULL)
		*value = n->value;

	return (0);
}