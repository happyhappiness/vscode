static void submit_counter (const char *type, const char *type_instance,
		counter_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "dns", sizeof (vl.plugin));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}