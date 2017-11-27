int plugin_unregister_data_set (const char *name)
{
	llentry_t  *e;
	data_set_t *ds;

	if (list_data_set == NULL)
		return (-1);

	e = llist_search (list_data_set, name);

	if (e == NULL)
		return (-1);

	llist_remove (list_data_set, e);
	ds = (data_set_t *) e->value;
	llentry_destroy (e);

	sfree (ds->ds);
	sfree (ds);

	return (0);
}