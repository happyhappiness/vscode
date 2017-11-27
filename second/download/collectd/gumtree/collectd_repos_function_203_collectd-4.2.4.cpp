static void wireless_submit (const char *plugin_instance, const char *type,
		double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "wireless");
	strncpy (vl.plugin_instance, plugin_instance,
			sizeof (vl.plugin_instance));

	plugin_dispatch_values (type, &vl);
}