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
	if ((status < 1) || (status >= sizeof (match_key)))
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
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "sensors");
	strcpy (vl.plugin_instance, plugin_instance);
	strcpy (vl.type_instance, type_instance);

	plugin_dispatch_values (type, &vl);
}