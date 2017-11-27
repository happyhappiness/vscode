static void ps_submit_fork_rate (derive_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = value;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy(vl.host, hostname_g, sizeof (vl.host));
	sstrncpy(vl.plugin, "processes", sizeof (vl.plugin));
	sstrncpy(vl.plugin_instance, "", sizeof (vl.plugin_instance));
	sstrncpy(vl.type, "fork_rate", sizeof (vl.type));
	sstrncpy(vl.type_instance, "", sizeof (vl.type_instance));

	plugin_dispatch_values(&vl);
}