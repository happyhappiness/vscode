static void nfs_procedures_submit (const char *plugin_instance,
		const char **type_instances,
		value_t *values, size_t values_num)
{
	value_list_t vl = VALUE_LIST_INIT;
	size_t i;

	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "nfs", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, plugin_instance,
			sizeof (vl.plugin_instance));
	sstrncpy (vl.type, "nfs_procedure", sizeof (vl.type));

	for (i = 0; i < values_num; i++)
	{
		vl.values = values + i;
		sstrncpy (vl.type_instance, type_instances[i],
				sizeof (vl.type_instance));
		plugin_dispatch_values_secure (&vl);
	}
}