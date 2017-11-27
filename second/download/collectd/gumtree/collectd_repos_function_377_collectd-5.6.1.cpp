static int apcups_config (oconfig_item_t *ci)
{
	_Bool persistent_conn_set = 0;

	for (int i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp (child->key, "Host") == 0)
			cf_util_get_string (child, &conf_node);
		else if (strcasecmp (child->key, "Port") == 0)
			cf_util_get_service (child, &conf_service);
		else if (strcasecmp (child->key, "ReportSeconds") == 0)
			cf_util_get_boolean (child, &conf_report_seconds);
		else if (strcasecmp (child->key, "PersistentConnection") == 0) {
			cf_util_get_boolean (child, &conf_persistent_conn);
			persistent_conn_set = 1;
		}
		else
			ERROR ("apcups plugin: Unknown config option \"%s\".", child->key);
	}

	if (!persistent_conn_set) {
		double interval = CDTIME_T_TO_DOUBLE(plugin_get_interval());
		if (interval > APCUPS_SERVER_TIMEOUT) {
			NOTICE ("apcups plugin: Plugin poll interval set to %.3f seconds. "
				"Apcupsd NIS socket timeout is %.3f seconds, "
				"PersistentConnection disabled by default.",
				interval, APCUPS_SERVER_TIMEOUT);
			conf_persistent_conn = 0;
		}
	}

	return (0);
}