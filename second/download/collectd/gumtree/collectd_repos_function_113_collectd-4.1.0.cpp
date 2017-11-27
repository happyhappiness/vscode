static void submit_counter (const char *type, const char *type_instance,
		unsigned long long value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	DEBUG ("type = %s; type_instance = %s; value = %llu;",
			type, type_instance, value);

	values[0].counter = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "apache");
	strcpy (vl.plugin_instance, "");
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}