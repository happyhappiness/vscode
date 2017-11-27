static void cs_submit (derive_t context_switches)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = (derive_t) context_switches;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "contextswitch", sizeof (vl.plugin));
	sstrncpy (vl.type, "contextswitch", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}