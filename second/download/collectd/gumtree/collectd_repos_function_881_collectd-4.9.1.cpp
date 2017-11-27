static int cna_config (oconfig_item_t *ci) { /* {{{ */
	int i;
	oconfig_item_t *item;

	for (i = 0; i < ci->children_num; ++i) {
		item = ci->children + i;

		if (strcasecmp(item->key, "Host") == 0)
		{
			host_config_t *host;
			char cb_name[256];
			struct timespec interval;
			user_data_t ud;

			host = cna_config_host (item);
			if (host == NULL)
				continue;

			ssnprintf (cb_name, sizeof (cb_name), "netapp-%s", host->name);

			memset (&interval, 0, sizeof (interval));
			interval.tv_sec = host->interval;

			memset (&ud, 0, sizeof (ud));
			ud.data = host;
			ud.free_func = (void (*) (void *)) free_host_config;

			plugin_register_complex_read (cb_name,
					/* callback  = */ cna_read, 
					/* interval  = */ (host->interval > 0) ? &interval : NULL,
					/* user data = */ &ud);
			continue;
		}
		else /* if (item->key != "Host") */
		{
			WARNING("netapp plugin: Ignoring unknown config option \"%s\".", item->key);
		}
	}
	return 0;
}