static void mic_submit_power(int micnumber, const char *type, const char *type_instance, gauge_t val)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = val;

	vl.values=values;
	vl.values_len=1;

	strncpy (vl.host, hostname_g, sizeof (vl.host));
	strncpy (vl.plugin, "mic", sizeof (vl.plugin));
	ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance), "%i", micnumber);
	strncpy (vl.type, type, sizeof (vl.type));
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}