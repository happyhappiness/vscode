static void cipvs_submit_connections (char *pi, char *ti, counter_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = value;

	vl.values     = values;
	vl.values_len = 1;

	vl.time     = time (NULL);
	vl.interval = interval_g;

	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "ipvs");
	strcpy (vl.plugin_instance, pi);
	strcpy (vl.type_instance, (NULL != ti) ? ti : "total");

	plugin_dispatch_values ("connections", &vl);
	return;
}