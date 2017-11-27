c_avl_tree_t *c_avl_create (int (*compare) (const void *, const void *))
{
	c_avl_tree_t *t;

	if (compare == NULL)
		return (NULL);

	if ((t = (c_avl_tree_t *) malloc (sizeof (c_avl_tree_t))) == NULL)
		return (NULL);

	t->root = NULL;
	t->compare = compare;
	t->size = 0;

	return (t);
}