static void ping_submit (char *host, double latency)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = latency;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "ping");
	strcpy (vl.plugin_instance, "");
	strncpy (vl.type_instance, host, sizeof (vl.type_instance));

	plugin_dispatch_values ("ping", &vl);
}