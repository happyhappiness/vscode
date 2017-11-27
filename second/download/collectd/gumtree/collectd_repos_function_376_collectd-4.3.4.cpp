static void serial_submit (const char *type_instance,
		counter_t rx, counter_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values = values;
	vl.values_len = 2;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "serial", sizeof (vl.plugin));
	strncpy (vl.type_instance, type_instance,
			sizeof (vl.type_instance));

	plugin_dispatch_values ("serial_octets", &vl);
}