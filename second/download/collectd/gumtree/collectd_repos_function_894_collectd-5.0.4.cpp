static int submit_values (const char *host, /* {{{ */
		const char *plugin_inst,
		const char *type, const char *type_inst,
		value_t *values, int values_len,
		cdtime_t timestamp, cdtime_t interval)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = values;
	vl.values_len = values_len;

	if (timestamp > 0)
		vl.time = timestamp;

	if (interval > 0)
		vl.interval = interval;

	if (host != NULL)
		sstrncpy (vl.host, host, sizeof (vl.host));
	else
		sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "netapp", sizeof (vl.plugin));
	if (plugin_inst != NULL)
		sstrncpy (vl.plugin_instance, plugin_inst, sizeof (vl.plugin_instance));
	sstrncpy (vl.type, type, sizeof (vl.type));
	if (type_inst != NULL)
		sstrncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));

	return (plugin_dispatch_values (&vl));
}