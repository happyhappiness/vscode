int plugin_unregister_data_set (const char *name)
{
	data_set_t *ds;

	if (data_sets == NULL)
		return (-1);

	if (c_avl_remove (data_sets, name, NULL, (void *) &ds) != 0)
		return (-1);

	sfree (ds->ds);
	sfree (ds);

	return (0);
}