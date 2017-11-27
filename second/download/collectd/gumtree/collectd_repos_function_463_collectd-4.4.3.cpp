static void traffic_submit (const char *plugin_instance,
		const char *type_instance, counter_t rx, counter_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "vserver", sizeof (vl.plugin));
	strncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values ("if_octets", &vl);
}