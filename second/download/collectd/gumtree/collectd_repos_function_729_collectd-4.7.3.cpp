static void openvpn_submit (char *name, counter_t rx, counter_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "openvpn", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, name, sizeof (vl.plugin_instance));
	sstrncpy (vl.type, "if_octets", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}