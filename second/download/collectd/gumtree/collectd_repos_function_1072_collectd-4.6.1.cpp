int plugin_dispatch_values (value_list_t *vl)
{
	int status;
	static c_complain_t no_write_complaint = C_COMPLAIN_INIT_STATIC;

	data_set_t *ds;

	if ((vl == NULL) || (*vl->type == '\0')) {
		ERROR ("plugin_dispatch_values: Invalid value list.");
		return (-1);
	}

	if (list_write == NULL)
		c_complain_once (LOG_WARNING, &no_write_complaint,
				"plugin_dispatch_values: No write callback has been "
				"registered. Please load at least one output plugin, "
				"if you want the collected data to be stored.");

	if (data_sets == NULL)
	{
		ERROR ("plugin_dispatch_values: No data sets registered. "
				"Could the types database be read? Check "
				"your `TypesDB' setting!");
		return (-1);
	}

	if (c_avl_get (data_sets, vl->type, (void *) &ds) != 0)
	{
		INFO ("plugin_dispatch_values: Dataset not found: %s", vl->type);
		return (-1);
	}

	if (vl->time == 0)
		vl->time = time (NULL);

	DEBUG ("plugin_dispatch_values: time = %u; interval = %i; "
			"host = %s; "
			"plugin = %s; plugin_instance = %s; "
			"type = %s; type_instance = %s;",
			(unsigned int) vl->time, vl->interval,
			vl->host,
			vl->plugin, vl->plugin_instance,
			vl->type, vl->type_instance);

#if COLLECT_DEBUG
	assert (0 == strcmp (ds->type, vl->type));
#else
	if (0 != strcmp (ds->type, vl->type))
		WARNING ("plugin_dispatch_values: (ds->type = %s) != (vl->type = %s)",
				ds->type, vl->type);
#endif

#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("plugin_dispatch_values: ds->type = %s: "
				"(ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	escape_slashes (vl->host, sizeof (vl->host));
	escape_slashes (vl->plugin, sizeof (vl->plugin));
	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
	escape_slashes (vl->type, sizeof (vl->type));
	escape_slashes (vl->type_instance, sizeof (vl->type_instance));

	if (pre_cache_chain != NULL)
	{
		status = fc_process_chain (ds, vl, pre_cache_chain);
		if (status < 0)
		{
			WARNING ("plugin_dispatch_values: Running the "
					"pre-cache chain failed with "
					"status %i (%#x).",
					status, status);
		}
		else if (status == FC_TARGET_STOP)
			return (0);
	}

	/* Update the value cache */
	uc_update (ds, vl);

	if (post_cache_chain != NULL)
	{
		status = fc_process_chain (ds, vl, post_cache_chain);
		if (status < 0)
		{
			WARNING ("plugin_dispatch_values: Running the "
					"post-cache chain failed with "
					"status %i (%#x).",
					status, status);
		}
	}
	else
		fc_default_action (ds, vl);

	return (0);
}