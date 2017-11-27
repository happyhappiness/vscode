static void ntpd_submit (char *type, char *type_inst, double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "ntpd");
	strcpy (vl.plugin_instance, "");
	strncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}