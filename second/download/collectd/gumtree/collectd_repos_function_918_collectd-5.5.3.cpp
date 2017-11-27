static void zookeeper_submit_derive (const char * type, const char * type_inst, derive_t val)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = val;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "zookeeper", sizeof (vl.plugin));
	sstrncpy (vl.type, type, sizeof (vl.type));
	if (type_inst != NULL)
		sstrncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}