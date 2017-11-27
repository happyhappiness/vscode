int plugin_register_data_set (const data_set_t *ds)
{
	data_set_t *ds_copy;
	int i;

	if ((list_data_set != NULL)
			&& (llist_search (list_data_set, ds->type) != NULL))
	{
		NOTICE ("Replacing DS `%s' with another version.", ds->type);
		plugin_unregister_data_set (ds->type);
	}

	ds_copy = (data_set_t *) malloc (sizeof (data_set_t));
	if (ds_copy == NULL)
		return (-1);
	memcpy(ds_copy, ds, sizeof (data_set_t));

	ds_copy->ds = (data_source_t *) malloc (sizeof (data_source_t)
			* ds->ds_num);
	if (ds_copy->ds == NULL)
	{
		free (ds_copy);
		return (-1);
	}

	for (i = 0; i < ds->ds_num; i++)
		memcpy (ds_copy->ds + i, ds->ds + i, sizeof (data_source_t));

	return (register_callback (&list_data_set, ds->type, (void *) ds_copy));
}