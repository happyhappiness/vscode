static void thermal_submit (const char *plugin_instance, enum dev_type dt,
		gauge_t value)
{
	value_list_t vl = VALUE_LIST_INIT;
	value_t v;

	v.gauge = value;
	vl.values = &v;

	sstrncpy (vl.plugin, "thermal", sizeof(vl.plugin));
	if (plugin_instance != NULL)
		sstrncpy (vl.plugin_instance, plugin_instance,
				sizeof (vl.plugin_instance));
	sstrncpy (vl.type,
			(dt == TEMP) ? "temperature" : "gauge",
			sizeof (vl.type));

	plugin_dispatch_values (&vl);
}