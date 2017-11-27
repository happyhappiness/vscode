int plugin_dispatch_values (value_list_t *vl)
{
	int status;
	static c_complain_t no_write_complaint = C_COMPLAIN_INIT_STATIC;

	value_t *saved_values;
	int      saved_values_len;

	data_set_t *ds;

	int free_meta_data = 0;

	if ((vl == NULL) || (vl->type[0] == 0)
			|| (vl->values == NULL) || (vl->values_len < 1))
	{
		ERROR ("plugin_dispatch_values: Invalid value list "
				"from plugin %s.", vl->plugin);
		return (-1);
	}

	/* Free meta data only if the calling function didn't specify any. In
	 * this case matches and targets may add some and the calling function
	 * may not expect (and therefore free) that data. */
	if (vl->meta == NULL)
		free_meta_data = 1;

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
		char ident[6 * DATA_MAX_NAME_LEN];

		FORMAT_VL (ident, sizeof (ident), vl);
		INFO ("plugin_dispatch_values: Dataset not found: %s "
				"(from \"%s\"), check your types.db!",
				vl->type, ident);
		return (-1);
	}

	if (vl->time == 0)
		vl->time = cdtime ();

	if (vl->interval <= 0)
		vl->interval = interval_g;

	DEBUG ("plugin_dispatch_values: time = %.3f; interval = %.3f; "
			"host = %s; "
			"plugin = %s; plugin_instance = %s; "
			"type = %s; type_instance = %s;",
			CDTIME_T_TO_DOUBLE (vl->time),
			CDTIME_T_TO_DOUBLE (vl->interval),
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

	/* Copy the values. This way, we can assure `targets' that they get
	 * dynamically allocated values, which they can free and replace if
	 * they like. */
	if ((pre_cache_chain != NULL) || (post_cache_chain != NULL))
	{
		saved_values     = vl->values;
		saved_values_len = vl->values_len;

		vl->values = (value_t *) calloc (vl->values_len,
				sizeof (*vl->values));
		if (vl->values == NULL)
		{
			ERROR ("plugin_dispatch_values: calloc failed.");
			vl->values = saved_values;
			return (-1);
		}
		memcpy (vl->values, saved_values,
				vl->values_len * sizeof (*vl->values));
	}
	else /* if ((pre == NULL) && (post == NULL)) */
	{
		saved_values     = NULL;
		saved_values_len = 0;
	}

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
		{
			/* Restore the state of the value_list so that plugins
			 * don't get confused.. */
			if (saved_values != NULL)
			{
				free (vl->values);
				vl->values     = saved_values;
				vl->values_len = saved_values_len;
			}
			return (0);
		}
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

	/* Restore the state of the value_list so that plugins don't get
	 * confused.. */
	if (saved_values != NULL)
	{
		free (vl->values);
		vl->values     = saved_values;
		vl->values_len = saved_values_len;
	}

	if ((free_meta_data != 0) && (vl->meta != NULL))
	{
		meta_data_destroy (vl->meta);
		vl->meta = NULL;
	}

	return (0);
}