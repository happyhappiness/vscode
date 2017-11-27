static void cpufreq_submit (int cpu_num, double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "cpufreq");
	snprintf (vl.type_instance, sizeof (vl.type_instance),
			"%i", cpu_num);

	plugin_dispatch_values ("cpufreq", &vl);
}