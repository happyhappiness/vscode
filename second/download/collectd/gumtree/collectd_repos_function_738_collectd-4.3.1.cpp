int plugin_dispatch_values (const char *name, value_list_t *vl)
{
	int (*callback) (const data_set_t *, const value_list_t *);
	data_set_t *ds;
	llentry_t *le;

	if ((list_write == NULL) || (data_sets == NULL))
		return (-1);

	if (c_avl_get (data_sets, name, (void *) &ds) != 0)
	{
		DEBUG ("No such dataset registered: %s", name);
		return (-1);
	}

	DEBUG ("plugin: plugin_dispatch_values: time = %u; interval = %i; "
			"host = %s; "
			"plugin = %s; plugin_instance = %s; "
			"type = %s; type_instance = %s;",
			(unsigned int) vl->time, vl->interval,
			vl->host,
			vl->plugin, vl->plugin_instance,
			ds->type, vl->type_instance);

#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("plugin: ds->type = %s: (ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	escape_slashes (vl->host, sizeof (vl->host));
	escape_slashes (vl->plugin, sizeof (vl->plugin));
	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
	escape_slashes (vl->type_instance, sizeof (vl->type_instance));

	/* Update the value cache */
	uc_update (ds, vl);
	ut_check_threshold (ds, vl);

	le = llist_head (list_write);
	while (le != NULL)
	{
		callback = (int (*) (const data_set_t *, const value_list_t *)) le->value;
		(*callback) (ds, vl);

		le = le->next;
	}

	return (0);
}