static void mic_submit_cpu(int micnumber, const char *type_instance,
		int core, derive_t val)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = val;

	vl.values=values;
	vl.values_len=1;

	strncpy (vl.host, hostname_g, sizeof (vl.host));
	strncpy (vl.plugin, "mic", sizeof (vl.plugin));
	if (core < 0) /* global aggregation */
		ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
				"%i", micnumber);
	else /* per-core statistics */
		ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
				"%i-cpu-%i", micnumber, core);
	strncpy (vl.type, "cpu", sizeof (vl.type));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}