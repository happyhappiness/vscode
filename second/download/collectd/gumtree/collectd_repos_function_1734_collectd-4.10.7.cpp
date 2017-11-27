static void conntrack_submit (value_t conntrack)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = &conntrack;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "conntrack", sizeof (vl.plugin));
	sstrncpy (vl.type, "conntrack", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}