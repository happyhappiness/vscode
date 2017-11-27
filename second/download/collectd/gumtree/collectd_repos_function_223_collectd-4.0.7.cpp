static void ps_submit_state (const char *state, double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "processes");
	strcpy (vl.plugin_instance, "");
	strncpy (vl.type_instance, state, sizeof (vl.type_instance));

	plugin_dispatch_values ("ps_state", &vl);
}