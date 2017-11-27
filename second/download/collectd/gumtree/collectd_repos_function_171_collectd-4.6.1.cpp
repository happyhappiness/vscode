static void ping_submit (char *host, double latency)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = latency;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "ping", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));
	sstrncpy (vl.type_instance, host, sizeof (vl.type_instance));
	sstrncpy (vl.type, "ping", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}