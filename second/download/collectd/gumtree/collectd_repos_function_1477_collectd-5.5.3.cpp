static void cpufreq_submit (int cpu_num, double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "cpufreq", sizeof (vl.plugin));
	sstrncpy (vl.type, "cpufreq", sizeof (vl.type));
	ssnprintf (vl.type_instance, sizeof (vl.type_instance),
			"%i", cpu_num);

	plugin_dispatch_values (&vl);
}