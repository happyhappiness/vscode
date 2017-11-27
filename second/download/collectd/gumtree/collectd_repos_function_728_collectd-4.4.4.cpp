static void threads_submit (gauge_t running, gauge_t connected, gauge_t cached,
		counter_t created)
{
	value_t values[4];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge   = running;
	values[1].gauge   = connected;
	values[2].gauge   = cached;
	values[3].counter = created;

	vl.values = values;
	vl.values_len = 4;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "mysql", sizeof (vl.plugin));

	plugin_dispatch_values ("mysql_threads", &vl);
}