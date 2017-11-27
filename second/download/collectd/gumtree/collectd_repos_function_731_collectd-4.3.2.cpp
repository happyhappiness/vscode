int plugin_unregister_read (const char *name)
{
	llentry_t *e;

	e = llist_search (list_read, name);

	if (e == NULL)
		return (-1);

	llist_remove (list_read, e);
	free (e->value);
	free (e->key);
	llentry_destroy (e);

	return (0);
}