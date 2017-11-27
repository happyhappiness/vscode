static void submit (int cpu_num, const char *type_instance, counter_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = value;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "cpu", sizeof (vl.plugin));
	ssnprintf (vl.plugin_instance, sizeof (vl.type_instance),
			"%i", cpu_num);
	sstrncpy (vl.type, "cpu", sizeof (vl.type));
	sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}