static void tape_submit (const char *plugin_instance,
		const char *type,
		counter_t read, counter_t write)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = read;
	values[1].counter = write;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "tape", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, plugin_instance,
			sizeof (vl.plugin_instance));
	sstrncpy (vl.type, type, sizeof (vl.type));

	plugin_dispatch_values (&vl);
}