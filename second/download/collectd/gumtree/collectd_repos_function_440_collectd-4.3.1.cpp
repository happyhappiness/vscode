static void submit_gauge (const char *plugin_instance, const char *type,
		const char *type_instance, gauge_t value)

{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "vserver");
	strncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}