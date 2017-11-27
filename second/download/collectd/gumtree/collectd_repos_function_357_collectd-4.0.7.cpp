avl_iterator_t *avl_get_iterator (avl_tree_t *t)
{
	avl_iterator_t *iter;

	if (t == NULL)
		return (NULL);

	iter = (avl_iterator_t *) malloc (sizeof (avl_iterator_t));
	if (iter == NULL)
		return (NULL);
	memset (iter, '\0', sizeof (avl_iterator_t));
	iter->tree = t;

	return (iter);
}