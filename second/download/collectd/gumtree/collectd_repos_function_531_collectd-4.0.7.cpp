static int register_callback (llist_t **list, const char *name, void *callback)
{
	llentry_t *le;

	if ((*list == NULL)
			&& ((*list = llist_create ()) == NULL))
		return (-1);

	le = llist_search (*list, name);
	if (le == NULL)
	{
		le = llentry_create (name, callback);
		if (le == NULL)
			return (-1);

		llist_append (*list, le);
	}
	else
	{
		le->value = callback;
	}

	return (0);
}