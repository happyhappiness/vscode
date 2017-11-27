c_avl_iterator_t *c_avl_get_iterator (c_avl_tree_t *t)
{
	c_avl_iterator_t *iter;

	if (t == NULL)
		return (NULL);

	iter = (c_avl_iterator_t *) malloc (sizeof (c_avl_iterator_t));
	if (iter == NULL)
		return (NULL);
	memset (iter, '\0', sizeof (c_avl_iterator_t));
	iter->tree = t;

	return (iter);
}