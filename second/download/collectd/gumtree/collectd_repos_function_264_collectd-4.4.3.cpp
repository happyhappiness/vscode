static void nfs_procedures_submit (const char *plugin_instance,
	       	unsigned long long *val, const char **names, int len)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;
	int i;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "nfs", sizeof (vl.plugin));
	strncpy (vl.plugin_instance, plugin_instance,
		       	sizeof (vl.plugin_instance));

	for (i = 0; i < len; i++)
	{
		values[0].counter = val[i];
		strncpy (vl.type_instance, names[i],
				sizeof (vl.type_instance));
		DEBUG ("%s-%s/nfs_procedure-%s = %llu",
				vl.plugin, vl.plugin_instance,
				vl.type_instance, val[i]);
		plugin_dispatch_values ("nfs_procedure", &vl);
	}
}