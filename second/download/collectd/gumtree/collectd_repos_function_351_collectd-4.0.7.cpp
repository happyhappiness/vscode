avl_tree_t *avl_create (int (*compare) (const void *, const void *))
{
	avl_tree_t *t;

	if (compare == NULL)
		return (NULL);

	if ((t = (avl_tree_t *) malloc (sizeof (avl_tree_t))) == NULL)
		return (NULL);

	t->root = NULL;
	t->compare = compare;

	return (t);
}