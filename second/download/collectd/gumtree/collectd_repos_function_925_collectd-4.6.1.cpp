static void traffic_submit (counter_t rx, counter_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "mysql", sizeof (vl.plugin));
	sstrncpy (vl.type, "mysql_octets", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}