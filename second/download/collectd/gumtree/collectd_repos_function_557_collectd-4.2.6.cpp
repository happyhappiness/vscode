static void memory_submit (const char *type_instance, gauge_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "memory");
	strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
	vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

	plugin_dispatch_values ("memory", &vl);
}