static void submit_gauge (const char *type, const char *type_instance,
		gauge_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "apache", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));

	if (type_instance != NULL)
	{
		strncpy (vl.type_instance, type_instance,
				sizeof (vl.type_instance));
		vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';
	}

	plugin_dispatch_values (type, &vl);
}