static int plugin_unregister (llist_t *list, const char *name)
{
	llentry_t *e;

	e = llist_search (list, name);

	if (e == NULL)
		return (-1);

	llist_remove (list, e);
	free (e->key);
	llentry_destroy (e);

	return (0);
}