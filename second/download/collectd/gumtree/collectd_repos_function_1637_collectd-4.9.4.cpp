static void conntrack_submit (double conntrack)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = conntrack;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "conntrack", sizeof (vl.plugin));
	sstrncpy (vl.type, "conntrack", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}