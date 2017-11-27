static void multimeter_submit (double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "multimeter", sizeof (vl.plugin));
	sstrncpy (vl.type, "multimeter", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}