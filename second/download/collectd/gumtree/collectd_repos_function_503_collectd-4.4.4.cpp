static void tss2_submit_io (const char *plugin_instance, const char *type,
		counter_t rx, counter_t tx)
{
	/*
	 * Submits the io rx/tx tuple to the collectd daemon
	 */
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values     = values;
	vl.values_len = 2;
	vl.time       = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "teamspeak2", sizeof (vl.plugin));

	if (plugin_instance != NULL)
		sstrncpy (vl.plugin_instance, plugin_instance,
				sizeof (vl.plugin_instance));
	
	plugin_dispatch_values (type, &vl);
}