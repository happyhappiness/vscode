static void sensors_submit (const char *plugin_instance,
		const char *type, const char *type_instance,
		double val)
{
	char match_key[1024];
	int status;

	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	status = snprintf (match_key, sizeof (match_key), "%s/%s-%s",
			plugin_instance, type, type_instance);
	if (status < 1)
		return;
	match_key[sizeof (match_key) - 1] = '\0';

	if (sensor_list != NULL)
	{
		DEBUG ("sensors plugin: Checking ignorelist for `%s'", match_key);
		if (ignorelist_match (sensor_list, match_key))
			return;
	}

	values[0].gauge = val;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);

	strncpy (vl.host, hostname_g, sizeof (vl.host));
	vl.host[sizeof (vl.host) - 1] = '\0';
	strncpy (vl.plugin, "sensors", sizeof (vl.plugin));
	vl.plugin[sizeof (vl.plugin) - 1] = '\0';
	strncpy (vl.plugin_instance, plugin_instance,
			sizeof (vl.plugin_instance));
	vl.plugin_instance[sizeof (vl.plugin_instance) - 1] = '\0';
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
	vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

	plugin_dispatch_values (type, &vl);
}