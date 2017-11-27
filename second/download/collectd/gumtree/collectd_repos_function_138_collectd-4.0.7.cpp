static void submit (int cpu_num, const char *type_instance, counter_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "cpu");
	snprintf (vl.plugin_instance, sizeof (vl.type_instance),
			"%i", cpu_num);
	vl.plugin_instance[DATA_MAX_NAME_LEN - 1] = '\0';
	strcpy (vl.type_instance, type_instance);

	plugin_dispatch_values ("cpu", &vl);
}