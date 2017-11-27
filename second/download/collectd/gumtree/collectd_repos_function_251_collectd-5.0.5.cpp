static int varnish_config_instance (const oconfig_item_t *ci) /* {{{ */
{
	user_config_t *conf;
	user_data_t ud;
	char callback_name[DATA_MAX_NAME_LEN];
	int i;

	conf = malloc (sizeof (*conf));
	if (conf == NULL)
		return (ENOMEM);
	memset (conf, 0, sizeof (*conf));
	conf->instance = NULL;

	varnish_config_apply_default (conf);

	if (ci->values_num == 1)
	{
		int status;

		status = cf_util_get_string (ci, &conf->instance);
		if (status != 0)
		{
			sfree (conf);
			return (status);
		}
		assert (conf->instance != NULL);

		if (strcmp ("localhost", conf->instance) == 0)
		{
			sfree (conf->instance);
			conf->instance = NULL;
		}
	}
	else if (ci->values_num > 1)
	{
		WARNING ("Varnish plugin: \"Instance\" blocks accept only "
				"one argument.");
		return (EINVAL);
	}

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("CollectCache", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_cache);
		else if (strcasecmp ("CollectConnections", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_connections);
		else if (strcasecmp ("CollectESI", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_esi);
		else if (strcasecmp ("CollectBackend", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_backend);
		else if (strcasecmp ("CollectFetch", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_fetch);
		else if (strcasecmp ("CollectHCB", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_hcb);
		else if (strcasecmp ("CollectSHM", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_shm);
		else if (strcasecmp ("CollectSMA", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_sma);
		else if (strcasecmp ("CollectSMS", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_sms);
		else if (strcasecmp ("CollectSM", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_sm);
		else if (strcasecmp ("CollectTotals", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_totals);
		else if (strcasecmp ("CollectWorkers", child->key) == 0)
			cf_util_get_boolean (child, &conf->collect_workers);
		else
		{
			WARNING ("Varnish plugin: Ignoring unknown "
					"configuration option: \"%s\"",
					child->key);
		}
	}

	if (!conf->collect_cache
			&& !conf->collect_connections
			&& !conf->collect_esi
			&& !conf->collect_backend
			&& !conf->collect_fetch
			&& !conf->collect_hcb
			&& !conf->collect_shm
			&& !conf->collect_sma
			&& !conf->collect_sms
			&& !conf->collect_sm
			&& !conf->collect_totals
			&& !conf->collect_workers)
	{
		WARNING ("Varnish plugin: No metric has been configured for "
				"instance \"%s\". Disabling this instance.",
				(conf->instance == NULL) ? "localhost" : conf->instance);
		return (EINVAL);
	}

	ssnprintf (callback_name, sizeof (callback_name), "varnish/%s",
			(conf->instance == NULL) ? "localhost" : conf->instance);

	ud.data = conf;
	ud.free_func = varnish_config_free;

	plugin_register_complex_read (/* group = */ "varnish",
			/* name      = */ callback_name,
			/* callback  = */ varnish_read,
			/* interval  = */ NULL,
			/* user data = */ &ud);

	have_instance = 1;

	return (0);
}